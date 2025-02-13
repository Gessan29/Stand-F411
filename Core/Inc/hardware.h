/*
 * hardware.h
 *
 *  Created on: Feb 7, 2025
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "parser.h"

#define RELAY_1_PORT GPIOB
#define RELAY_1_PIN (1 << 9)
#define RELAY_0_PIN (0 << 9)

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
