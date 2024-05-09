/*******************************************************************************
* File Name: Dimmer.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Dimmer_H) /* Pins Dimmer_H */
#define CY_PINS_Dimmer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Dimmer_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Dimmer_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Dimmer_Read(void);
void    Dimmer_Write(uint8 value);
uint8   Dimmer_ReadDataReg(void);
#if defined(Dimmer__PC) || (CY_PSOC4_4200L) 
    void    Dimmer_SetDriveMode(uint8 mode);
#endif
void    Dimmer_SetInterruptMode(uint16 position, uint16 mode);
uint8   Dimmer_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Dimmer_Sleep(void); 
void Dimmer_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Dimmer__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Dimmer_DRIVE_MODE_BITS        (3)
    #define Dimmer_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Dimmer_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Dimmer_SetDriveMode() function.
         *  @{
         */
        #define Dimmer_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Dimmer_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Dimmer_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Dimmer_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Dimmer_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Dimmer_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Dimmer_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Dimmer_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Dimmer_MASK               Dimmer__MASK
#define Dimmer_SHIFT              Dimmer__SHIFT
#define Dimmer_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Dimmer_SetInterruptMode() function.
     *  @{
     */
        #define Dimmer_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Dimmer_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Dimmer_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Dimmer_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Dimmer__SIO)
    #define Dimmer_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Dimmer__PC) && (CY_PSOC4_4200L)
    #define Dimmer_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Dimmer_USBIO_DISABLE              ((uint32)(~Dimmer_USBIO_ENABLE))
    #define Dimmer_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Dimmer_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Dimmer_USBIO_ENTER_SLEEP          ((uint32)((1u << Dimmer_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Dimmer_USBIO_SUSPEND_DEL_SHIFT)))
    #define Dimmer_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Dimmer_USBIO_SUSPEND_SHIFT)))
    #define Dimmer_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Dimmer_USBIO_SUSPEND_DEL_SHIFT)))
    #define Dimmer_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Dimmer__PC)
    /* Port Configuration */
    #define Dimmer_PC                 (* (reg32 *) Dimmer__PC)
#endif
/* Pin State */
#define Dimmer_PS                     (* (reg32 *) Dimmer__PS)
/* Data Register */
#define Dimmer_DR                     (* (reg32 *) Dimmer__DR)
/* Input Buffer Disable Override */
#define Dimmer_INP_DIS                (* (reg32 *) Dimmer__PC2)

/* Interrupt configuration Registers */
#define Dimmer_INTCFG                 (* (reg32 *) Dimmer__INTCFG)
#define Dimmer_INTSTAT                (* (reg32 *) Dimmer__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Dimmer_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Dimmer__SIO)
    #define Dimmer_SIO_REG            (* (reg32 *) Dimmer__SIO)
#endif /* (Dimmer__SIO_CFG) */

/* USBIO registers */
#if !defined(Dimmer__PC) && (CY_PSOC4_4200L)
    #define Dimmer_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Dimmer_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Dimmer_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Dimmer_DRIVE_MODE_SHIFT       (0x00u)
#define Dimmer_DRIVE_MODE_MASK        (0x07u << Dimmer_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Dimmer_H */


/* [] END OF FILE */
