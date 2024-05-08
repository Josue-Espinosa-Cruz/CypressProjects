/*******************************************************************************
* File Name: Cruce.h  
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

#if !defined(CY_PINS_Cruce_ALIASES_H) /* Pins Cruce_ALIASES_H */
#define CY_PINS_Cruce_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Cruce_0			(Cruce__0__PC)
#define Cruce_0_PS		(Cruce__0__PS)
#define Cruce_0_PC		(Cruce__0__PC)
#define Cruce_0_DR		(Cruce__0__DR)
#define Cruce_0_SHIFT	(Cruce__0__SHIFT)
#define Cruce_0_INTR	((uint16)((uint16)0x0003u << (Cruce__0__SHIFT*2u)))

#define Cruce_INTR_ALL	 ((uint16)(Cruce_0_INTR))


#endif /* End Pins Cruce_ALIASES_H */


/* [] END OF FILE */
