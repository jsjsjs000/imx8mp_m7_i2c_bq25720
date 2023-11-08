#include <fsl_common.h>
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include "common.h"
#include "i2c_task.h"
#include "i2c_bq25720.h"
#include "i2c_bq25720_print.h"

void i2c_bq25720_print_charge_option0(union charge_option0_t *charge_option0)
{
	PRINTF("Charge option0: 0x%4x:\r\n", charge_option0->data16);
	PRINTF("  chrg_inhibit = %d\r\n", charge_option0->charge_option0.chrg_inhibit);
	PRINTF("  en_iin_dpm = %d\r\n", charge_option0->charge_option0.en_iin_dpm);
	PRINTF("  en_ldo = %d\r\n", charge_option0->charge_option0.en_ldo);
	PRINTF("  ibat_gain = %d\r\n", charge_option0->charge_option0.ibat_gain);
	PRINTF("  iadpt_gain = %d\r\n", charge_option0->charge_option0.iadpt_gain);
	PRINTF("  en_learn = %d\r\n", charge_option0->charge_option0.en_learn);
	PRINTF("  vsys_uvp_enz = %d\r\n", charge_option0->charge_option0.vsys_uvp_enz);
	PRINTF("  en_cmp_latch = %d\r\n", charge_option0->charge_option0.en_cmp_latch);
	PRINTF("  dis_strgrv = %d\r\n", charge_option0->charge_option0.dis_strgrv);
	PRINTF("  pwm_freq = %d\r\n", charge_option0->charge_option0.pwm_freq);
	PRINTF("  en_ooa = %d\r\n", charge_option0->charge_option0.en_ooa);
	PRINTF("  otg_on_chrgok = %d\r\n", charge_option0->charge_option0.otg_on_chrgok);
	PRINTF("  iin_dpm_auto_disable = %d\r\n", charge_option0->charge_option0.iin_dpm_auto_disable);
	switch (charge_option0->charge_option0.wdtmr_adj)
	{
		case 0:  PRINTF("  wdtmr_adj = disable_watchdog_timer\r\n"); break;
		case 1:  PRINTF("  wdtmr_adj = enabled_5sec\r\n"); break;
		case 2:  PRINTF("  wdtmr_adj = enabled_88sec\r\n"); break;
		case 3:  PRINTF("  wdtmr_adj = enable_watchdog_timer_175sec\r\n"); break;
		default: PRINTF("  wdtmr_adj = unknown\r\n");
	}
	PRINTF("  en_lwpwr = %d\r\n", charge_option0->charge_option0.en_lwpwr);
}

void i2c_bq25720_print_charge_current(uint16_t current_ma)  /// max 8192mA, resolution 64mA, on 10mOhm R
{
	PRINTF("Charge current: %dmA\r\n", current_ma);
}

void i2c_bq25720_print_charge_voltage(uint16_t charge_voltage)  /// 1024-19200mV, 8mV resolution
{
	PRINTF("Charge voltage: %dmV\r\n", charge_voltage);
}

void i2c_bq25720_print_charger_status(union charger_status_t *charger_status)
{
	PRINTF("Charger status: 0x%4x:\r\n", charger_status->data16);
	PRINTF("  stat_ac = %d\r\n", charger_status->charger_status.stat_ac);
	PRINTF("  ico_done = %d\r\n", charger_status->charger_status.ico_done);
	PRINTF("  in_vap = %d\r\n", charger_status->charger_status.in_vap);
	PRINTF("  in_vindpm = %d\r\n", charger_status->charger_status.in_vindpm);
	PRINTF("  in_iin_dpm = %d\r\n", charger_status->charger_status.in_iin_dpm);
	PRINTF("  in_fchrg = %d\r\n", charger_status->charger_status.in_fchrg);
	PRINTF("  in_pchrg = %d\r\n", charger_status->charger_status.in_pchrg);
	PRINTF("  in_otg = %d\r\n", charger_status->charger_status.in_otg);
	PRINTF("  fault_acov = %d\r\n", charger_status->charger_status.fault_acov);
	PRINTF("  fault_batoc = %d\r\n", charger_status->charger_status.fault_batoc);
	PRINTF("  fault_acoc = %d\r\n", charger_status->charger_status.fault_acoc);
	PRINTF("  fault_sysovp = %d\r\n", charger_status->charger_status.fault_sysovp);
	PRINTF("  fault_vsys_uvp = %d\r\n", charger_status->charger_status.fault_vsys_uvp);
	PRINTF("  fault_force_converter_off = %d\r\n", charger_status->charger_status.fault_force_converter_off);
	PRINTF("  fault_otg_ovp = %d\r\n", charger_status->charger_status.fault_otg_ovp);
	PRINTF("  fault_otg_uvp = %d\r\n", charger_status->charger_status.fault_otg_uvp);
}

