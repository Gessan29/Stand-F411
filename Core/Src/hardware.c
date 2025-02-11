/*
 * Файл с функциями непосредственной проверки контрольных точек и ключевых элементов
 *
 *
 *
 */
 #include "hardware.h"
#include <stdint.h>
#include <string.h>
uint16_t voltage_raw;
float voltage;

void func_0(uint8_t* buf) // Подставить нужный пин, сейчас PB9
{
	switch (buf[1]) {
		case 0:
			SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR9);
			if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID9) != 0){
					buf[0] = STATUS_EXEC_ERROR;
				} else {
				    buf[0] = STATUS_OK;
				}
			return;
		case 1:
			SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS9);
			if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID9) != 0){
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

void func_1(uint8_t* buf)
{
	switch (buf[1])
	{
	case 1:
		voltage_raw = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
		voltage = voltage_raw * 3.3 / 4095;
		voltage_raw = (uint16_t*)voltage;
		buf[1] = (uint8_t)(voltage_raw & 0xFF);
		buf[2] = (uint8_t)(voltage_raw >> 8 & 0xFF);
		buf[0] = STATUS_OK;;
		return;

	case 2:
		voltage = 330;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 3:
		voltage = 500;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 4:
		voltage = 600;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	default:
		buf[0] = STATUS_INVALID_CMD;
		break;
	}
}

void func_2(uint8_t* buf)
{
	switch (buf[1])
	{
	case 0: // voltage
		voltage = 1200;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 1: // current
		voltage = 500;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	default:
		buf[0] = STATUS_INVALID_CMD;
		break;
	}
}

void func_3(uint8_t* buf) //Подставить нужный пин, сейчас PB8
{
	switch (buf[1]) {
			case 0:
				SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR8);
				if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID8) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case 1:
				SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS8);
				if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID8) != 0){
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

void func_4(uint8_t* buf)
{
	switch (buf[1])
	{
	case 0:
		voltage = 120;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	case 1:
		voltage = 180;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 2:
		voltage = 250;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 3:
		voltage = 550;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 4:
		voltage = 450;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	case 5:
		voltage = 550;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 6:
		voltage = 550;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 7:
		voltage = 180;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 8:
		voltage = 250;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	case 9:
		voltage = 500;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;

	case 10:
		voltage = 2048;
		buf[1] = (uint8_t)(voltage & 0xFF);
		buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
		buf[0] = STATUS_OK;
		break;
	default:
		buf[0] = STATUS_INVALID_CMD;
		break;
	}
}

void func_5(uint8_t* buf)
{
	voltage = 0;
	for (size_t i = 1; i < 201; i += 2)
	{
		buf[i] = (uint8_t)(voltage & 0xFF);
		buf[i + 1] = (uint8_t)(voltage >> 8 & 0xFF);
		voltage += 10;
    }
	buf[0] = STATUS_OK;

}

void func_6(uint8_t* buf)
{
	voltage = 550;
	buf[1] = (uint8_t)(voltage & 0xFF);
	buf[2] = (uint8_t)(voltage >> 8 & 0xFF);
	buf[0] = STATUS_OK;
}

void func_7(uint8_t* buf) //Подставить нужный пин, сейчас PB7
{
	switch (buf[1]) {
			case 0:
				SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR7);
				if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID7) != 0){
						buf[0] = STATUS_EXEC_ERROR;
					} else {
					    buf[0] = STATUS_OK;
					}
				return;
			case 1:
				SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
				if (READ_BIT(GPIOB->IDR, GPIO_IDR_ID7) != 0){
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

void func_8(uint8_t* buf)
{
	for (int a = 1; a < 5; a++) {
		buf[a] = 0;
	}
	buf[0] = STATUS_OK;
}

void func_9(uint8_t* buf)
{
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	buf[0] = STATUS_OK;
}


