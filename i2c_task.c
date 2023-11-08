	/* Freescale includes. */
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include <fsl_gpio.h>
#include <fsl_i2c.h>
#include <fsl_i2c_freertos.h>

	/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

	/* Board config */
#include "board_cfg/board.h"
#include "board_cfg/clock_config.h"
#include "board_cfg/pin_mux.h"

#include "main.h"
#include "common.h"
#include "i2c_task.h"
#include "i2c_bq25720.h"
#include "i2c_bq25720_print.h"

static uint8_t i2c_buffor[I2C_BUFFOR_SIZE];
static i2c_master_handle_t *i2c_master_handle;

static i2c_rtos_handle_t master_rtos_handle;
static i2c_master_config_t masterConfig;
static i2c_master_transfer_t masterXfer;
static uint32_t sourceClock;

static void i2c_task_initialize_i2c(void);

void i2c_task_initialize(void)
{
	CLOCK_SetRootMux(SMBUS_BQ25720_CLK_ROOT, SMBUS_BQ25720_ROOT_MUX_SYS_PLL_DIV); /* Set I2C source to SysPLL1 Div5 160MHZ */
	CLOCK_SetRootDivider(SMBUS_BQ25720_CLK_ROOT, 1U, 10U);                        /* Set root clock to 160MHZ / 10 = 16MHZ */
	NVIC_SetPriority(SMBUS_BQ25720_IRQN, 3);

	i2c_task_initialize_i2c();
}

static void i2c_task_initialize_i2c(void)
{
	/*
		masterConfig.baudRate_Bps = 100000U;
		masterConfig.enableStopHold = false;
		masterConfig.glitchFilterWidth = 0U;
		masterConfig.enableMaster = true;
	*/
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	sourceClock = SMBUS_BQ25720_CLK_FREQ;

	status_t status = I2C_RTOS_Init(&master_rtos_handle, SMBUS_BQ25720, &masterConfig, sourceClock);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during init, 0x%x\r\n", status);
	}

	i2c_master_handle = &master_rtos_handle.drv_handle;

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = SMBUS_BQ25720_SLAVE_ADDR_7BIT;
	masterXfer.direction      = kI2C_Write;
	masterXfer.data           = i2c_buffor;
	masterXfer.dataSize       = 0;
	masterXfer.flags          = kI2C_TransferDefaultFlag;
}