void i2c_bq25720_print_prochot_status(union prochot_status_t *prochot_status)
{
	PRINTF("PROCHOT status: 0x%4x\r\n", prochot_status->data16);
	PRINTF("  stat_adapter_removal = %d\r\n", prochot_status->prochot_status.stat_adapter_removal);
	PRINTF("  stat_battery_removal = %d\r\n", prochot_status->prochot_status.stat_battery_removal);
	PRINTF("  stat_vsys = %d\r\n", prochot_status->prochot_status.stat_vsys);
	PRINTF("  stat_idchg1 = %d\r\n", prochot_status->prochot_status.stat_idchg1);
	PRINTF("  stat_inom = %d\r\n", prochot_status->prochot_status.stat_inom);
	PRINTF("  stat_icrit = %d\r\n", prochot_status->prochot_status.stat_icrit);
	PRINTF("  stat_comp = %d\r\n", prochot_status->prochot_status.stat_comp);
	PRINTF("  stat_vindpm = %d\r\n", prochot_status->prochot_status.stat_vindpm);
	PRINTF("  stat_exit_vap = %d\r\n", prochot_status->prochot_status.stat_exit_vap);
	PRINTF("  stat_vap_fail = %d\r\n", prochot_status->prochot_status.stat_vap_fail);
	PRINTF("  tshut = %d\r\n", prochot_status->prochot_status.tshut);
	PRINTF("  prochot_clear = %d\r\n", prochot_status->prochot_status.prochot_clear);
	switch (prochot_status->prochot_status.prochot_width)
	{
		case 0:  PRINTF("  prochot_width = 100us\r\n"); break;
		case 1:  PRINTF("  prochot_width = 1ms\r\n"); break;
		case 2:  PRINTF("  prochot_width = 5ms\r\n"); break;
		case 3:  PRINTF("  prochot_width = 10ms\r\n"); break;
		default: PRINTF("  prochot_width = unknown\r\n");
	}
	PRINTF("  en_prochot_ext = %d\r\n", prochot_status->prochot_status.en_prochot_ext);
}

void i2c_bq25720_print_iin_dpm(uint16_t iin_dpm)  /// actual input current limit, 50-6350mA, 50mA resolution, on 10mOhm R
{
	PRINTF("Iin dpm: %dmA\r\n", iin_dpm);
}

void i2c_bq25720_print_adcvbus_psys(union adcvbus_psys_t *adcvbus_psys)
{
	PRINTF("ADC Vbus psys: 0x%04d:\r\n", adcvbus_psys->data16);
	PRINTF("  input_voltage = %d\r\n", adcvbus_psys->adcvbus_psys.input_voltage);
	PRINTF("  system_power = %d\r\n", adcvbus_psys->adcvbus_psys.system_power);
}

void i2c_bq25720_print_adcibat(union adcibat_t *adcibat)
{
	PRINTF("ADC Ibat: 0x%04d:\r\n", adcibat->data16);
	PRINTF("  battery_discharge_current = %d\r\n", adcibat->adcibat.battery_discharge_current);
	PRINTF("  battery_charge_current = %d\r\n", adcibat->adcibat.battery_charge_current);
}

void i2c_bq25720_print_adciincmpin(union adciincmpin_t *adciincmpin)
{
	PRINTF("AdcIinCmpIn: 0x%04d:\r\n", adciincmpin->data16);
	PRINTF("  cmpin_voltage = %d\r\n", adciincmpin->adciincmpin.cmpin_voltage);
	PRINTF("  input_current = %d\r\n", adciincmpin->adciincmpin.input_current);
}

void i2c_bq25720_print_adcvsysvbat(union adcvsysvbat_t *adcvsysvbat)
{
	PRINTF("AdcVSysBat: 0x%04d:\r\n", adcvsysvbat->data16);
	PRINTF("  battery_voltage = %d\r\n", adcvsysvbat->adciincmpin.battery_voltage);
	PRINTF("  system_voltage = %d\r\n", adcvsysvbat->adciincmpin.system_voltage);
}

