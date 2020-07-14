/******************************************************************************
*
* Copyright (C) 2014 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
* @file  xttcps_tapp_example.c
*
* This file contains an example uses ttc to generate interrupt and
* update a flag which is checked in interrupt example to confirm whether the
* interrupt is generated or not.
*
*
* @note
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver  Who    Date     Changes
* ---- ------ -------- ---------------------------------------------
* 3.00 pkp    01/12/15 First release
* 3.01 pkp	  01/30/16 Modified SetupTimer to remove XTtcps_Stop before TTC
*					   configuration as it is added in xttcps.c in
*					   XTtcPs_CfgInitialize
* 3.01 pkp	  03/04/16 Added status check after SetupTicker is called by
*					   TmrInterruptExample
* 3.2  mus    10/28/16 Updated TmrCntrSetup as per prototype of
*                      XTtcPs_CalcIntervalFromFreq
*      ms     01/23/17 Modified xil_printf statement in main function to
*                      ensure that "Successfully ran" and "Failed" strings
*                      are available in all examples. This is a fix for
*                      CR-965028.
*</pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xil_printf.h"
#include "test.h"


/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */

#define TTC_TICK_DEVICE_ID	XPAR_XTTCPS_11_DEVICE_ID
#define TTC_TICK_INTR_ID	XPAR_XTTCPS_11_INTR
/**用来测试rpmsg的通信时延 */
#define TTC_COUNT_DEVICE_ID	XPAR_XTTCPS_8_DEVICE_ID

#define INTC_DEVICE_ID		XPAR_SCUGIC_0_DEVICE_ID
#define	TICK_TIMER_FREQ_HZ	50  /* Tick timer counter's output frequency */

/**************************** Type Definitions *******************************/
typedef struct {
	u32 OutputHz;	/* Output frequency */
	XInterval Interval;	/* Interval value */
	u8 Prescaler;	/* Prescaler value */
	u16 Options;	/* Option settings */
} TmrCntrSetup;

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

static int SetupIntr(XTtcPs *TtcPsInst,u16 TtcTickIntrID,
				XScuGic *InterruptController);
/* Set up routines for timer counters */
static int SetupTicker(XTtcPs *TtcPsInst,u16 DeviceID);
static int SetupTimer(u16 DeviceID, XTtcPs *TtcPsInst);
static void TickHandler(void *CallBackRef);
static int SetupCounter(XTtcPs *TtcPsInst,u16 DeviceID);
/************************** Variable Definitions *****************************/
static TmrCntrSetup SettingsTable=
	{TICK_TIMER_FREQ_HZ, 0, 0, 0};	/* Ticker timer counter initial setup,
									only output freq */
static XTtcPs TtcPsInst;  /* Timer counter instance */
static XTtcPs TtcPsCount;  /*作为计数器使用 */


/**
 * @brief tcc初始化函数
 * 
 * @return int 
 */
