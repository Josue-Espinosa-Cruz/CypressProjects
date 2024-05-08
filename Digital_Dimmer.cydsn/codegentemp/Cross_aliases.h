/*******************************************************************************
* File Name: Cross.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Cross_ALIASES_H) /* Pins Cross_ALIASES_H */
#define CY_PINS_Cross_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Cross_0			(Cross__0__PC)
#define Cross_0_PS		(Cross__0__PS)
#define Cross_0_PC		(Cross__0__PC)
#define Cross_0_DR		(Cross__0__DR)
#define Cross_0_SHIFT	(Cross__0__SHIFT)
#define Cross_0_INTR	((uint16)((uint16)0x0003u << (Cross__0__SHIFT*2u)))

#define Cross_INTR_ALL	 ((uint16)(Cross_0_INTR))


#endif /* End Pins Cross_ALIASES_H */


/* [] END OF FILE */
