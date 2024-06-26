/*******************************************************************************
* File Name: Out_3.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Out_3.h"

static Out_3_BACKUP_STRUCT  Out_3_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Out_3_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Out_3_SUT.c usage_Out_3_Sleep_Wakeup
*******************************************************************************/
void Out_3_Sleep(void)
{
    #if defined(Out_3__PC)
        Out_3_backup.pcState = Out_3_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Out_3_backup.usbState = Out_3_CR1_REG;
            Out_3_USB_POWER_REG |= Out_3_USBIO_ENTER_SLEEP;
            Out_3_CR1_REG &= Out_3_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Out_3__SIO)
        Out_3_backup.sioState = Out_3_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Out_3_SIO_REG &= (uint32)(~Out_3_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Out_3_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Out_3_Sleep() for an example usage.
*******************************************************************************/
void Out_3_Wakeup(void)
{
    #if defined(Out_3__PC)
        Out_3_PC = Out_3_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Out_3_USB_POWER_REG &= Out_3_USBIO_EXIT_SLEEP_PH1;
            Out_3_CR1_REG = Out_3_backup.usbState;
            Out_3_USB_POWER_REG &= Out_3_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Out_3__SIO)
        Out_3_SIO_REG = Out_3_backup.sioState;
    #endif
}


/* [] END OF FILE */
