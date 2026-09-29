#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#define CAN1 ((CAN_RegMap_t*)0x40006400UL)

typedef struct {
    volatile uint32_t MCR;      //0x000
    volatile uint32_t MSR;      //0x004
    volatile uint32_t TSR;      //0x008
    volatile uint32_t RF0R;     //0x00C
    volatile uint32_t RF1R;     //0x010
    volatile uint32_t IER;      //0x014
    volatile uint32_t ESR;      //0x018
    volatile uint32_t BTR;      //0x01C
    volatile uint32_t RESERVED[88]; //0x020-0x17C
    volatile uint32_t TI0R;     //0x180
    volatile uint32_t TDT0R;    //0x184
    volatile uint32_t TDL0R;    //0x188
    volatile uint32_t TDH0R;    //0x18C
    volatile uint32_t TI1R;     //0x190
    volatile uint32_t TDT1R;    //0x194
    volatile uint32_t TDL1R;    //0x198
    volatile uint32_t TDH1R;    //0x19C
    volatile uint32_t TI2R;     //0x1A0
    volatile uint32_t TDT2R;    //0x1A4
    volatile uint32_t TDL2R;    //0x1A8
    volatile uint32_t TDH2R;    //0x1AC
    volatile uint32_t RI0R;     //0x1B0
    volatile uint32_t RDT0R;    //0x1B4
    volatile uint32_t RDL0R;    //0x1B8
    volatile uint32_t RDH0R;    //0x1BC
    volatile uint32_t RI1R;     //0x1C0
    volatile uint32_t RDT1R;    //0x1C4
    volatile uint32_t RDL1R;    //0x1C8
    volatile uint32_t RDH1R;    //0x1CC
    volatile uint32_t RESERVED2[12]; //0x1D0 - 0x1FF
    volatile uint32_t FMR;      //0x200
    volatile uint32_t FM1R;     //0x204
    volatile uint32_t RESERVED4;//0x208
    volatile uint32_t FS1R;     //0x20C
    volatile uint32_t RESERVED5;//0x210
    volatile uint32_t FFA1R;    //0x214
    volatile uint32_t RESERVED6;//0x218
    volatile uint32_t FA1R;     //0x21C
    volatile uint32_t RESERVED7;//0x220
    volatile uint32_t RESERVED8[7];//0x224 - 0x23F
    volatile uint32_t FILTER_REGS[56]; //0x240 - 0x31C
} CAN_RegMap_t;

typedef enum {
    CAN_FILTER_MASK = 0,
    CAN_FILTER_LIST
} CAN_LIST_MASK_t;

typedef enum {
    CAN_FILTER_32BIT = 0,
    CAN_FILTER_16BIT
} CAN_16_32_t;

typedef struct {
    union {
        struct {
            uint32_t id[4];
            uint8_t num_ids;
        } list_mode;
        struct {
            uint32_t id[2];
            uint32_t mask[2];
        } mask_mode;
    }; 
    uint8_t bank;
    uint8_t fifo;
    CAN_16_32_t scale;
    CAN_LIST_MASK_t mode;
} CAN_Filter_t;

void CAN_init(void);

void CAN_filter_init(CAN_Filter_t *cfg);

#endif //can.h