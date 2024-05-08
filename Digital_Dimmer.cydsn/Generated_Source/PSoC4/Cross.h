/*******************************************************************************
* File Name: Cross.h  
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

#if !defined(CY_PINS_Cross_H) /* Pins Cross_H */
#define CY_PINS_Cross_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Cross_aliases.h"


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
} Cross_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Cross_Read(void);
void    Cross_Write(uint8 value);
uint8   Cross_ReadDataReg(void);
#if defined(Cross__PC) || (CY_PSOC4_4200L) 
    void    Cross_SetDriveMode(uint8 mode);
#endif
void    Cross_SetInterruptMode(uint16 position, uint16 mode);
uint8   Cross_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Cross_Sleep(void); 
void Cross_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Cross__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Cross_DRIVE_MODE_BITS        (3)
    #define Cross_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Cross_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Cross_SetDriveMode() function.
         *  @{
         */
        #define Cross_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Cross_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Cross_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Cross_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Cross_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Cross_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Cross_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Cross_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Cross_MASK               Cross__MASK
#define Cross_SHIFT              Cross__SHIFT
#define Cross_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Cross_SetInterruptMode() function.
     *  @{
     */
        #define Cross_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Cross_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Cross_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Cross_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Cross__SIO)
    #define Cross_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Cross__PC) && (CY_PSOC4_4200L)
    #define Cross_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Cross_USBIO_DISABLE              ((uint32)(~Cross_USBIO_ENABLE))
    #define Cross_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Cross_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Cross_USBIO_ENTER_SLEEP          ((uint32)((1u << Cross_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Cross_USBIO_SUSPEND_DEL_SHIFT)))
    #define Cross_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Cross_USBIO_SUSPEND_SHIFT)))
    #define Cross_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Cross_USBIO_SUSPEND_DEL_SHIFT)))
    #define Cross_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Cross__PC)
    /* Port Configuration */
    #define Cross_PC                 (* (reg32 *) Cross__PC)
#endif
/* Pin State */
#define Cross_PS                     (* (reg32 *) Cross__PS)
/* Data Register */
#define Cross_DR                     (* (reg32 *) Cross__DR)
/* Input Buffer Disable Override */
#define Cross_INP_DIS                (* (reg32 *) Cross__PC2)

/* Interrupt configuration Registers */
#define Cross_INTCFG                 (* (reg32 *) Cross__INTCFG)
#define Cross_INTSTAT                (* (reg32 *) Cross__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Cross_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Cross__SIO)
    #define Cross_SIO_REG            (* (reg32 *) Cross__SIO)
#endif /* (Cross__SIO_CFG) */

/* USBIO registers */
#if !defined(Cross__PC) && (CY_PSOC4_4200L)
    #define Cross_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Cross_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Cross_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Cross_DRIVE_MODE_SHIFT       (0x00u)
#define Cross_DRIVE_MODE_MASK        (0x07u << Cross_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Cross_H */


/* [] END OF FILE */
