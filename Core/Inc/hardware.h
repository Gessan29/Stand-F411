/*
 * hardware.h
 *
 *  Created on: Feb 7, 2025
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "parser.h"
#include "stm32f411xe.h"
#define CLOSE_RELAY 0
#define OPEN_RELAY 1
#define CHECKPOINT_6V_NEG 1
#define CHECKPOINT_3_3V 2
#define CHECKPOINT_5V 3
#define CHECKPOINT_6V 4
#define RELAY_PORT GPIOB
#define RELAY_1_PIN_1 (1 << 9)
#define RELAY_1_PIN_0 (1 << 25)
#define RELAY_2_PIN_1 (1 << 8)
#define RELAY_2_PIN_0 (1 << 24)
#define RELAY_5_PIN_1 (1 << 7)
#define RELAY_5_PIN_0 (1 << 23)
#define SYPPLY_VOLTAGE 0
#define SUPPLY_CURRENT 1
#define CHECKPOINT_1_2V 0
#define CHECKPOINT_1_8V 1
#define CHECKPOINT_2_5V 2
#define CHECKPOINT_GPS_5_5V 3
#define CHECKPOINT_VREF_ADC_4_5V 4
#define CHECKPOINT_5_5VA 5
#define CHECKPOINT_5_5VA_NEG 6
#define CHECKPOINT_1_8VA 7
#define CHECKPOINT_OFFSET_2_5V 8
#define CHECKPOINT_LASER_5V 9
#define CHECKPOINT_VREF_DAC_2_048V 10
#define REFERENCE_VOLTAGE 3300
#define ADC_BIT_RATE 4095
#define RES_SHUNT 100
#define SAMPLES_LASER 100
#define SAMPLES 100
#define TIME 1000
#define UART_1 &huart1
#define UART_2 &huart2
#define UART_6 &huart6
#define RS_232 8
#define GPS_SIZE 49

void test_voltage(uint8_t* buf);
void apply_relay(GPIO_TypeDef *PORT, uint32_t PIN);
int compare_arrays(uint8_t arr1[], uint8_t arr2[], size_t size);

void apply_voltage_relay_1(uint8_t* buf);
void test_voltage_4_point(uint8_t* buf);
void test_voltage_current(uint8_t* buf);
void apply_voltage_relay_2(uint8_t* buf);
void test_voltage_11_point(uint8_t* buf);
void test_corrent_laser(uint8_t* buf);
void test_voltage_peltie(uint8_t* buf);
void apply_voltage_relay_5(uint8_t* buf);
void massage_rs232(uint8_t* buf);
void massage_gps(uint8_t* buf);

#endif /* INC_HARDWARE_H_ */