void i2c_task_task(void *pvParameters)
{
	PRINTF("I2C task started.\r\n\r\n");
	vTaskDelay(pdMS_TO_TICKS(500));

	uint16_t write_charge_current = 128;
	bool write_charge_current_ok = i2c_bq25720_write_charge_current(write_charge_current);
	PRINTF("Write charge current %dmA. Ok = %d\r\n\r\n", write_charge_current, write_charge_current_ok);
	vTaskDelay(pdMS_TO_TICKS(500));

	union charge_option0_t charge_option0;
	if (i2c_bq25720_read_charge_option0(&charge_option0))
		i2c_bq25720_print_charge_option0(&charge_option0);
	else
		PRINTF("Can't read charge option0.\r\n");

	uint16_t charge_current;
	if (i2c_bq25720_read_charge_current(&charge_current))
		i2c_bq25720_print_charge_current(charge_current);
	else
		PRINTF("Can't read charge current.\r\n");

	uint16_t charge_voltage;
	if (i2c_bq25720_read_charge_voltage(&charge_voltage))
		i2c_bq25720_print_charge_voltage(charge_voltage);
	else
		PRINTF("Can't read charge voltage.\r\n");

	union charger_status_t charger_status;
	if (i2c_bq25720_read_charger_status(&charger_status))
		i2c_bq25720_print_charger_status(&charger_status);
	else
		PRINTF("Can't read charger status.\r\n");

	union prochot_status_t prochot_status;
	if (i2c_bq25720_read_prochot_status(&prochot_status))
		i2c_bq25720_print_prochot_status(&prochot_status);
	else
		PRINTF("Can't read PROCHOT status.\r\n");

	uint16_t iin_dpm;
	if (i2c_bq25720_read_iin_dpm(&iin_dpm))
		i2c_bq25720_print_iin_dpm(iin_dpm);
	else
		PRINTF("Can't read Iin dpm.\r\n");

	union adcvbus_psys_t adcvbus_psys;
	if (i2c_bq25720_read_adcvbus_psys(&adcvbus_psys))
		i2c_bq25720_print_adcvbus_psys(&adcvbus_psys);
	else
		PRINTF("Can't read ADC Vbus psys.\r\n");

	union adcibat_t adcibat;
	if (i2c_bq25720_read_adcibat(&adcibat))
		i2c_bq25720_print_adcibat(&adcibat);
	else
		PRINTF("Can't read ADC Ibat.\r\n");

	union adciincmpin_t adciincmpin;
	if (i2c_bq25720_read_adciincmpin(&adciincmpin))
		i2c_bq25720_print_adciincmpin(&adciincmpin);
	else
		PRINTF("Can't read AdcIinCmpIn.\r\n");

	union adcvsysvbat_t adcvsysvbat;
	if (i2c_bq25720_read_adcvsysvbat(&adcvsysvbat))
		i2c_bq25720_print_adcvsysvbat(&adcvsysvbat);
	else
		PRINTF("Can't read AdcVSysBat.\r\n");

	union charge_option1_t charge_option1;
	if (i2c_bq25720_read_charge_option1(&charge_option1))
		i2c_bq25720_print_charge_option1(&charge_option1);
	else
		PRINTF("Can't read charge option1.\r\n");

	union charge_option2_t charge_option2;
	if (i2c_bq25720_read_charge_option2(&charge_option2))
		i2c_bq25720_print_charge_option2(&charge_option2);
	else
		PRINTF("Can't read charge option2.\r\n");

	union charge_option3_t charge_option3;
	if (i2c_bq25720_read_charge_option3(&charge_option3))
		i2c_bq25720_print_charge_option3(&charge_option3);
	else
		PRINTF("Can't read charge option3.\r\n");

	union prochot_option0_t prochot_option0;
	if (i2c_bq25720_read_prochot_option0(&prochot_option0))
		i2c_bq25720_print_prochot_option0(&prochot_option0);
	else
		PRINTF("Can't read PROCHOT option0.\r\n");

	union prochot_option1_t prochot_option1;
	if (i2c_bq25720_read_prochot_option1(&prochot_option1))
		i2c_bq25720_print_prochot_option1(&prochot_option1);
	else
		PRINTF("Can't read PROCHOT option1.\r\n");

	union adc_option_t adc_option;
	if (i2c_bq25720_read_adc_option(&adc_option))
		i2c_bq25720_print_adc_option(&adc_option);
	else
		PRINTF("Can't read ADC option.\r\n");

	union charge_option4_t charge_option4;
	if (i2c_bq25720_read_charge_option4(&charge_option4))
		i2c_bq25720_print_charge_option4(&charge_option4);
	else
		PRINTF("Can't read charge option4.\r\n");

	union vmin_active_protection_t vmin_active_protection;
	if (i2c_bq25720_read_vmin_active_protection(&vmin_active_protection))
		i2c_bq25720_print_vmin_active_protection(&vmin_active_protection);
	else
		PRINTF("Can't read Vmin active protection.\r\n");

	uint16_t input_voltage;
	if (i2c_bq25720_read_input_voltage(&input_voltage))
		i2c_bq25720_print_input_voltage(input_voltage);
	else
		PRINTF("Can't read Input voltage.\r\n");

	uint16_t vsys_min;
	if (i2c_bq25720_read_vsys_min(&vsys_min))
		i2c_bq25720_print_vsys_min(vsys_min);
	else
		PRINTF("Can't read Vsys min.\r\n");

	uint16_t iin_host;
	if (i2c_bq25720_read_iin_host(&iin_host))
		i2c_bq25720_print_iin_host(iin_host);
	else
		PRINTF("Can't read Iin host.\r\n");

	uint16_t manufacturer_id;
	if (i2c_bq25720_read_manufacturer_id(&manufacturer_id))
		i2c_bq25720_print_manufacturer_id(manufacturer_id);
	else
		PRINTF("Can't read Manufacturer ID.\r\n");

	uint16_t device_id;
	if (i2c_bq25720_read_device_id(&device_id))
		i2c_bq25720_print_device_id(device_id);
	else
		PRINTF("Can't read Device ID.\r\n");;

	while (true)
	{
		vTaskDelay(pdMS_TO_TICKS(500));
	}

	vTaskSuspend(NULL);
}

bool i2c_task_read_data(uint8_t *send, size_t send_size, uint8_t *received, size_t received_size)
{
	memcpy(i2c_buffor, send, send_size);

		/* write to I2C */
	masterXfer.direction = kI2C_Write;
	masterXfer.dataSize = 1;

	status_t status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during write transaction, 0x%x\r\n", status);
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

		/* read from I2C */
	masterXfer.direction = kI2C_Read;
	masterXfer.dataSize = received_size;

	status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during read transaction, 0x%x\r\n", status);
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

	memcpy(received, i2c_buffor, received_size);

	return true;
}

bool i2c_task_write_data(uint8_t *data, size_t data_size)
{
	memcpy(i2c_buffor, data, data_size);

		/* write to I2C */
	masterXfer.direction = kI2C_Write;
	masterXfer.dataSize = data_size;

	status_t status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during write transaction, 0x%x\r\n", status);
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

	return true;
}
