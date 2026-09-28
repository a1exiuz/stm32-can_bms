#include "can.h"

void CAN_init(void) {
    /*
    pg. 1021
    software request init or sleep
    -set INRQ or SLEEP bit in MCR reg

    Can confrims by setting INAK or SLAK bits in MSR
    (something about internal pull up disable. cuase before its active)
    When neither is set CAN in normal mode

    before enter normal mode, SYNCHRONIZE = wait
    until CAN bus is idle = 11 consecutive recessive bits
    have been monitored on CANRX

    Software init when hardware is in init mode
    To enter init mode 
    Software sets the INRQ bit in MCR reg, and wait
    until harware sets INAK in the MSR reg

    to leave init mode software cleras INRQ bit, and 
    ready when INAK bit is cleared by hardware

    to init can - software set up bit timing in BTR reg
    and CAN options in MCR registers

    To init registers associated with filter banks
    (mode, scale, fifo, assignment, activation, and filter values)
    software hsa to set the finit bit in FMR
    --filter iniit can be done outside init mode

    once init completete 
    clear INRQ bit in MCR reg
    wait for occurence of a sequence of 11 consecutive reccessive bits
    swithc to normal mode confirmed by hardware by clearing INAK bit in MSR reg
    */
   CAN1->MCR |= (1U << 0);          // Set INRQ bit - request init
   while(!(CAN1->MSR & (1U << 0))); // Wait for INAK bit - CAN sets 1 when in init mode

   /*BIT TIMING - 500kbps
   Baudrate = Fclk / ((BRP + 1) * (1 + TS1 + TS2))
        16,000,000 / ((1 + 1) * (1 + 13 + 2))
        16,000,000 / (2 * 16)
        16,000,000 / 32
        500,000 = 500kbps
   */
   CAN1->BTR &= ~(0x3FF);           // Prescaler set to 2
   CAN1->BTR |= (1U);               // BRP bit [9:0] + 1 = 2
   
   /*MUST EQUAL 16 (1 + TS1 + TS2)*/
   CAN1->BTR &= ~(0xF << 16);       //TS1 = 13 
   CAN1->BTR |= (12U << 16);        //TS1 bit [3:0] + 1 = 13

   CAN1->BTR &= ~(7U << 20);        //TS2 = 2
   CAN1->BTR |= (1U << 20);         //TS2 bit [2:0] + 1 = 2

   CAN1->BTR &= ~(3U << 24);        //SJW = 1 -> SJW bit [1:0] + 1 = 1

   /*MCR OPTIONS*/
   CAN1->MCR &= ~(1U << 2);     //TXFP bit - Priority driven by ID of message
   CAN1->MCR &= ~(1U << 3);     //RFLM bit - Overwrite once FIFO full 
   CAN1->MCR &= ~(1U << 4);     //NART bit - Auto re-transmit until succesfull transmittion
   CAN1->MCR |= (1U << 5);      //AWUM bit - Auto wake when message detected
   CAN1->MCR |= (1U << 6);      //ABOM bit - automatic bus-off state 
}