int TccInit(void)
{
	int Status;

	xil_printf("Starting tcc_init \r\n");
	Status = SetupTicker(&TtcPsInst,TTC_TICK_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("SetupTicker Failed\r\n!");
		return XST_FAILURE;
	}
	Status = SetupCounter(&TtcPsCount,TTC_COUNT_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("SetupTicker Failed\r\n!");
		return XST_FAILURE;
	}
	Status = SetupIntr(&TtcPsInst,TTC_TICK_INTR_ID,&InterruptController);
	if (Status != XST_SUCCESS) {
		xil_printf("SetupIntr Failed\r\n!");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
/**
 * @brief tcc start
 * 
 * @return int 
 */
int TccStart(void)
{
	XTtcPs_Start(&TtcPsInst);
	XTtcPs_Start(&TtcPsCount);
	xil_printf("tcc_start Successfully \r\n");
	return XST_SUCCESS;
}

int TccGetCount(void)
{
	u32 CountNumber;
	CountNumber = XTtcPs_GetCounterValue(&TtcPsCount);
	xil_printf("CountNumber %x \r\n", CountNumber);
	return XST_SUCCESS;
}
/**
 * @brief 将定时器中断连接到gic
 * 
 * @param TtcPsInst 
 * @param TtcTickIntrID 
 * @param InterruptController 
 * @return int 
 */
static int SetupIntr(XTtcPs *TtcPsInst,u16 TtcTickIntrID,
				XScuGic *InterruptController)
{
	int Status;
	XTtcPs *TtcPsTick;

	TtcPsTick = TtcPsInst;
	/*
	 * Connect to the interrupt controller
	 */
	Status = XScuGic_Connect(InterruptController, TtcTickIntrID,
		(Xil_InterruptHandler)TickHandler, (void *)TtcPsTick);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Enable the interrupt for the Timer counter
	 */
	XScuGic_Enable(InterruptController, TtcTickIntrID);

	/*
	 * Enable the interrupts for the tick timer/counter
	 */
	XTtcPs_EnableInterrupts(TtcPsTick, XTTCPS_IXR_INTERVAL_MASK);

	return Status;
}
/**
 * @brief 配置定时器
 * 
 * @param TtcPsInst 
 * @param DeviceID 
 * @param TtcTickIntrID 
 * @param InterruptController 
 * @return int 
 */
int SetupTicker(XTtcPs *TtcPsInst,u16 DeviceID)
{
	int Status;
	TmrCntrSetup *TimerSetup;

	TimerSetup = &SettingsTable;

	/*
	 * Set up appropriate options for Ticker: interval mode without
	 * waveform output.
	 */
	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
					      XTTCPS_OPTION_WAVE_DISABLE);

	/*
	 * Calling the timer setup routine
	 *  . initialize device
	 *  . set options
	 */
	Status = SetupTimer(DeviceID,TtcPsInst);
	if(Status != XST_SUCCESS) {
		return Status;
	}

	return Status;
}

/**
 * @brief 初始化计数器
 * 
 * @param TtcPsInst 
 * @param DeviceID 
 * @return int 
 */
static int SetupCounter(XTtcPs *TtcPsInst,u16 DeviceID)
{
	int Status;
	TmrCntrSetup TimerSetup = {0};
	XTtcPs_Config *Config;
	
	/*
	 * Set up appropriate options for Ticker: interval mode without
	 * waveform output.
	 */
	TimerSetup.Options |= (XTTCPS_OPTION_WAVE_DISABLE);

	/*
	 * Look up the configuration based on the device identifier
	 */
	Config = XTtcPs_LookupConfig(DeviceID);
	if (NULL == Config) {
		return XST_FAILURE;
	}
	/*
	 * Initialize the device
	 */
	Status = XTtcPs_CfgInitialize(TtcPsInst, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the options
	 */
	XTtcPs_SetOptions(TtcPsInst, TimerSetup.Options);
	return Status;
}
/****************************************************************************/
/**
*
* This function sets up a timer counter device, using the information in its
* setup structure.
*  . initialize device
*  . set options
*  . set interval and prescaler value for given output frequency.
*
* @param	DeviceID is the unique ID for the device.
* @param	TtcPsInst is a pointer to the ttc instance.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
*****************************************************************************/
int SetupTimer(u16 DeviceID,XTtcPs *TtcPsInst)
{
	int Status;
	XTtcPs_Config *Config;
	XTtcPs *Timer;
	TmrCntrSetup *TimerSetup;

	TimerSetup = &SettingsTable;

	Timer = TtcPsInst;

	/*
	 * Look up the configuration based on the device identifier
	 */
	Config = XTtcPs_LookupConfig(DeviceID);
	if (NULL == Config) {
		return XST_FAILURE;
	}
	/*
	 * Initialize the device
	 */
	Status = XTtcPs_CfgInitialize(Timer, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the options
	 */
	XTtcPs_SetOptions(Timer, TimerSetup->Options);

	/*
	 * Timer frequency is preset in the TimerSetup structure,
	 * however, the value is not reflected in its other fields, such as
	 * IntervalValue and PrescalerValue. The following call will map the
	 * frequency to the interval and prescaler values.
	 */
	XTtcPs_CalcIntervalFromFreq(Timer, TimerSetup->OutputHz,
		&(TimerSetup->Interval), &(TimerSetup->Prescaler));

	/*
	 * Set the interval and prescale
	 */
	XTtcPs_SetInterval(Timer, TimerSetup->Interval);
	XTtcPs_SetPrescaler(Timer, TimerSetup->Prescaler);

	return XST_SUCCESS;
}

/***************************************************************************/
/**
*
* This function is the handler which updates the flag when TTC interrupt is
* occurred
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the TTC driver.
*
* @return	None.
*
*****************************************************************************/
static void TickHandler(void *CallBackRef)
{
	u32 StatusEvent;

	/*
	 * Read the interrupt status, then write it back to clear the interrupt.
	 */
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
	//xil_printf("TccHandler in \r\n");
	CanSend();

	XTtcPs_ResetCounterValue(&TtcPsInst);
	XTtcPs_Start(&TtcPsInst);

}
