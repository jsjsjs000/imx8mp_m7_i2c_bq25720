#include <fsl_common.h>
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include "common.h"
#include "i2c_task.h"
#include "i2c_bq25720.h"
#include "i2c_bq25720_print.h"

	/// read and write I2C
static bool i2c_bq25720_read_2_registers(uint8_t reg, uint16_t *received)
{
	uint8_t send[] = { reg };
	uint8_t read[2];
	if (!i2c_task_read_data(send, sizeof(send), read, sizeof(uint16_t)))
		return false;

	*received = UINT16_FROM_LE_BYTES(read[0], read[1]);
	return true;
}

static bool i2c_bq25720_write_2_registers(uint8_t reg, uint16_t value)
{
	uint8_t data[] = { reg, UINT32_0B(value), UINT32_1B(value) };
	return i2c_task_write_data(data, sizeof(data));
}

	/// read and write registers
bool i2c_bq25720_read_charge_option0(union charge_option0_t *charge_option0)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEOPTION0, &charge_option0->data16);
}

bool i2c_bq25720_write_charge_option0(union charge_option0_t *charge_option0)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEOPTION0, charge_option0->data16);
}

bool i2c_bq25720_read_charge_current(uint16_t *current_ma)  /// max 8192mA, resolution 64mA, on 10mOhm R
{
	uint16_t a;
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_CHARGECURRENT, &a);
	*current_ma = a & 0x1fe0;
	return ok;
}

bool i2c_bq25720_write_charge_current(uint16_t current_ma)  /// max 8192mA, resolution 64mA, on 10mOhm R
{
	if (current_ma > 8192)
		return false;

	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGECURRENT, current_ma);
}

bool i2c_bq25720_read_charge_voltage(uint16_t *charge_voltage)  /// 1024-19200mV, 8mV resolution, default 4.2V for 1s, 8.4V for 2s, 12.6V for 3s, 16.8V for 4s
{
	uint16_t a;
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEVOLTAGE, &a);
	*charge_voltage = a & 0x7ff8;
	return ok;
}

bool i2c_bq25720_write_charge_voltage(uint16_t charge_voltage)  /// 1024-19200mV, 8mV resolution, default 4.2V for 1s, 8.4V for 2s, 12.6V for 3s, 16.8V for 4s
{
	if (charge_voltage < 1024 || charge_voltage > 19200)
		return false;

	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEVOLTAGE, charge_voltage);
}

bool i2c_bq25720_read_charger_status(union charger_status_t *charger_status)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGERSTATUS, &charger_status->data16);
}

bool i2c_bq25720_write_charger_status(union charger_status_t *charger_status)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGERSTATUS, charger_status->data16);
}

bool i2c_bq25720_read_prochot_status(union prochot_status_t *prochot_status)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_PROCHOTSTATUS, &prochot_status->data16);
}

bool i2c_bq25720_write_prochot_status(union prochot_status_t *prochot_status)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_PROCHOTSTATUS, prochot_status->data16);
}

bool i2c_bq25720_read_iin_dpm(uint16_t *iin_dpm)  /// actual input current limit, 50-6350mA, 50mA resolution, on 10mOhm R
{
	uint16_t a;	
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_IIN_DPM, &a);
	*iin_dpm = (a >> 8) * 50;
	return ok;
}

bool i2c_bq25720_read_adcvbus_psys(union adcvbus_psys_t *adcvbus_psys)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_ADCVBUS_PSYS, &adcvbus_psys->data16);
}

bool i2c_bq25720_read_adcibat(union adcibat_t *adcibat)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_ADCIBAT, &adcibat->data16);
}

bool i2c_bq25720_read_adciincmpin(union adciincmpin_t *adciincmpin)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_ADCIINCMPIN, &adciincmpin->data16);
}

bool i2c_bq25720_read_adcvsysvbat(union adcvsysvbat_t *adcvsysvbat)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_ADCVSYSVBAT, &adcvsysvbat->data16);
}

bool i2c_bq25720_read_charge_option1(union charge_option1_t *charge_option1)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEOPTION1, &charge_option1->data16);
}

bool i2c_bq25720_write_charge_option1(union charge_option1_t *charge_option1)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEOPTION1, charge_option1->data16);
}

bool i2c_bq25720_read_charge_option2(union charge_option2_t *charge_option2)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEOPTION2, &charge_option2->data16);
}

bool i2c_bq25720_write_charge_option2(union charge_option2_t *charge_option2)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEOPTION2, charge_option2->data16);
}

