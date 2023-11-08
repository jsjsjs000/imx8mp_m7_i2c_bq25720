#include <stdio.h>
#include <stdbool.h>
#include <fsl_device_registers.h>

#define SMBUS_BQ25720_BASE                  I2C4
#define SMBUS_BQ25720_IRQN                  I2C4_IRQn
#define SMBUS_BQ25720_CLK_ROOT              kCLOCK_RootI2c4
#define SMBUS_BQ25720_ROOT_MUX_SYS_PLL_DIV  kCLOCK_I2cRootmuxSysPll1Div5
#define SMBUS_BQ25720_CLK_FREQ                                                                      \
		(CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(SMBUS_BQ25720_CLK_ROOT)) /  \
		(CLOCK_GetRootPostDivider(SMBUS_BQ25720_CLK_ROOT)) / 5)                           /* SYSTEM PLL1 DIV5 */

#define SMBUS_BQ25720 ((I2C_Type *)SMBUS_BQ25720_BASE)

#define SMBUS_BQ25720_SLAVE_ADDR_7BIT  0x09     /* SMBUS_BQ25720 0x12 */
#define I2C_BAUDRATE                   100000   /* 100 KHz */
#define I2C_BUFFOR_SIZE                64

#define master_task_PRIORITY (configMAX_PRIORITIES - 2)

// #define I2C_TASK_TIMER_IN_MS  50
// #define I2C_TASK_TIMER_OUT_MS 100

extern void i2c_task_initialize(void);
extern void i2c_task_task(void *pvParameters);
extern bool i2c_task_read_data(uint8_t *send, size_t send_size, uint8_t *received, size_t received_size);
extern bool i2c_task_write_data(uint8_t *data, size_t data_size);
