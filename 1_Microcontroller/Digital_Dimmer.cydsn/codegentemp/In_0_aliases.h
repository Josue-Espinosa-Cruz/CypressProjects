/*******************************************************************************
* File Name: In_0.h  
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

#if !defined(CY_PINS_In_0_ALIASES_H) /* Pins In_0_ALIASES_H */
#define CY_PINS_In_0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define In_0_0			(In_0__0__PC)
#define In_0_0_PS		(In_0__0__PS)
#define In_0_0_PC		(In_0__0__PC)
#define In_0_0_DR		(In_0__0__DR)
#define In_0_0_SHIFT	(In_0__0__SHIFT)
#define In_0_0_INTR	((uint16)((uint16)0x0003u << (In_0__0__SHIFT*2u)))

#define In_0_INTR_ALL	 ((uint16)(In_0_0_INTR))


#endif /* End Pins In_0_ALIASES_H */


/* [] END OF FILE */