void i2c_bq25720_print_charge_option1(union charge_option1_t *charge_option1)
{
	PRINTF("Charge option1: 0x%04d:\r\n", charge_option1->data16);
	PRINTF("  auto_wakeup_en = %d\r\n", charge_option1->charge_option1.auto_wakeup_en);
	PRINTF("  en_ship_dchg = %d\r\n", charge_option1->charge_option1.en_ship_dchg);
	PRINTF("  en_ptm = %d\r\n", charge_option1->charge_option1.en_ptm);
	PRINTF("  force_conv_off = %d\r\n", charge_option1->charge_option1.force_conv_off);
	switch (charge_option1->charge_option1.cmp_deg)
	{
		case 0:  PRINTF("  cmp_deg = 5us\r\n"); break;
		case 1:  PRINTF("  cmp_deg = 2ms\r\n"); break;
		case 2:  PRINTF("  cmp_deg = 20ms\r\n"); break;
		case 3:  PRINTF("  cmp_deg = 5s\r\n"); break;
		default: PRINTF("  cmp_deg = unknown\r\n");
	}
	PRINTF("  cmp_pol = %d\r\n", charge_option1->charge_option1.cmp_pol);
	PRINTF("  cmp_ref = %d\r\n", charge_option1->charge_option1.cmp_ref);
	PRINTF("  en_fast_5mohm = %d\r\n", charge_option1->charge_option1.en_fast_5mohm);
	PRINTF("  psys_ratio = %d\r\n", charge_option1->charge_option1.psys_ratio);
	PRINTF("  rsns_rsr = %d\r\n", charge_option1->charge_option1.rsns_rsr);
	PRINTF("  rsns_rac = %d\r\n", charge_option1->charge_option1.rsns_rac);
	switch (charge_option1->charge_option1.psys_config)
	{
		case 0:  PRINTF("  psys_config = pbus_pbat\r\n"); break;
		case 1:  PRINTF("  psys_config = pbus\r\n"); break;
		case 2:  PRINTF("  psys_config = reserved\r\n"); break;
		case 3:  PRINTF("  psys_config = turn_off_psys\r\n"); break;
		default: PRINTF("  psys_config = unknown\r\n");
	}
	PRINTF("  en_prochot_lpwr = %d\r\n", charge_option1->charge_option1.en_prochot_lpwr);
	PRINTF("  en_ibat = %d\r\n", charge_option1->charge_option1.en_ibat);
}

void i2c_bq25720_print_charge_option2(union charge_option2_t *charge_option2)
{
	PRINTF("Charge option2: 0x%04d:\r\n", charge_option2->data16);
	PRINTF("  batoc_vth = %d\r\n", charge_option2->charge_option2.batoc_vth);
	PRINTF("  en_batoc = %d\r\n", charge_option2->charge_option2.en_batoc);
	PRINTF("  acoc_vth = %d\r\n", charge_option2->charge_option2.acoc_vth);
	PRINTF("  en_acoc = %d\r\n", charge_option2->charge_option2.en_acoc);
	PRINTF("  acx_ocp = %d\r\n", charge_option2->charge_option2.acx_ocp);
	PRINTF("  q2_ocp = %d\r\n", charge_option2->charge_option2.q2_ocp);
	PRINTF("  en_ichg_idchg = %d\r\n", charge_option2->charge_option2.en_ichg_idchg);
	PRINTF("  en_extilim = %d\r\n", charge_option2->charge_option2.en_extilim);
	switch (charge_option2->charge_option2.pkpwr_tmax)
	{
		case 0:  PRINTF("  pkpwr_tmax = 20ms\r\n"); break;
		case 1:  PRINTF("  pkpwr_tmax = 40ms\r\n"); break;
		case 2:  PRINTF("  pkpwr_tmax = 80ms\r\n"); break;
		case 3:  PRINTF("  pkpwr_tmax = 1s\r\n"); break;
		default: PRINTF("  pkpwr_tmax = unknown\r\n");
	}
	PRINTF("  stat_pkpwr_relax = %d\r\n", charge_option2->charge_option2.stat_pkpwr_relax);
	PRINTF("  stat_pkpwr_ovld = %d\r\n", charge_option2->charge_option2.stat_pkpwr_ovld);
	PRINTF("  en_pkpwr_vsys = %d\r\n", charge_option2->charge_option2.en_pkpwr_vsys);
	PRINTF("  en_pkpwr_iin_dpm = %d\r\n", charge_option2->charge_option2.en_pkpwr_iin_dpm);
	switch (charge_option2->charge_option2.pkpwr_tovld_deg)
	{
		case 0:  PRINTF("  pkpwr_tovld_deg = 1ms\r\n"); break;
		case 1:  PRINTF("  pkpwr_tovld_deg = 2ms\r\n"); break;
		case 2:  PRINTF("  pkpwr_tovld_deg = 5ms\r\n"); break;
		case 3:  PRINTF("  pkpwr_tovld_deg = 10ms\r\n"); break;
		default: PRINTF("  pkpwr_tovld_deg = unknown\r\n");
	}
}

