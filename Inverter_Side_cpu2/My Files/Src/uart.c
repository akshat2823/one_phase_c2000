/*
 * uart.c
 *
 *  Created on: Jul 22, 2025
 *      Author: Anamitra Sarkar
 */

#include "uart.h"

    uint16_t Start_Address;
    uint16_t DataSize;

    uint16_t crcACKglobal[4] = {0x0000};

    int harmonicChunk = 0;


//    bool MemRead = FALSE;
    bool MemRead = TRUE;


    bool TransmitData = FALSE;

    int MemReadCount = 0;
    uint16_t r_Buff2[1024] = {0x0000};


    void handle_Display_uart(uint16_t r_Buff[], uint16_t size)
    {

        int k = 0;
        int n = 0;

        if(r_Buff[0] == receiveHeader_setVal || r_Buff[0] == receiveHeader_MeasVal)
        {
            for(n = 0; n < size; n++)
            {
                r_Buff2[n] = r_Buff[n];
            }
        }
        else{
            for(k = 0; k < size; k++)
            {
                if(r_Buff[k] == receiveHeader_setVal || r_Buff[k] == receiveHeader_MeasVal)
                    break;
            }
            for(n = 0; n < size; n++)
            {
                r_Buff2[n] = r_Buff[n + k];
            }
        }

        if(r_Buff2[0] == receiveHeader_setVal && r_Buff2[(size - k) - 1] == 0x00EF)
        {

            uint16_t crcCheck = crc16(r_Buff2, (size - k)- 1);

            if(crcCheck == 0x0000)
            {
                Start_Address = r_Buff2[1]*256 + r_Buff2[2];
                DataSize = r_Buff2[3]*256 + r_Buff2[4];

                if(Start_Address == (uint16_t)DSP_SET_START_ADDR)
                {
                    uint16_t p = 0;
                    for(p = 0; p < DataSize; p++)
                    {
                        Receive_Buf_Secondary[Start_Address + p] = r_Buff2[5 + p];
                        cpu2Write[Start_Address + p] = r_Buff2[5 + p];
                    }
    //                SetDataUpdate();
                    ProcessData();
                    SyncCommToControl();
                }
                else
                {
                    uint16_t p = 0;
                    for(p = 0; p < DataSize; p++)
                    {
                        Receive_Buf_Secondary[Start_Address + p] = r_Buff2[5 + p];
                    }
    //                HarmonicTableUpdate(Start_Address, DataSize);

                    uint16_t q = 0;
                    for(q = 0; q < MAX_LENGTH; q++)
                    {
                        Receive_Buf_Primary[q] = 0x0000;
                    }

    //                harmonicChunk++;
    //
    //                if(harmonicChunk == 5)
    //                {
    //                    ackDataReceive();
    //                    harmonicChunk = 0;
    //                }
    //                else{}
                }

            }

        }

        else if(r_Buff2[0] == receiveHeader_MeasVal && r_Buff2[(size - k) - 1] == 0x00EF)
        {
            uint16_t crcCheck = crc16(r_Buff2, (size - k)- 1);

            if(crcCheck == 0x0000)
            {
                    SyncCommToControl();
                    send_Data_to_STM();

            }

        }
    }

void send_Data_to_STM(void)
{

    uint16_t StartIdx = (uint16_t)DSP_MEAS_VAC;
    uint16_t EndIdx = (uint16_t)DSP_MEAS_END_ADDR;

    uint16_t Length = EndIdx - StartIdx;

    transmitBuff[0] = transmitHeader;
    transmitBuff[1] = ((StartIdx >> 8) & 0x00FF);
    transmitBuff[2] = (StartIdx & 0x00FF);
    transmitBuff[3] = ((Length >> 8) & 0x00FF);
    transmitBuff[4] = (Length & 0x00FF);

    // Fill payload: read float from cpu2Read, add offset, pack back
    int i;
    for(i = 0; i < Length; i++)
    {
        transmitBuff[5 + i] = cpu2Read[StartIdx + i];
    }


    // compute CRC
    uint16_t crc = crc16(transmitBuff, (uint16_t)(5U + Length));

    // append CRC (Modbus order: Low, then High)
    transmitBuff[5 + Length] = (uint8_t)(crc & 0xFF);          // CRC Low
    transmitBuff[6 + Length] = (uint8_t)((crc >> 8) & 0xFF);   // CRC High
    transmitBuff[7 + Length] = 0x00EF;

    uint16_t frame_len = 8U + Length;

    GPIO_writePin(95, 1);
    uint16_t j = 0;

    for(j = 0; j < frame_len + 1; j++)
    {
        SCI_writeCharBlockingFIFO(SCIC_BASE, transmitBuff[j]);
    }

    while(SCI_isTransmitterBusy(SCIC_BASE))
    {

    }
    GPIO_writePin(95, 0);

}



