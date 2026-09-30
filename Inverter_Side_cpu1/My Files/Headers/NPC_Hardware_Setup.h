/*
 * NPC_Hardware_Setup.h
 *
 *  Created on: 17-Jun-2025
 *      Author: Subhasis Mishra
 */


#ifndef NPC_HARDWARE_SETUP_H_
#define NPC_HARDWARE_SETUP_H_

#include "f28x_project.h"
#include "driverlib.h"
#include "device.h"
#include "project_defines.h"

#include <string.h>
#include "sci.h"
#include "hw_memmap.h"
#include "Config.h"

// function declaration
//
extern void NPC_HAL_setupDevice(void);
extern void NPC_HAL_setupEPWM(void);
extern void NPC_HAL_setupADC(void);
extern void NPC_HAL_configureDAC(void);
extern void NPC_HAL_passDAC_AVals(uint16_t DACval_A);
extern void NPC_HAL_passDAC_BVals(uint16_t DACval_B);
extern void NPC_HAL_enableEPWMInterruptGeneration(void);
extern void NPC_HAL_setup_AUX_ISR_interrupt(void);
extern void NPC_HAL_setupEPWMtoTriggerADCSOC(void);
extern void NPC_HAL_disablePWMCLKCounting(void);
extern void NPC_HAL_enablePWMCLKCounting(void);
extern void NPC_HAL_setGpioPinsAsPWM(void);
extern void NPC_HAL_setupBoardProtection(void);
//extern void NPC_HAL_setupGateDriverEnableGPIO(void);

#if CONVERTER_TYPE == THREE_PHASE

extern void NPC_HAL_setupGateDriverDESATGPIO(void);
extern bool NPC_HAL_getGateDriverDESATGPIOStatus(void);

#else
#endif

extern void NPC_HAL_setup_INVONOFF_GPIO(void);
extern bool NPC_HAL_get_INVONOFF_GPIOStatus(void);



//extern void NPC_HAL_Disable_GateDriver();
//extern void NPC_HAL_Enable_GateDriver(void);
extern void NPC_HAL_setupLEDGPIO(void);
extern void NPC_HAL_setupRelayGPIO(void);
extern void NPC_HAL_TurnONRelay(void);
extern void NPC_HAL_TurnON_REDLED(void);
extern void NPC_HAL_TurnON_BLUELED(void);

#if CONVERTER_TYPE == THREE_PHASE

extern void NPC_HAL_TurnON_AC_OV_LED(void);
extern void NPC_HAL_TurnON_AC_UV_LED(void);
extern void NPC_HAL_TurnON_AC_OC_LED(void);
extern void NPC_HAL_TurnON_DC_OV_LED(void);
extern void NPC_HAL_TurnON_DESAT_LED(void);
extern void NPC_HAL_TurnON_PFC_RDY_LED(void);
extern void NPC_HAL_TurnOFF_PFC_RDY_LED(void);
extern void NPC_HAL_TurnOFF_AC_OV_LED(void);
extern void NPC_HAL_TurnOFF_AC_UV_LED(void);
extern void NPC_HAL_TurnON_LED1(void);
extern void NPC_HAL_TurnOFF_LED1(void);
extern void NPC_HAL_TurnON_LED2(void);
extern void NPC_HAL_TurnOFF_LED2(void);

#else
#endif



extern void NPC_HAL_SCI_B_GPIO_18_19_Init(void);
extern void NPC_HAL_SCI_C_GPIO_56_139_Init(void);
extern void NPC_HAL_config_SCI_polling(uint32_t base);
extern void NPC_HAL_config_SCI_interrupt(uint32_t base);
extern void MasterSlaveSelect_GPIO_init(void);

extern void SyncIn_GpioSelect(void);
extern void setupInputXbar_SyncIn(void);
extern void PWR_ON_OFF_GPIO_INIT(void);
extern void DESAT_PINS_INIT(void);
extern void outputRelay_INIT(void);
extern void RemoteSenseRelay_INIT(void);
extern void RS485_TX_EN_GPIO_INIT(void);
extern void PFC_STATUS_GPIO_INIT(void);

#pragma INTERRUPT (ISR, HPI)
interrupt void ISR(void);
interrupt void AUX_ISR(void);
//
// In line functions
//


