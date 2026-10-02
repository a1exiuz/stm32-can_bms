#include "can.h"
#include "bms.h"

static const uint32_t bms_ids[] = {
    BMS_CELL_VOLTAGE_ID,
    BMS_INFO_ID
};

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

void CAN_filter_init(CAN_Filter_t *cfg) {
    /*Filter init
    pg 1029
   
    Clear FACT bit in CAN_FA1R reg
    Filter scale config in FSCx bit in FS1R reg
    Identifier list or identifier mask mode for mask/identifier reg
    config by FBMx bits in FM1R reg

    To filter a group of ids, config Mask/ID reg in mask mode
    To select single id, configu Mask/ID in id list mode
    */
    CAN1->FMR |= (1U);       //Enter filter init mode
    CAN1->FA1R &= ~(1U);     //Clear FACT BIT 

   
    if(cfg->scale == CAN_FILTER_32BIT) {
        CAN1->FS1R |= (1U << cfg->bank);  //FSCx Bit - single 32-bit scale config
    } else {
        CAN1->FS1R &= ~(1U << cfg->bank); //dual 16-bit scale
    }

    /*
     /*
        F0R1 bits: (ID register)
        [31-21] = STID = your chosen ID (0x400)
        [20-4]  = EXID (not used for standard 11-bit)
        [3]     = IDE = 0 (standard frame)
        [2]     = RTR = 0 (data frame)
        [1-0]   = unused

        F0R2 same layout (Mask register)
        CAN1->Filter_regs = FxRi 
        cfg->bank = 0 * 2 =     F0R1
        cfg->bank = 0 * 2 + 1 = F0R2 

        cfg->bank = 1 * 2 =     F1R1
        cfg->bank = 1 * 2 + 1 = F1R2 
        etc...

        = instead of |= we want to insert id and make everything else 0

    */
    if(cfg->mode == CAN_FILTER_MASK) {
        CAN1->FM1R &= ~(1U << cfg->bank); //FMBx bit - Mask mode
        
        if(cfg->scale == CAN_FILTER_32BIT) {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->mask_mode.id[0] << 21);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->mask_mode.mask[0] << 21);
        } else {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->mask_mode.mask[0] << 21) | (cfg->mask_mode.id[0] << 5);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->mask_mode.mask[1] << 21) | (cfg->mask_mode.id[1] << 5);
        }    
    } else {
        CAN1->FM1R |= (1U << cfg->bank);  //List mode

        if((cfg->list_mode.num_ids == 1)  && (cfg->scale == CAN_FILTER_32BIT)) {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->list_mode.id[0] << 21);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->list_mode.id[0] << 21);
        } else if((cfg->list_mode.num_ids == 2) && (cfg->scale == CAN_FILTER_32BIT)) {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->list_mode.id[0] << 21);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->list_mode.id[1] << 21);
        } else if((cfg->list_mode.num_ids == 3) && (cfg->scale == CAN_FILTER_16BIT)) {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->list_mode.id[1] << 21) | (cfg->list_mode.id[0] << 5);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->list_mode.id[2] << 5);
        } else if((cfg->list_mode.num_ids == 4) && (cfg->scale == CAN_FILTER_16BIT)) {
            CAN1->FILTER_REGS[cfg->bank * 2] = (cfg->list_mode.id[1] << 21) | (cfg->list_mode.id[0] << 5);
            CAN1->FILTER_REGS[cfg->bank * 2 + 1] = (cfg->list_mode.id[2] << 21) | (cfg->list_mode.id[3] << 5);
        } else 
            return;

        if(cfg->fifo == 0) {
            CAN1->FFA1R &= ~(1U << cfg->bank);
        } else {
            CAN1->FFA1R |= (1U << cfg->bank);
        }
            
        CAN1->FA1R |= (1U << cfg->bank);

        CAN1->FMR &= ~(1U);      //Exit filter init mode
        CAN1->MCR &= ~(1U);      //Exit CAN init mode
        while(CAN1->MSR & (1U)); //Wait for INAK bit to be cleared
    }
}