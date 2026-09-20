#include "bms.h"
#include "adc.h"

const float CELL_R1[] = {CELL1_RESISTOR1, CELL2_RESISTOR1, 
CELL3_RESISTOR1, CELL4_RESISTOR1};

const float CELL_R2[] = {CELL1_RESISTOR2, CELL2_RESISTOR2, 
CELL3_RESISTOR2, CELL4_RESISTOR2};

float BMS_raw_to_volt(uint16_t raw, float r1, float r2) {
    float junction = (raw / ADC_MAX_VAL) * ADC_MAX_VOLTAGE;
    float cell_volt = junction * (r1 + r2) / r2;
    return (cell_volt);
}

void BMS_calculate_cell_voltage(uint16_t *raw, float *voltages, uint8_t num_cells) {
    if(!raw || !voltages)
        return;
    
    for(uint8_t i = 0; i < num_cells; i++) {
        if(i == 0) {
            voltages[i] = BMS_raw_to_volt(raw[i], CELL_R1[i], CELL_R2[i]);
        } else {
            float voltage = BMS_raw_to_volt(raw[i], CELL_R1[i], CELL_R2[i]);
            voltages[i] = voltage - voltages[i - 1];
        } 
    }
}

float BMS_avg_voltage(float *voltages, uint8_t num_cells) {
    if(!voltages) 
        return 0;

    float cumulative_volt = 0;

    for(uint8_t i = 0; i < num_cells; i++) {
        cumulative_volt += voltages[i];
    }

    return(cumulative_volt / num_cells);
}

float BMS_calculate_charge(float avg_voltage) {
    return((avg_voltage - CELL_MIN_VOLTAGE) / (CELL_MAX_VOLTAGE - CELL_MIN_VOLTAGE) * 100.0f);
}

BMS_Status_t BMS_check_fault(float *voltages, uint8_t num_cells) {
    if(!voltages)
        return FAULT;

    for(uint8_t i = 0; i < num_cells; i++) {
        if(voltages[i] <= CELL_MIN_VOLTAGE) {
            return FAULT;
        }
    }
    
    return OK;
}