static inline void NPC_HAL_updatePWMDutyAndDeadBand(uint32_t dutyA_S1,
                                                    uint32_t dutyB_S1,
                                                    uint32_t dutyC_S1,
                                                    uint32_t dutyN_S1,
                                                    uint32_t dutyE_S1,
                                                    uint32_t dutyF_S1,
                                                    float32_t dbval_DAB,
                                                    float32_t dbval_INV)
{
    //
    //Update COMP_A values
    //
    EPwm1Regs.CMPA.bit.CMPA = (uint32_t)dutyA_S1;
    EPwm2Regs.CMPA.bit.CMPA = (uint32_t)dutyB_S1;  // FOR PIN COMPACTABILITY OF PWB+SCC EPWM4...8 ARE USED
    EPwm3Regs.CMPA.bit.CMPA = (uint32_t)dutyC_S1;
    EPwm4Regs.CMPA.bit.CMPA = (uint32_t)dutyN_S1;
    EPwm5Regs.CMPA.bit.CMPA = (uint32_t)dutyE_S1;
    EPwm6Regs.CMPA.bit.CMPA = (uint32_t)dutyF_S1;



    //Update DeadBand values
    //
    /***************EPWM1_DBVals*****************/
    EPwm1Regs.DBRED.bit.DBRED  = (Uint16) dbval_INV;
    EPwm1Regs.DBFED.bit.DBFED  = (Uint16) dbval_INV;
    /***************EPWM2_DBVals*****************/
    EPwm2Regs.DBRED.bit.DBRED  = (Uint16) dbval_INV;
    EPwm2Regs.DBFED.bit.DBFED  = (Uint16) dbval_INV;
    /***************EPWM3_DBVals*****************/
    EPwm3Regs.DBRED.bit.DBRED  = (Uint16) dbval_DAB;
    EPwm3Regs.DBFED.bit.DBFED  = (Uint16) dbval_DAB;
    /***************EPWM4_DBVals*****************/
    EPwm4Regs.DBRED.bit.DBRED  = (Uint16) dbval_DAB;
    EPwm4Regs.DBFED.bit.DBFED  = (Uint16) dbval_DAB;
    /***************EPWM5_DBVals*****************/
    EPwm5Regs.DBRED.bit.DBRED  = (Uint16) dbval_DAB;
    EPwm5Regs.DBFED.bit.DBFED  = (Uint16) dbval_DAB;
    /***************EPWM6_DBVals*****************/
    EPwm6Regs.DBRED.bit.DBRED  = (Uint16) dbval_DAB;
    EPwm6Regs.DBFED.bit.DBFED  = (Uint16) dbval_DAB;
//    /***************EPWM3_DBVals*****************/
//    EPwm3Regs.DBRED.bit.DBRED  = (Uint16) dbval;
//    EPwm3Regs.DBFED.bit.DBFED  = (Uint16) dbval;
//    /***************EPWM4_DBVals*****************/
//    EPwm4Regs.DBRED.bit.DBRED  = (Uint16) dbval;
//    EPwm4Regs.DBFED.bit.DBFED  = (Uint16) dbval;
//    /***************EPWM5_DBVals*****************/
//    EPwm5Regs.DBRED.bit.DBRED  = (Uint16) dbval;
//    EPwm5Regs.DBFED.bit.DBFED  = (Uint16) dbval;
//    /***************EPWM6_DBVals*****************/
//    EPwm6Regs.DBRED.bit.DBRED  = (Uint16) dbval;
//    EPwm6Regs.DBFED.bit.DBFED  = (Uint16) dbval;
}


static inline void NPC_HAL_UpdatefandriveDuty(float32_t temp_fb) //NI
 {
     uint32_t duty_fan;
     //
     //Limit the signal between 0.1 to 0.75
     //
     temp_fb = (temp_fb > 1.0f) ? 0.9f : temp_fb;
     temp_fb = (temp_fb < 0.0f) ? 0.1f : temp_fb;

     duty_fan = (float)(0.5f*TimeBase_FAN);
     //
     //Update COMP_A values
     //
   //  EPwm8Regs.CMPA.bit.CMPA = duty_fan;
 }

static inline void NPC_HAL_ForceOSTEVENTtoALLEPWM(void)
{

    EPWM_forceTripZoneEvent(EPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM2_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM3_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM4_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM5_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM6_BASE, EPWM_TZ_FORCE_EVENT_OST);

}

static inline void NPC_HAL_ForceOSTEVENT_to_DAB_EPWM(void)
{

    EPWM_forceTripZoneEvent(EPWM3_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM4_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM5_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM6_BASE, EPWM_TZ_FORCE_EVENT_OST);

}

