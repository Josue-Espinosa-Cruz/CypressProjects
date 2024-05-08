/*******************************************************************************
* File Name: Dimmer.c  
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
#include "Dimmer.h"

static Dimmer_BACKUP_STRUCT  Dimmer_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Dimmer_Sleep
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
*  \snippet Dimmer_SUT.c usage_Dimmer_Sleep_Wakeup
*******************************************************************************/
void Dimmer_Sleep(void)
{
    #if defined(Dimmer__PC)
        Dimmer_backup.pcState = Dimmer_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Dimmer_backup.usbState = Dimmer_CR1_REG;
            Dimmer_USB_POWER_REG |= Dimmer_USBIO_ENTER_SLEEP;
            Dimmer_CR1_REG &= Dimmer_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Dimmer__SIO)
        Dimmer_backup.sioState = Dimmer_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Dimmer_SIO_REG &= (uint32)(~Dimmer_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Dimmer_Wakeup
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
*  Refer to Dimmer_Sleep() for an example usage.
*******************************************************************************/
void Dimmer_Wakeup(void)
{
    #if defined(Dimmer__PC)
        Dimmer_PC = Dimmer_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Dimmer_USB_POWER_REG &= Dimmer_USBIO_EXIT_SLEEP_PH1;
            Dimmer_CR1_REG = Dimmer_backup.usbState;
            Dimmer_USB_POWER_REG &= Dimmer_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Dimmer__SIO)
        Dimmer_SIO_REG = Dimmer_backup.sioState;
    #endif
}


/* [] END OF FILE */
