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
#include "stm32f4xx_hal.h"

// директивы реле:
#define CLOSE_RELAY 0
#define OPEN_RELAY 1

// директивы 4 контрольных точек (test_voltage_4_point):
#define CHECKPOINT_6V_NEG 1
#define CHECKPOINT_3_3V 2
#define CHECKPOINT_5V 3
#define CHECKPOINT_6V 4

// директивы измерения тока или напряжения (test_voltage_current):
#define SYPPLY_VOLTAGE 0
#define SUPPLY_CURRENT 1

// директивы 11 контрольных точек (test_voltage_11_point):
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

//директивы настройки параметров

// директивы установки битов GPIO (для реле):
#define RELAY_1_PIN_1 (1 << 9) // PB9
#define RELAY_1_PIN_0 (1 << 25)

#define RELAY_2_PIN_1 (1 << 8) // PB8
#define RELAY_2_PIN_0 (1 << 24)

#define RELAY_5_PIN_1 (1 << 7) // PB7
#define RELAY_5_PIN_0 (1 << 23)

// директивы каналов АЦП
#define ADC_MUX ADC_CHANNEL_0 // Канал АЦП для мультиплексора 1:16.
#define ADC_SYPPLY_VOLTAGE ADC_CHANNEL_1 // Канал АЦП для измерения напряжения питания.
#define ADC_SUPPLY_CURRENT ADC_CHANNEL_4 // Канал АЦП для измерения тока питания.
#define ADC_LASER ADC_CHANNEL_5 // Канал АЦП для измерения формы тока лазерного диода.
#define ADC_PELTIE ADC_CHANNEL_6 // Канал АЦП для измерения напряжения элемента Пельтье.

#define RELAY_PORT GPIOB // выбор порта ножек GPIO для реле
#define REFERENCE_VOLTAGE 3300 // опорное напряжение, мВ.
#define ADC_BIT_RATE 4095 // разрешение АЦП.
#define RES_SHUNT 100 // номинал шунтирующего резистора, мОм.
#define SAMPLES_LASER 100 // кол-во измерений сигнала лазерного диода.
#define SAMPLES 100 // кол-во измерений контрольной точки.
#define TIMEOUT_RX HAL_MAX_DELAY // время передачи пакета команды
#define TIME_ADC HAL_MAX_DELAY // время измерения АЦП, мс.
#define UART_USB huart1 // для выбора uart.
#define UART_RS_232 huart1 // для выбора uart.
#define UART_GPS huart1 // для выбора uart.
#define RS_232 7 // размер передаваемого массива функции massage_rs232.
#define GPS_SIZE 49 // размер передаваемого массива функции massage_gps.

// функции подсчета переменных:
void test_voltage(uint8_t* buf, uint32_t channel); // снимает напряжение с контрольной точки.
void apply_relay(GPIO_TypeDef *PORT, uint32_t PIN); // выставляет лог. 0 или лог. 1 на ножку GPIO (Для реле).
int compare_arrays(uint8_t arr1[], uint8_t arr2[], size_t size); // для сравнения "эталонного" массива с полученным массивом.
void uart_tx_rx(UART_HandleTypeDef* uart, uint8_t* buf, uint8_t* tx, uint8_t* rx, size_t size); // для передачи/приема байт по uart.

// управляющие функции:
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