static inline void NPC_HAL_ForceOSTEVENT_to_INV_EPWM(void)
{

    EPWM_forceTripZoneEvent(EPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(EPWM2_BASE, EPWM_TZ_FORCE_EVENT_OST);

}


static inline void NPC_HAL_ClearALLPWMTripFlags(void)  //NI
{

    EPWM_clearTripZoneFlag(EPWM1_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM2_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM3_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM4_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM5_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM6_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));

    if(masterFlag)
    {
        EPWM_clearTripZoneFlag(EPWM8_BASE, (EPWM_TZ_INTERRUPT_OST |
                                             EPWM_TZ_INTERRUPT_CBC |
                                             EPWM_TZ_INTERRUPT_DCAEVT1));
    }


}

static inline void NPC_HAL_ClearDAB_PWMTripFlags(void)  //NI
{
    EPWM_clearTripZoneFlag(EPWM3_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM4_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM5_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM6_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
}

static inline void NPC_HAL_ClearINV_PWMTripFlags(void)  //NI
{

    EPWM_clearTripZoneFlag(EPWM1_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));
    EPWM_clearTripZoneFlag(EPWM2_BASE, (EPWM_TZ_INTERRUPT_OST |
            EPWM_TZ_INTERRUPT_CBC |
            EPWM_TZ_INTERRUPT_DCAEVT1));

    if(masterFlag)
    {
        EPWM_clearTripZoneFlag(EPWM8_BASE, (EPWM_TZ_INTERRUPT_OST |
                                             EPWM_TZ_INTERRUPT_CBC |
                                             EPWM_TZ_INTERRUPT_DCAEVT1));
    }


}

static inline bool NPC_HAL_check_CMPSS_Flag(void)
{
#if CONVERTER_TYPE == SINGLE_PHASE
    return (XBAR_getInputFlagStatus(NPC_A_XBAR_FLAG1) ||
            XBAR_getInputFlagStatus(NPC_A_XBAR_FLAG2) == 1);
#elif CONVERTER_TYPE == THREE_PHASE
return (XBAR_getInputFlagStatus(NPC_A_XBAR_FLAG1) ||
        XBAR_getInputFlagStatus(NPC_A_XBAR_FLAG2) ||
        XBAR_getInputFlagStatus(NPC_B_XBAR_FLAG1) ||
        XBAR_getInputFlagStatus(NPC_B_XBAR_FLAG2) ||
        XBAR_getInputFlagStatus(NPC_C_XBAR_FLAG1) ||
        XBAR_getInputFlagStatus(NPC_C_XBAR_FLAG2) == 1);
#else
#endif
}



#if CONVERTER_TYPE == SINGLE_PHASE
static inline void NPC_HAL_clear_ISR1_EPWM1_InterruptFlag(void)
{
    EPwm1Regs.ETCLR.bit.INT = 1; //clear INT1 flag
}

static inline void NPC_HAL_clear_ISR2_EPWM4_InterruptFlag(void)
{
    EPwm4Regs.ETCLR.bit.INT = 1; //clear INT1 flag
}

#elif CONVERTER_TYPE == THREE_PHASE

static inline void NPC_HAL_clear_ISR1_EPWM4_InterruptFlag(void)
{
    EPwm4Regs.ETCLR.bit.INT = 1; //clear INT1 flag
}

#else
#endif