bool i2c_bq25720_read_charge_option3(union charge_option3_t *charge_option3)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEOPTION3, &charge_option3->data16);
}

bool i2c_bq25720_write_charge_option3(union charge_option3_t *charge_option3)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEOPTION3, charge_option3->data16);
}

bool i2c_bq25720_read_prochot_option0(union prochot_option0_t *prochot_option0)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_PROCHOTOPTION0, &prochot_option0->data16);
}

bool i2c_bq25720_write_prochot_option0(union prochot_option0_t *prochot_option0)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_PROCHOTOPTION0, prochot_option0->data16);
}

bool i2c_bq25720_read_prochot_option1(union prochot_option1_t *prochot_option1)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_PROCHOTOPTION1, &prochot_option1->data16);
}

bool i2c_bq25720_write_prochot_option1(union prochot_option1_t *prochot_option1)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_PROCHOTOPTION1, prochot_option1->data16);
}

bool i2c_bq25720_read_adc_option(union adc_option_t *adc_option)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_ADCOPTION, &adc_option->data16);
}

bool i2c_bq25720_write_adc_option(union adc_option_t *adc_option)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_ADCOPTION, adc_option->data16);
}

bool i2c_bq25720_read_charge_option4(union charge_option4_t *charge_option4)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_CHARGEOPTION4, &charge_option4->data16);
}

bool i2c_bq25720_write_charge_option4(union charge_option4_t *charge_option4)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_CHARGEOPTION4, charge_option4->data16);
}

bool i2c_bq25720_read_vmin_active_protection(union vmin_active_protection_t *vmin_active_protection)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_VMINACTIVEPROTECTION, &vmin_active_protection->data16);
}

bool i2c_bq25720_write_vmin_active_protection(union vmin_active_protection_t *vmin_active_protection)
{
	return i2c_bq25720_write_2_registers(BQ25720_REG_VMINACTIVEPROTECTION, vmin_active_protection->data16);
}

bool i2c_bq25720_read_input_voltage(uint16_t *input_voltage)  /// 64-16383mV, 64mV resolution, 1.28V default
{
	uint16_t a;
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_INPUTVOLTAGE, &a);
	*input_voltage = a & 0x3fc0;
	return ok;
}

bool i2c_bq25720_write_input_voltage(uint16_t input_voltage)  /// 64-16383mV, 64mV resolution, 1.28V default
{
	if (input_voltage < 64 || input_voltage > 16384)
		return false;

	return i2c_bq25720_write_2_registers(BQ25720_REG_INPUTVOLTAGE, input_voltage);
}

bool i2c_bq25720_read_vsys_min(uint16_t *vsys_min)   /// 1-19.2V, 100mV resolution, 3.6V for 1s (1 cell), 6.6V for 2s, 9.2V for 3s, 12.3V for 4s
{
	uint16_t a;
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_VSYS_MIN, &a);
	*vsys_min = (a >> 8) * 100;
	return ok;
}

bool i2c_bq25720_write_vsys_min(uint16_t vsys_min)   /// 1-19.2V, 100mV resolution, 3.6V for 1s (1 cell), 6.6V for 2s, 9.2V for 3s, 12.3V for 4s
{
	if (vsys_min < 1000 || vsys_min > 19200)
		return false;

	uint16_t a = (vsys_min / 100) << 8;
	return i2c_bq25720_write_2_registers(BQ25720_REG_VSYS_MIN, a);
}

bool i2c_bq25720_read_iin_host(uint16_t *iin_host)   /// 50-6350mA, 50mA resolution, 3.25A default, for R=10mOhm
{
	uint16_t a;
	bool ok = i2c_bq25720_read_2_registers(BQ25720_REG_IIN_HOST, &a);
	*iin_host = (a >> 8) * 50;
	return ok;
}

bool i2c_bq25720_write_iin_host(uint16_t iin_host)   /// 50-6350mA, 50mA resolution, 3.25A default, for R=10mOhm
{
	if (iin_host < 50 || iin_host > 6350)
		return false;

	uint16_t a = (iin_host / 50) << 8;
	return i2c_bq25720_write_2_registers(BQ25720_REG_IIN_HOST, a);
}

bool i2c_bq25720_read_manufacturer_id(uint16_t *manufacturer_id)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_MANUFACTURERID, manufacturer_id);
}

bool i2c_bq25720_read_device_id(uint16_t *device_id)
{
	return i2c_bq25720_read_2_registers(BQ25720_REG_DEVICEID, device_id);
}
