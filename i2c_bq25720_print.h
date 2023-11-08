extern void i2c_bq25720_print_charge_option0(union charge_option0_t *charge_option0);
extern void i2c_bq25720_print_charge_current(uint16_t current_ma);  /// max 8192mA, resolution 64mA, on 10mOhm R
extern void i2c_bq25720_print_charge_voltage(uint16_t charge_voltage);  /// 1024-19200mV, 8mV resolution
extern void i2c_bq25720_print_charger_status(union charger_status_t *charger_status);
extern void i2c_bq25720_print_prochot_status(union prochot_status_t *prochot_status);
extern void i2c_bq25720_print_iin_dpm(uint16_t iin_dpm);  /// actual input current limit, 50-6350mA, 50mA resolution, on 10mOhm R
extern void i2c_bq25720_print_adcvbus_psys(union adcvbus_psys_t *adcvbus_psys);
extern void i2c_bq25720_print_adcibat(union adcibat_t *adcibat);
extern void i2c_bq25720_print_adciincmpin(union adciincmpin_t *adciincmpin);
extern void i2c_bq25720_print_adcvsysvbat(union adcvsysvbat_t *adcvsysvbat);
extern void i2c_bq25720_print_charge_option1(union charge_option1_t *charge_option1);
extern void i2c_bq25720_print_charge_option2(union charge_option2_t *charge_option2);
extern void i2c_bq25720_print_charge_option3(union charge_option3_t *charge_option3);
extern void i2c_bq25720_print_prochot_option0(union prochot_option0_t *prochot_option0);
extern void i2c_bq25720_print_prochot_option1(union prochot_option1_t *prochot_option1);
extern void i2c_bq25720_print_adc_option(union adc_option_t *adc_option);
extern void i2c_bq25720_print_charge_option4(union charge_option4_t *charge_option4);
extern void i2c_bq25720_print_vmin_active_protection(union vmin_active_protection_t *vmin_active_protection);
extern void i2c_bq25720_print_input_voltage(uint16_t input_voltage);  /// 64-16383mV, 64mV resolution, 1.28V default
extern void i2c_bq25720_print_vsys_min(uint16_t vsys_min);
extern void i2c_bq25720_print_iin_host(uint16_t iin_host);
extern void i2c_bq25720_print_manufacturer_id(uint16_t manufacturer_id);
extern void i2c_bq25720_print_device_id(uint16_t device_id);
