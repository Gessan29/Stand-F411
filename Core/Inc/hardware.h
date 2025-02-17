/*
 * hardware.h
 *
 *  Created on: Feb 7, 2025
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "parser.h"

#define RELAY_PORT GPIOB
#define RELAY_1_PIN_1 (1 << 9)
#define RELAY_1_PIN_0 (0 << 9)
#define RELAY_2_PIN_1 (1 << 8)
#define RELAY_2_PIN_0 (0 << 8)
#define RELAY_5_PIN_1 (1 << 7)
#define RELAY_5_PIN_0 (0 << 7)
#define ADC_1 &hadc1

void test_voltage(uint8_t* buf);

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