void i2c_bq25720_print_charge_option3(union charge_option3_t *charge_option3)
{
	PRINTF("Charge option3: 0x%04d:\r\n", charge_option3->data16);
	PRINTF("  psys_otg_idchg = %d\r\n", charge_option3->charge_option3.psys_otg_idchg);
	PRINTF("  batfetoff_hiz = %d\r\n", charge_option3->charge_option3.batfetoff_hiz);
	PRINTF("  cmp_en = %d\r\n", charge_option3->charge_option3.cmp_en);
	switch (charge_option3->charge_option3.il_avg)
	{
		case 0:  PRINTF("  il_avg = 6a\r\n"); break;
		case 1:  PRINTF("  il_avg = 10a\r\n"); break;
		case 2:  PRINTF("  il_avg = 15a\r\n"); break;
		case 3:  PRINTF("  il_avg = disabled\r\n"); break;
		default: PRINTF("  il_avg = unknown\r\n");
	}
	PRINTF("  otg_vap_mode = %d\r\n", charge_option3->charge_option3.otg_vap_mode);
	PRINTF("  en_vbus_vap = %d\r\n", charge_option3->charge_option3.en_vbus_vap);
	PRINTF("  batfet_enz = %d\r\n", charge_option3->charge_option3.batfet_enz);
	PRINTF("  en_otg_bigcap = %d\r\n", charge_option3->charge_option3.en_otg_bigcap);
	PRINTF("  en_vsys_min_soft_sr = %d\r\n", charge_option3->charge_option3.en_vsys_min_soft_sr);
	PRINTF("  en_port_ctrl = %d\r\n", charge_option3->charge_option3.en_port_ctrl);
	PRINTF("  en_ico_mode = %d\r\n", charge_option3->charge_option3.en_ico_mode);
	PRINTF("  en_otg = %d\r\n", charge_option3->charge_option3.en_otg);
	PRINTF("  reset_vindpm = %d\r\n", charge_option3->charge_option3.reset_vindpm);
	PRINTF("  reset_reg = %d\r\n", charge_option3->charge_option3.reset_reg);
	PRINTF("  en_hiz = %d\r\n", charge_option3->charge_option3.en_hiz);
}

void i2c_bq25720_print_prochot_option0(union prochot_option0_t *prochot_option0)
{
	PRINTF("PROCHOT option0: 0x%04d:\r\n", prochot_option0->data16);
	PRINTF("  lower_prochot_vindpm = %d\r\n", prochot_option0->prochot_option0.lower_prochot_vindpm);
	PRINTF("  inom_deg = %d\r\n", prochot_option0->prochot_option0.inom_deg);
	PRINTF("  vsys_th1 = %d\r\n", prochot_option0->prochot_option0.vsys_th1);
	PRINTF("  prochot_vindpm_80_90 = %d\r\n", prochot_option0->prochot_option0.prochot_vindpm_80_90);
	switch (prochot_option0->prochot_option0.icrit_deg)
	{
		case 0:  PRINTF("  icrit_deg = 15us\r\n"); break;
		case 1:  PRINTF("  icrit_deg = 100us\r\n"); break;
		case 2:  PRINTF("  icrit_deg = 400us\r\n"); break;
		case 3:  PRINTF("  icrit_deg = 800us\r\n"); break;
		default: PRINTF("  icrit_deg = unknown\r\n");
	}
	PRINTF("  ilim2_vth = %d\r\n", prochot_option0->prochot_option0.ilim2_vth);
}

