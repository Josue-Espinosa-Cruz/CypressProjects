/*******************************************************************************
* File Name: Salida.h  
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

#if !defined(CY_PINS_Salida_H) /* Pins Salida_H */
#define CY_PINS_Salida_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Salida_aliases.h"


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
} Salida_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Salida_Read(void);
void    Salida_Write(uint8 value);
uint8   Salida_ReadDataReg(void);
#if defined(Salida__PC) || (CY_PSOC4_4200L) 
    void    Salida_SetDriveMode(uint8 mode);
#endif
void    Salida_SetInterruptMode(uint16 position, uint16 mode);
uint8   Salida_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Salida_Sleep(void); 
void Salida_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Salida__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Salida_DRIVE_MODE_BITS        (3)
    #define Salida_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Salida_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Salida_SetDriveMode() function.
         *  @{
         */
        #define Salida_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Salida_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Salida_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Salida_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Salida_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Salida_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Salida_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Salida_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Salida_MASK               Salida__MASK
#define Salida_SHIFT              Salida__SHIFT
#define Salida_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Salida_SetInterruptMode() function.
     *  @{
     */
        #define Salida_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Salida_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Salida_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Salida_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Salida__SIO)
    #define Salida_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Salida__PC) && (CY_PSOC4_4200L)
    #define Salida_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Salida_USBIO_DISABLE              ((uint32)(~Salida_USBIO_ENABLE))
    #define Salida_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Salida_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Salida_USBIO_ENTER_SLEEP          ((uint32)((1u << Salida_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Salida_USBIO_SUSPEND_DEL_SHIFT)))
    #define Salida_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Salida_USBIO_SUSPEND_SHIFT)))
    #define Salida_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Salida_USBIO_SUSPEND_DEL_SHIFT)))
    #define Salida_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Salida__PC)
    /* Port Configuration */
    #define Salida_PC                 (* (reg32 *) Salida__PC)
#endif
/* Pin State */
#define Salida_PS                     (* (reg32 *) Salida__PS)
/* Data Register */
#define Salida_DR                     (* (reg32 *) Salida__DR)
/* Input Buffer Disable Override */
#define Salida_INP_DIS                (* (reg32 *) Salida__PC2)

/* Interrupt configuration Registers */
#define Salida_INTCFG                 (* (reg32 *) Salida__INTCFG)
#define Salida_INTSTAT                (* (reg32 *) Salida__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Salida_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Salida__SIO)
    #define Salida_SIO_REG            (* (reg32 *) Salida__SIO)
#endif /* (Salida__SIO_CFG) */

/* USBIO registers */
#if !defined(Salida__PC) && (CY_PSOC4_4200L)
    #define Salida_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Salida_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Salida_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Salida_DRIVE_MODE_SHIFT       (0x00u)
#define Salida_DRIVE_MODE_MASK        (0x07u << Salida_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Salida_H */


/* [] END OF FILE */
