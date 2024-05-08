/*******************************************************************************
* File Name: Cruce.h  
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

#if !defined(CY_PINS_Cruce_H) /* Pins Cruce_H */
#define CY_PINS_Cruce_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Cruce_aliases.h"


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
} Cruce_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Cruce_Read(void);
void    Cruce_Write(uint8 value);
uint8   Cruce_ReadDataReg(void);
#if defined(Cruce__PC) || (CY_PSOC4_4200L) 
    void    Cruce_SetDriveMode(uint8 mode);
#endif
void    Cruce_SetInterruptMode(uint16 position, uint16 mode);
uint8   Cruce_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Cruce_Sleep(void); 
void Cruce_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Cruce__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Cruce_DRIVE_MODE_BITS        (3)
    #define Cruce_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Cruce_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Cruce_SetDriveMode() function.
         *  @{
         */
        #define Cruce_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Cruce_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Cruce_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Cruce_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Cruce_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Cruce_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Cruce_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Cruce_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Cruce_MASK               Cruce__MASK
#define Cruce_SHIFT              Cruce__SHIFT
#define Cruce_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Cruce_SetInterruptMode() function.
     *  @{
     */
        #define Cruce_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Cruce_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Cruce_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Cruce_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Cruce__SIO)
    #define Cruce_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Cruce__PC) && (CY_PSOC4_4200L)
    #define Cruce_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Cruce_USBIO_DISABLE              ((uint32)(~Cruce_USBIO_ENABLE))
    #define Cruce_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Cruce_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Cruce_USBIO_ENTER_SLEEP          ((uint32)((1u << Cruce_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Cruce_USBIO_SUSPEND_DEL_SHIFT)))
    #define Cruce_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Cruce_USBIO_SUSPEND_SHIFT)))
    #define Cruce_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Cruce_USBIO_SUSPEND_DEL_SHIFT)))
    #define Cruce_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Cruce__PC)
    /* Port Configuration */
    #define Cruce_PC                 (* (reg32 *) Cruce__PC)
#endif
/* Pin State */
#define Cruce_PS                     (* (reg32 *) Cruce__PS)
/* Data Register */
#define Cruce_DR                     (* (reg32 *) Cruce__DR)
/* Input Buffer Disable Override */
#define Cruce_INP_DIS                (* (reg32 *) Cruce__PC2)

/* Interrupt configuration Registers */
#define Cruce_INTCFG                 (* (reg32 *) Cruce__INTCFG)
#define Cruce_INTSTAT                (* (reg32 *) Cruce__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Cruce_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Cruce__SIO)
    #define Cruce_SIO_REG            (* (reg32 *) Cruce__SIO)
#endif /* (Cruce__SIO_CFG) */

/* USBIO registers */
#if !defined(Cruce__PC) && (CY_PSOC4_4200L)
    #define Cruce_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Cruce_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Cruce_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Cruce_DRIVE_MODE_SHIFT       (0x00u)
#define Cruce_DRIVE_MODE_MASK        (0x07u << Cruce_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Cruce_H */


/* [] END OF FILE */
