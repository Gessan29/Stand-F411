/*
 * Файл с функциями непосредственной проверки контрольных точек и ключевых элементов
 *
 *
 *
 */
 #include "hardware.h"
#include <stdint.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;

uint16_t vol, tok;

void test_voltage(uint8_t* buf){
	if (HAL_ADC_PollForConversion(ADC_1, HAL_MAX_DELAY) != HAL_OK) {
	    buf[0] = STATUS_EXEC_ERROR;
	} else {
	    vol = HAL_ADC_GetValue(ADC_1);
	    HAL_ADC_Stop(ADC_1);
	    vol = vol * 3300 / 4095;

	    buf[1] = (uint8_t)(vol & 0xFF);
	    buf[2] = (uint8_t)((vol >> 8) & 0xFF);
	    buf[0] = STATUS_OK;
	}
			return;
}

void apply_voltage_relay_1(uint8_t* buf) // Подставить нужный пин, сейчас PB9
{
	switch (buf[1]) {
		case 0:
			SET_BIT(RELAY_PORT->BSRR, RELAY_1_PIN_0);
			if (READ_BIT(RELAY_PORT->IDR, RELAY_1_PIN_0) != 0){
					buf[0] = STATUS_EXEC_ERROR;
				} else {
				    buf[0] = STATUS_OK;
				}
			return;
		case 1:
			SET_BIT(RELAY_PORT->BSRR, RELAY_1_PIN_1);
			if (READ_BIT(RELAY_PORT->IDR, RELAY_1_PIN_1) != 0){
					buf[0] = STATUS_OK;
				} else {
				    buf[0] = STATUS_EXEC_ERROR;
				}
			return;
		default:
			buf[0] = STATUS_INVALID_CMD;
			return;
	}
}

void test_voltage_4_point(uint8_t* buf)
{
	switch (buf[1])
	{
	case 1:
		test_voltage(buf);
		return;

	case 2:
		test_voltage(buf);
				return;

	case 3:
		test_voltage(buf);
				return;

	case 4:
		test_voltage(buf);
				return;
	default:
		buf[0] = STATUS_INVALID_CMD;
		return;
	}
}

void test_voltage_current(uint8_t* buf)
{
	switch (buf[1])
	{
	case 0: // voltage
		test_voltage(buf);
				return;

	case 1: // current
		if (HAL_ADC_PollForConversion(ADC_1, HAL_MAX_DELAY) != HAL_OK) {
		    buf[0] = STATUS_EXEC_ERROR;
		} else {
		uint16_t res_shunt = 100; // шунтирующий резистор для измерения тока 0.1 Om == 100 mOm
								vol = HAL_ADC_GetValue(ADC_1);
								HAL_ADC_Stop(ADC_1);
								vol = vol * 3300 / 4095;
								tok = vol / res_shunt;
								buf[1] = (uint8_t)(tok & 0xFF);
								buf[2] = (uint8_t)(tok >> 8 & 0xFF);
								buf[0] = STATUS_OK;
								return;
		}
	default:
		buf[0] = STATUS_INVALID_CMD;
		return;
	}
}

void apply_voltage_relay_2(uint8_t* buf) //Подставить нужный пин, сейчас PB8
{
	switch (buf[1]) {
			case 0:
				SET_BIT(RELAY_PORT->BSRR, RELAY_2_PIN_0);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_2_PIN_0) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case 1:
				SET_BIT(RELAY_PORT->BSRR, RELAY_2_PIN_1);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_2_PIN_1) != 0){
						buf[0] = STATUS_OK;
					} else {
					    buf[0] = STATUS_EXEC_ERROR;
					}
				return;
			default:
				buf[0] = STATUS_INVALID_CMD;
				return;
		}
}

void test_voltage_11_point(uint8_t* buf)
{
	switch (buf[1])
	{
	case 0:
		test_voltage(buf);
				return;

	case 1:
		test_voltage(buf);
				return;

	case 2:
		test_voltage(buf);
				return;

	case 3:
		test_voltage(buf);
				return;

	case 4:
		test_voltage(buf);
				return;

	case 5:
		test_voltage(buf);
				return;

	case 6:
		test_voltage(buf);
				return;


	case 7:
		test_voltage(buf);
				return;

	case 8:
		test_voltage(buf);
				return;

	case 9:
		test_voltage(buf);
				return;

	case 10:
		test_voltage(buf);
				return;

	default:
		buf[0] = STATUS_INVALID_CMD;
		return;
	}
}

void test_corrent_laser(uint8_t* buf)
{
	if (HAL_ADC_PollForConversion(ADC_1, HAL_MAX_DELAY) != HAL_OK) {
	    buf[0] = STATUS_EXEC_ERROR;
	    return;
	} else {
	uint16_t adcSamples[100];
		for (int i = 0; i < 100; i++){
			while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {}
			    adcSamples[i] = HAL_ADC_GetValue(ADC_1);
			    LL_ADC_ClearFlag_EOCS(ADC1);
		}
		  HAL_ADC_Stop(ADC_1);
		for (int i = 0; i < 100; i++){
			    		  vol = adcSamples[i] * 3300 / 4095;
			    		  buf[i * 2 + 1] = (uint8_t)(vol & 0xFF);
			    		  buf[i * 2 + 2] = (uint8_t)(vol >> 8 & 0xFF);
		}
	buf[0] = STATUS_OK;
	}
}

void test_voltage_peltie(uint8_t* buf)
{
	test_voltage(buf);
			return;
}

void apply_voltage_relay_5(uint8_t* buf) //Подставить нужный пин, сейчас PB7
{
	switch (buf[1]) {
			case 0:
				SET_BIT(RELAY_PORT->BSRR, RELAY_5_PIN_0);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_5_PIN_0) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case 1:
				SET_BIT(RELAY_PORT->BSRR, RELAY_5_PIN_1);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_5_PIN_1) != 0){
						buf[0] = STATUS_OK;
					} else {
					    buf[0] = STATUS_EXEC_ERROR;
					}
				return;
			default:
				buf[0] = STATUS_INVALID_CMD;
				return;
		}
}

void massage_rs232(uint8_t* buf)
{
	for (int a = 1; a < 5; a++) {
		buf[a] = 5;
	}
	buf[0] = STATUS_OK;
}

void massage_gps(uint8_t* buf)
{
	uint8_t GPS [] = "$GNGLL,5502.49000,N,08256.07600,E,1235  .000,A,A*\r\n"; // GLL, version 4.1 and 4.2, NMEA 0183
	GPS[38] = (buf[1]/ 10) + '0';
	GPS[39] = (buf[1] % 10) + '0';
	buf[0] = STATUS_OK;
}