static inline void ackDataReceive(void)
{
    uint16_t ackBuf[4] = {0x004F, 0x004B, 0x0000, 0x0000};
    uint16_t crcCheck = crc16(ackBuf, (uint16_t)2u);
    ackBuf[2] = (uint16_t)(crcCheck & 0x00FF); // CRC Low
    ackBuf[3] = (uint16_t)((crcCheck >> 8) & 0x00FF); //CRC High

    int j = 0;
    for(j = 0; j < 4; j++)
    {
        crcACKglobal[j] = ackBuf[j];
        SCI_writeCharBlockingFIFO(SCIB_BASE, ackBuf[j]);
        while(SCI_getTxFIFOStatus(SCIB_BASE) != SCI_FIFO_TX0){}
//        SCI_writeCharBlockingFIFO(SCIC_BASE, ackBuf[j]);
//        while(SCI_getTxFIFOStatus(SCIC_BASE) != SCI_FIFO_TX0){}
        ackBuf[j] = 0x0000;
    }
}


void handle_PFC_uart(uint16_t Pfc_buff[], uint16_t Pfc_datasize)
{
    if(Pfc_buff[0] == 0x004A && Pfc_buff[Pfc_datasize - 1] == 0x00EF)
    {
        uint16_t crcCheck = crc16(Pfc_buff, (Pfc_datasize - 1));

        if(crcCheck == 0x0000)
        {
            uint16_t pfcStartAddr = Pfc_buff[1]*256 + Pfc_buff[2];
            uint16_t pfcDataLen = Pfc_buff[3]*256 + Pfc_buff[4];
            uint16_t p = 0;
            for(p = 0; p < pfcDataLen; p++)
            {
                Receive_Buf_Secondary[pfcStartAddr + p] = Pfc_buff[5 + p];
            }
            ReadMeasureDataFromPFC();
        }
    }
}


void SyncCommToControl(void)
{
    // ---------- Setpoints: Comm -> Control ----------
    Vac_fundamental    = SetSourceVoltage1P;
    Iset               = SetSourceCurrent1P;
    AC_Freq_Ref        = SetSourceFrequency1P;
    V_DC               = SetVdc;
    LoadSource_mode    = LoadSourceMode;

    // ---------- Limits: Comm -> Control ----------
    Limit_VAC          = SetLimVac;
    Limit_OCP          = SetLimIac;
    Limit_AC_Freq_Ref  = SetLimFreq;
    Limit_OPP          = SetLimPow;
    Limit_VDC_max  = SetLimVdcPlus;
    Limit_VDC_min  = SetLimVdcMinus;


    // ---------- Measurements: Control -> Comm ----------
    MeasureVoltage1P    = Meas_Vrms;
    ReadCurrent1P       = Meas_Irms;
    MeasureFrequency1P  = Meas_Freq;
    MeasureRealPower1P  = Meas_Preal;
    MeasurePfactor1P    = Meas_PF;

    MeasureVdc1P   = Meas_Vdc;
    MeasureIdc1P   = Meas_Idc;
    MeasureVpkPos1P = Meas_Vpk_P;
    MeasureVpkNeg1P = Meas_Vpk_N;
    MeasureIpkPos1P = Meas_Ipk_P;
    MeasureIpkNeg1P = Meas_Ipk_N;
}