void i2c_bq25720_print_prochot_option1(union prochot_option1_t *prochot_option1)
{
	PRINTF("PROCHOT option1: 0x%04d:\r\n", prochot_option1->data16);
	PRINTF("  pp_acok = %d\r\n", prochot_option1->prochot_option1.pp_acok);
	PRINTF("  pp_batpres = %d\r\n", prochot_option1->prochot_option1.pp_batpres);
	PRINTF("  pp_vsys = %d\r\n", prochot_option1->prochot_option1.pp_vsys);
	PRINTF("  pp_idchg1 = %d\r\n", prochot_option1->prochot_option1.pp_idchg1);
	PRINTF("  pp_inom = %d\r\n", prochot_option1->prochot_option1.pp_inom);
	PRINTF("  pp_icrit = %d\r\n", prochot_option1->prochot_option1.pp_icrit);
	PRINTF("  pp_comp = %d\r\n", prochot_option1->prochot_option1.pp_comp);
	PRINTF("  pp_vindpm = %d\r\n", prochot_option1->prochot_option1.pp_vindpm);
	switch (prochot_option1->prochot_option1.idchg_deg1)
	{
		case 0:  PRINTF("  idchg_deg1 = 78ms\r\n"); break;
		case 1:  PRINTF("  idchg_deg1 = 1_25s\r\n"); break;
		case 2:  PRINTF("  idchg_deg1 = 5s\r\n"); break;
		case 3:  PRINTF("  idchg_deg1 = 20s\r\n"); break;
		default: PRINTF("  idchg_deg1 = unknown\r\n");
	}
	PRINTF("  idchg_th1 = %d\r\n", prochot_option1->prochot_option1.idchg_th1);
}

void i2c_bq25720_print_adc_option(union adc_option_t *adc_option)
{
	PRINTF("ADC option: 0x%04d:\r\n", adc_option->data16);
	PRINTF("  en_adc_vbat = %d\r\n", adc_option->adc_option.en_adc_vbat);
	PRINTF("  en_adc_vsys = %d\r\n", adc_option->adc_option.en_adc_vsys);
	PRINTF("  en_adc_ichg = %d\r\n", adc_option->adc_option.en_adc_ichg);
	PRINTF("  en_adc_idchg = %d\r\n", adc_option->adc_option.en_adc_idchg);
	PRINTF("  en_adc_iin = %d\r\n", adc_option->adc_option.en_adc_iin);
	PRINTF("  en_adc_psys = %d\r\n", adc_option->adc_option.en_adc_psys);
	PRINTF("  en_adc_vbus = %d\r\n", adc_option->adc_option.en_adc_vbus);
	PRINTF("  en_adc_cmpin = %d\r\n", adc_option->adc_option.en_adc_cmpin);
	PRINTF("  ptm_exit_light_load = %d\r\n", adc_option->adc_option.ptm_exit_light_load);
	PRINTF("  adc_fullscale = %d\r\n", adc_option->adc_option.adc_fullscale);
	PRINTF("  adc_start = %d\r\n", adc_option->adc_option.adc_start);
	PRINTF("  adc_conv = %d\r\n", adc_option->adc_option.adc_conv);
}

