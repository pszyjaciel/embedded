/**
 * @file clock_xmc1.c
 * @date 2016-07-08
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * CLOCK_XMC1 v4.0.22 - APP to configure System and Peripheral Clocks.
 *
 * Copyright (c) 2015-2019, Infineon Technologies AG
 * All rights reserved.                        
 *                                             
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the           
 * following conditions are met:   
 *                                                                              
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following   
 *   disclaimer.                        
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the    
 *   following disclaimer in the documentation and/or other materials provided with the distribution.     
 *                         
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 *   products derived from this software without specific prior written permission. 
 *                                             
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,  
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE   
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR        
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,      
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE   
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
 *                                                                              
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes       
 * with Infineon Technologies AG (dave@infineon.com).        
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 * 2015-02-16:
 *     - Initial version for DAVEv4. <BR>
 * 2015-05-08:
 *     - Typo mistake corrected in _GetAppVersion(). <BR>
 * 2015-09-22:
 *     - CLOCK_XMC1_Init API and CLOCK_XMC1_SetMCLKFrequency APIs are provided. <BR>
 * 2015-10-19:
 *     - non-weak OSCHP_GetFrequency function is provided. <BR>
 *     - CLOCK_XMC1_IsDCO1ExtRefCalibrationReady function is provided. <BR>
 * 2016-05-24:
 *     - XMC_ASSERT is added for CLOCK_XMC1_Init API. <BR>
 * 2016-07-08:
 *     - Fixed incorrect case for an included header.<br>
 *
 * @endcond 
 *
 */
 
/***********************************************************************************************************************
 * HEADER FILES                                                                                                      
 **********************************************************************************************************************/
#include "clock_xmc1.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/***********************************************************************************************************************
* API IMPLEMENTATION
***********************************************************************************************************************/
/*  API to retrieve version of the APP */
DAVE_APP_VERSION_t CLOCK_XMC1_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;
  version.major = (uint8_t)CLOCK_XMC1_MAJOR_VERSION;
  version.minor = (uint8_t)CLOCK_XMC1_MINOR_VERSION;
  version.patch = (uint8_t)CLOCK_XMC1_PATCH_VERSION;

  return (version);
}

/*
 * API to initialize the CLOCK_XMC1 APP Interrupts
 */
CLOCK_XMC1_STATUS_t CLOCK_XMC1_Init(CLOCK_XMC1_t *handle)
{
  CLOCK_XMC1_STATUS_t status = CLOCK_XMC1_STATUS_SUCCESS;
  CLOCK_XMC1_STATUS_t loci_event_status = CLOCK_XMC1_STATUS_SUCCESS;
  CLOCK_XMC1_STATUS_t stdbyclkfail_status = CLOCK_XMC1_STATUS_SUCCESS;
  CLOCK_XMC1_STATUS_t loss_ext_clock_event_status = CLOCK_XMC1_STATUS_SUCCESS;
  CLOCK_XMC1_STATUS_t dco1_out_sync_status = CLOCK_XMC1_STATUS_SUCCESS;

  XMC_ASSERT("CLOCK_XMC1_Init: CLOCK_XMC1 APP handle pointer uninitialized", (handle != NULL));

  if (handle->init_status == false)
  {
#ifdef CLOCK_XMC1_INTERRUPT_ENABLED

    status = (CLOCK_XMC1_STATUS_t)GLOBAL_SCU_XMC1_Init(handle->global_scu_handleptr);
    if (CLOCK_XMC1_STATUS_SUCCESS == status)
    {
#ifdef CLOCK_XMC1_LOCI_EVENT_ENABLED
      /* Initialization of CPU_CTRL_XMC1 APP */
      loci_event_status = (CLOCK_XMC1_STATUS_t)GLOBAL_SCU_XMC1_RegisterCallback(
                           GLOBAL_SCU_XMC1_EVENT_LOCI, handle->callback_function_loci);
      /* Enable Loss of DCO1 Clock Event */
      XMC_SCU_INTERRUPT_EnableEvent(GLOBAL_SCU_XMC1_EVENT_LOCI);
#endif
#ifdef CLOCK_XMC1_STDBYCLKFAIL_EVENT_ENABLED
      /* Initialization of CPU_CTRL_XMC1 APP */
      stdbyclkfail_status = (CLOCK_XMC1_STATUS_t)GLOBAL_SCU_XMC1_RegisterCallback(
                             GLOBAL_SCU_XMC1_EVENT_STDBYCLKFAIL, handle->callback_function_stdbyclkfail);
      /* Enable Standby Clock Failure Event */
      XMC_SCU_INTERRUPT_EnableEvent(GLOBAL_SCU_XMC1_EVENT_STDBYCLKFAIL);
#endif

#if (UC_SERIES == XMC14)

#ifdef CLOCK_XMC1_LOSS_EXT_CLOCK_EVENT_ENABLED
      /* Initialization of CPU_CTRL_XMC1 APP */
      loss_ext_clock_event_status = (CLOCK_XMC1_STATUS_t)GLOBAL_SCU_XMC1_RegisterCallback(
                                     GLOBAL_SCU_XMC1_EVENT_LOSS_EXT_CLOCK, handle->callback_function_loss_ext_clock);
      /* Enable Loss of external OSC_HP clock Event */
      XMC_SCU_INTERRUPT_EnableEvent(GLOBAL_SCU_XMC1_EVENT_LOSS_EXT_CLOCK);
#endif
#ifdef CLOCK_XMC1_DCO1_OUT_SYNC_EVENT_ENABLED
      /* Initialization of CPU_CTRL_XMC1 APP */
      dco1_out_sync_status = (CLOCK_XMC1_STATUS_t)GLOBAL_SCU_XMC1_RegisterCallback(
                              GLOBAL_SCU_XMC1_EVENT_DCO1_OUT_SYNC, handle->callback_function_dco1_out_sync);
      /* Enable  DCO1 Out of SYNC Event */
      XMC_SCU_INTERRUPT_EnableEvent(GLOBAL_SCU_XMC1_EVENT_DCO1_OUT_SYNC);
#endif

#endif
    }

#endif
    status = (CLOCK_XMC1_STATUS_t)(((uint32_t)loci_event_status) | ((uint32_t)stdbyclkfail_status) |
    		                       ((uint32_t)loss_ext_clock_event_status) | ((uint32_t)dco1_out_sync_status));
    if (CLOCK_XMC1_STATUS_SUCCESS == status)
    {
      handle->init_status = true;
    }
  }
  return (status);
}

/*  API for ramping up/down the system clock frequency  */
void CLOCK_XMC1_SetMCLKFrequency(uint32_t freq_khz)
{
  XMC_SCU_CLOCK_SetMCLKFrequency(freq_khz);
}

#if (CLOCK_XMC1_OSCHP_ENABLED)
/*  API to retrieve high precision external oscillator frequency */
uint32_t OSCHP_GetFrequency(void)
{
  return (CLOCK_XMC1_OSCHP_FREQUENCY);
}
#endif

#if (CLOCK_XMC1_DCO1_CALIBRATION_ENABLED)
/*  API to check whether DCO1 is synchronized to the XTAL frequency */
bool CLOCK_XMC1_IsDCO1ExtRefCalibrationReady(void)
{
  return (XMC_SCU_CLOCK_IsDCO1ExtRefCalibrationReady());
}
#endif
