#ifndef BMS_H
#define BMS_H

#include <stdint.h>

#define CELL1_CHANNEL 0
#define CELL2_CHANNEL 1
#define CELL3_CHANNEL 4
#define CELL4_CHANNEL 6
#define CELL1_RESISTOR1 10000.0f
#define CELL1_RESISTOR2 22000.0f
#define CELL2_RESISTOR1 22000.0f
#define CELL2_RESISTOR2 10000.0f
#define CELL3_RESISTOR1 33000.0f
#define CELL3_RESISTOR2 10000.0f
#define CELL4_RESISTOR1 47000.0f
#define CELL4_RESISTOR2 10000.0f
#define CELL_MAX_VOLTAGE 4.2f
#define CELL_MIN_VOLTAGE 3.0f

extern const float CELL_R1[];
extern const float CELL_R2[];

typedef enum {
    OK = 0,
    FAULT
} BMS_Status_t;

float BMS_raw_to_volt(uint16_t raw, float r1, float r2);

void BMS_calculate_cell_voltage(uint16_t *raw, float *voltages, uint8_t num_cells);

float BMS_avg_voltage(float *voltages, uint8_t num_cells);

float BMS_calculate_charge(float avg_voltage);

BMS_Status_t BMS_check_fault(float *voltages, uint8_t num_cells);


#endif //bms.h