void i2c_bq25720_print_charge_option4(union charge_option4_t *charge_option4)
{
	PRINTF("Charge option4: 0x%04d:\r\n", charge_option4->data16);
	PRINTF("  stat_ptm = %d\r\n", charge_option4->charge_option4.stat_ptm);
	PRINTF("  stat_idchg2 = %d\r\n", charge_option4->charge_option4.stat_idchg2);
	PRINTF("  pp_idchg2 = %d\r\n", charge_option4->charge_option4.pp_idchg2);
	PRINTF("  idchg_th2 = %d\r\n", charge_option4->charge_option4.idchg_th2);
	switch (charge_option4->charge_option4.idchg_th2)
	{
		case 0:  PRINTF("  idchg_th2 = 125%\r\n"); break;
		case 1:  PRINTF("  idchg_th2 = 150%\r\n"); break;
		case 2:  PRINTF("  idchg_th2 = 175%\r\n"); break;
		case 3:  PRINTF("  idchg_th2 = 200%\r\n"); break;
		case 4:  PRINTF("  idchg_th2 = 250%\r\n"); break;
		case 5:  PRINTF("  idchg_th2 = 300%\r\n"); break;
		case 6:  PRINTF("  idchg_th2 = 350%\r\n"); break;
		case 7:  PRINTF("  idchg_th2 = 400%\r\n"); break;
		default: PRINTF("  idchg_th2 = unknown\r\n");
	}
	PRINTF("  idchg_deg2 = %d\r\n", charge_option4->charge_option4.idchg_deg2);
	switch (charge_option4->charge_option4.idchg_deg2)
	{
		case 0:  PRINTF("  idchg_deg2 = 100us\r\n"); break;
		case 1:  PRINTF("  idchg_deg2 = 1_6ms\r\n"); break;
		case 2:  PRINTF("  idchg_deg2 = 6ms\r\n"); break;
		case 3:  PRINTF("  idchg_deg2 = 12ms\r\n"); break;
		default: PRINTF("  idchg_deg2 = unknown\r\n");
	}
	PRINTF("  stat_vbus_vap = %d\r\n", charge_option4->charge_option4.stat_vbus_vap);
	PRINTF("  pp_vbus_vap = %d\r\n", charge_option4->charge_option4.pp_vbus_vap);
	PRINTF("  vsys_uvp_no_hiccup = %d\r\n", charge_option4->charge_option4.vsys_uvp_no_hiccup);
	PRINTF("  en_dither = %d\r\n", charge_option4->charge_option4.en_dither);
	switch (charge_option4->charge_option4.en_dither)
	{
		case 0:  PRINTF("  en_dither = disable\r\n"); break;
		case 1:  PRINTF("  en_dither = 1x\r\n"); break;
		case 2:  PRINTF("  en_dither = 2x\r\n"); break;
		case 3:  PRINTF("  en_dither = 3x\r\n"); break;
		default: PRINTF("  en_dither = unknown\r\n");
	}
	PRINTF("  vsys_uvp = %d\r\n", charge_option4->charge_option4.vsys_uvp);
	switch (charge_option4->charge_option4.vsys_uvp)
	{
		case 0:  PRINTF("  vsys_uvp = 2.4V\r\n"); break;
		case 1:  PRINTF("  vsys_uvp = 3.2V\r\n"); break;
		case 2:  PRINTF("  vsys_uvp = 4.0V\r\n"); break;
		case 3:  PRINTF("  vsys_uvp = 4.8V\r\n"); break;
		case 4:  PRINTF("  vsys_uvp = 5.6V\r\n"); break;
		case 5:  PRINTF("  vsys_uvp = 6.4V\r\n"); break;
		case 6:  PRINTF("  vsys_uvp = 7.2V\r\n"); break;
		case 7:  PRINTF("  vsys_uvp = 8.0V\r\n"); break;
		default: PRINTF("  vsys_uvp = unknown\r\n");
	}
}

void i2c_bq25720_print_vmin_active_protection(union vmin_active_protection_t *vmin_active_protection)
{
	PRINTF("Vmin active protection: 0x%04d:\r\n", vmin_active_protection->data16);
	PRINTF("  en_frs = %d\r\n", vmin_active_protection->vmin_active_protection.en_frs);
	PRINTF("  en_vsysth2_follow_vsysth1 = %d\r\n", vmin_active_protection->vmin_active_protection.en_vsysth2_follow_vsysth1);
	PRINTF("  vsys_th2 = %d\r\n", vmin_active_protection->vmin_active_protection.vsys_th2);
	PRINTF("  vbus_vap_th = %d\r\n", vmin_active_protection->vmin_active_protection.vbus_vap_th);
}

void i2c_bq25720_print_input_voltage(uint16_t input_voltage)  /// 64-16383mV, 64mV resolution, 1.28V default
{
	PRINTF("Input voltage limit: %dmV\r\n", input_voltage);
}

void i2c_bq25720_print_vsys_min(uint16_t vsys_min)
{
	PRINTF("Vsys min: %dmV\r\n", vsys_min);
}

void i2c_bq25720_print_iin_host(uint16_t iin_host)
{
	PRINTF("Iin host: %dmA\r\n", iin_host);
}

void i2c_bq25720_print_manufacturer_id(uint16_t manufacturer_id)
{
	PRINTF("Manufacturer ID (0x40): 0x%x\r\n", manufacturer_id);
}

void i2c_bq25720_print_device_id(uint16_t device_id)
{
	PRINTF("Device ID (0xe1): 0x%x\r\n", device_id);
}