static inline void NPC_HAL_Acknowledge_Interrupt(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
static inline void NPC_HAL_clearAUX_ISRInterruptFlag(void)
{

    CPUTimer_clearOverflowFlag(CPUTIMER2_BASE);
}

static inline void NPC_HAL_setupInterrupt(void)
{
    //
    //main ISR interrupt setup
    //
    NPC_HAL_enableEPWMInterruptGeneration();
    EALLOW;
#if CONVERTER_TYPE == SINGLE_PHASE

    PieVectTable.EPWM1_INT = &ISR;      //Registers a function to be called when an interrupt occurs.

    EDIS;
    IER |= M_INT3;                      // Set EPWM4 interrupt path to CPU(group 3 is epwm4 path)
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  // Set EPMW4 interrupt path in PIE registers (3rd row 4th column)

//    PieVectTable.EPWM4_INT = &ISR2_EPWM4;      //Registers a function to be called when an interrupt occurs.
//    EDIS;
//    IER |= M_INT3;                      // Set EPWM4 interrupt path to CPU(group 3 is epwm4 path)
//    PieCtrlRegs.PIEIER3.bit.INTx4 = 1;  // Set EPMW4 interrupt path in PIE registers (3rd row 4th column)

#elif CONVERTER_TYPE == THREE_PHASE

    PieVectTable.EPWM4_INT = &ISR;      //Registers a function to be called when an interrupt occurs.
    EDIS;
    IER |= M_INT3;                      // Set EPWM4 interrupt path to CPU(group 3 is epwm4 path)
    PieCtrlRegs.PIEIER3.bit.INTx4 = 1;  // Set EPMW4 interrupt path in PIE registers (3rd row 4th column)

#else
#endif
    //
    //Auxiliary ISR interrupt setup
    //
//    NPC_HAL_setup_AUX_ISR_interrupt();
//    EALLOW;
//    PieVectTable.TIMER2_INT = &AUX_ISR;     //Registers a function to be called when an interrupt occurs.
//    EDIS;
//    IER |= M_INT14;                         // Set CPUTIMER2 interrupt path to CPU(group 14 is CPUTIMER2 path)

//    EINT;                                   // Enable Global interrupt INTM
//    ERTM;                                   // Enable Global real time interrupt DBGM
}

static inline void check_Master_Slave_configuration(void)
{
    if(GPIO_readPin(60) == 1U && GPIO_readPin(22) == 1U)
    {
        masterFlag = TRUE;
        Slave1Flag = FALSE;
        Slave2Flag = FALSE;
    }

    else if(GPIO_readPin(60) == 1U && GPIO_readPin(22) == 0U)
    {
        masterFlag = FALSE;
        Slave1Flag = TRUE;
        Slave2Flag = FALSE;
    }

    else if(GPIO_readPin(60) == 0U && GPIO_readPin(22) == 1U)
    {
        masterFlag = FALSE;
        Slave1Flag = FALSE;
        Slave2Flag = TRUE;
    }
}

static inline uint32_t PWR_ON_OFF_GPIO_STATUS(void)
{
    uint32_t val;
    val = GPIO_readPin(65);
    return val;
}

static inline uint32_t DESAT_Status(void)
{
    uint32_t val;
    val = GPIO_readPin(104);
    return val;
}

static inline void GateDriveON(void)
{
    GPIO_WritePin(63, 0);
}

static inline void GateDriveOFF(void)
{
    GPIO_WritePin(63, 1);
}

static inline void outputRelay_ON(void)
{
    GPIO_WritePin(111, 1);
}

static inline void outputRelay_OFF(void)
{
    GPIO_WritePin(111, 0);
}

static inline void RemoteSenseRelay_ON(void)
{
    GPIO_WritePin(67, 1);
}

static inline void RemoteSenseRelay_OFF(void)
{
    GPIO_WritePin(67, 0);
}

static inline void setupMasterSlaveLED(void)
{
    if(masterFlag == TRUE && Slave1Flag == FALSE && Slave2Flag == FALSE)
    {
        NPC_HAL_TurnON_REDLED();
        NPC_HAL_TurnON_BLUELED();
    }

    else if(masterFlag == FALSE && Slave1Flag == TRUE && Slave2Flag == FALSE)
    {
        NPC_HAL_TurnON_REDLED();
    }

    else if(masterFlag == FALSE && Slave1Flag == FALSE && Slave2Flag == TRUE)
    {
        NPC_HAL_TurnON_BLUELED();
    }
}

static inline void CPU1_to_CPU2_handover(void)
{
//    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL5_SCI, 2, SYSCTL_CPUSEL_CPU2); // Hand-over the SCI B module access to CPU2
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL5_SCI, 3, SYSCTL_CPUSEL_CPU2); // Hand-over the SCI C module access to CPU2

    MemCfg_setGSRAMControllerSel(MEMCFG_SECT_GS6 | MEMCFG_SECT_GS8 | MEMCFG_SECT_GS10, MEMCFG_GSRAMCONTROLLER_CPU2); //Hand-over the control of GS6 & GS8 shared memory section to CPU2

    GPIO_setControllerCore(95U, GPIO_CORE_CPU2); // Hand-over the RS-485 Tx Enable GPIO(GPIO 95) to CPU2
}

static inline uint32_t check_PFC_Boost_Status(void)
{
    uint32_t val;
    val = GPIO_readPin(18);
    return val;
}
#endif /* NPC_HARDWARE_SETUP_H_ */
