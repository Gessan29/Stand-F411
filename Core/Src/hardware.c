/*
 * Файл с функциями непосредственной проверки контрольных точек и ключевых элементов
 */
 #include "hardware.h"
#include <stdint.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;
uint16_t vol_raw, vol_average, tok;

void test_voltage(uint8_t* buf){
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, TIME) != HAL_OK) {
	    buf[0] = STATUS_EXEC_ERROR;
	} else {
		vol_average = 0;
		for (int i = 0; i < SAMPLES; i++){
			while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {}
							LL_ADC_ClearFlag_EOCS(ADC1);
						    vol_raw = HAL_ADC_GetValue(&hadc1);
						    vol_average += vol_raw;
		}
	    HAL_ADC_Stop(&hadc1);
	    vol_average = vol_average * REFERENCE_VOLTAGE / (ADC_BIT_RATE * SAMPLES);

	    buf[1] = (uint8_t)(vol_average & 0xFF);
	    buf[2] = (uint8_t)((vol_average >> 8) & 0xFF);
	    buf[0] = STATUS_OK;
	}
			return;
}

void apply_relay(GPIO_TypeDef *PORT, uint32_t PIN){
	            return(SET_BIT(PORT->BSRR, PIN));
}

void apply_voltage_relay_1(uint8_t* buf) // Подставить нужный пин, сейчас PB9
{
	switch (buf[1]) {
		case CLOSE_RELAY:
			apply_relay(RELAY_PORT, RELAY_1_PIN_0);
			if (READ_BIT(RELAY_PORT->IDR, RELAY_1_PIN_1) != 0){
								buf[0] = STATUS_EXEC_ERROR;
							} else {
							    buf[0] = STATUS_OK;
							}
			return;
		case OPEN_RELAY:
			apply_relay(RELAY_PORT, RELAY_1_PIN_1);
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
	case CHECKPOINT_6V_NEG:
		test_voltage(buf);
		return;

	case CHECKPOINT_3_3V:
		test_voltage(buf);
				return;

	case CHECKPOINT_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_6V:
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
	case SYPPLY_VOLTAGE:
		test_voltage(buf);
				return;

	case SUPPLY_CURRENT:
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, TIME) != HAL_OK) {
		    buf[0] = STATUS_EXEC_ERROR;
		    return;
		} else {
		vol_average = 0;
		uint16_t res_shunt = RES_SHUNT; // шунтирующий резистор для измерения тока 0.1 Om == 100 mOm
		for (int i = 0; i < SAMPLES; i++){
			while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {}
										LL_ADC_ClearFlag_EOCS(ADC1);
									    vol_raw = HAL_ADC_GetValue(&hadc1);
									    vol_average += vol_raw;
		}
								HAL_ADC_Stop(&hadc1);
								vol_average = vol_average * REFERENCE_VOLTAGE / (ADC_BIT_RATE * SAMPLES);
								tok = vol_average / res_shunt;
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
			case CLOSE_RELAY:
				apply_relay(RELAY_PORT, RELAY_2_PIN_0);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_2_PIN_1) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case OPEN_RELAY:
				apply_relay(RELAY_PORT, RELAY_2_PIN_1);
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
	case CHECKPOINT_1_2V:
		test_voltage(buf);
				return;

	case CHECKPOINT_1_8V:
		test_voltage(buf);
				return;

	case CHECKPOINT_2_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_GPS_5_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_VREF_ADC_4_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_5_5VA:
		test_voltage(buf);
				return;

	case CHECKPOINT_5_5VA_NEG:
		test_voltage(buf);
				return;


	case CHECKPOINT_1_8VA:
		test_voltage(buf);
				return;

	case CHECKPOINT_OFFSET_2_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_LASER_5V:
		test_voltage(buf);
				return;

	case CHECKPOINT_VREF_DAC_2_048V:
		test_voltage(buf);
				return;

	default:
		buf[0] = STATUS_INVALID_CMD;
		return;
	}
}

void test_corrent_laser(uint8_t* buf)
{
	uint16_t adcSamples[SAMPLES_LASER];
	HAL_ADC_Start(&hadc1);
		for (int i = 0; i < SAMPLES_LASER; i++){
			while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {}
					LL_ADC_ClearFlag_EOCS(ADC1);
					adcSamples[i] = HAL_ADC_GetValue(&hadc1);
		}
	HAL_ADC_Stop(&hadc1);
		for (int i = 0; i < SAMPLES_LASER; i++){
			    		  vol_average = adcSamples[i] * REFERENCE_VOLTAGE / ADC_BIT_RATE;
			    		  buf[i * 2 + 1] = (uint8_t)(vol_average & 0xFF);
			    		  buf[i * 2 + 2] = (uint8_t)(vol_average >> 8 & 0xFF);
		}
	buf[0] = STATUS_OK;
}

void test_voltage_peltie(uint8_t* buf)
{
	test_voltage(buf);
			return;
}

void apply_voltage_relay_5(uint8_t* buf) //Подставить нужный пин, сейчас PB7
{
	switch (buf[1]) {
			case CLOSE_RELAY:
				apply_relay(RELAY_PORT, RELAY_5_PIN_0);
				if (READ_BIT(RELAY_PORT->IDR, RELAY_5_PIN_1) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case OPEN_RELAY:
				apply_relay(RELAY_PORT, RELAY_5_PIN_1);
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

int compare_arrays(uint8_t arr1[], uint8_t arr2[], size_t size){
	for(int i = 0; i < size; i++){
		if (arr1[i] != arr2[i]){
			return 1;
		}
	}
	return 0;
}

void massage_rs232(uint8_t* buf)
{
	uint8_t rs_232_tx [RS_232] = "RS_232!";
	uint8_t rs_232_rx [RS_232];
	HAL_UART_Transmit(UART_1, rs_232_tx, RS_232, HAL_MAX_DELAY);//TIMEOUT_RX
	HAL_UART_Receive(UART_1, rs_232_rx, RS_232, HAL_MAX_DELAY);// TIMEOUT_RX
	if (compare_arrays(rs_232_tx, rs_232_rx, RS_232) == 0){
		buf[0] = STATUS_OK;
	}
	else {
		buf[0] = STATUS_EXEC_ERROR;
	}
}

void massage_gps(uint8_t* buf)
{
	uint8_t GPS_tx [GPS_SIZE] = "$GNGLL,5502.49000,N,08256.07600,E,1235  .000,A,A*"; // GLL, version 4.1 and 4.2, NMEA 0183
	uint8_t GPS_rx [GPS_SIZE];
	GPS_tx[38] = (buf[1]/ 10) + '0';
	GPS_tx[39] = (buf[1] % 10) + '0';
	HAL_UART_Transmit(UART_1, GPS_tx, GPS_SIZE, HAL_MAX_DELAY);// TIMEOUT_RX
	HAL_UART_Receive(UART_1, GPS_rx, GPS_SIZE, HAL_MAX_DELAY);// TIMEOUT_RX
	if (compare_arrays(GPS_tx, GPS_rx, GPS_SIZE) == 0){
			buf[0] = STATUS_OK;
		}
		else {
			buf[0] = STATUS_EXEC_ERROR;
		}
}


