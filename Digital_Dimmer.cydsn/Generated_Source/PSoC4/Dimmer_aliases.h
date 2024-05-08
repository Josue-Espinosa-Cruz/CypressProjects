/*******************************************************************************
* File Name: Dimmer.h  
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

#if !defined(CY_PINS_Dimmer_ALIASES_H) /* Pins Dimmer_ALIASES_H */
#define CY_PINS_Dimmer_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Dimmer_0			(Dimmer__0__PC)
#define Dimmer_0_PS		(Dimmer__0__PS)
#define Dimmer_0_PC		(Dimmer__0__PC)
#define Dimmer_0_DR		(Dimmer__0__DR)
#define Dimmer_0_SHIFT	(Dimmer__0__SHIFT)
#define Dimmer_0_INTR	((uint16)((uint16)0x0003u << (Dimmer__0__SHIFT*2u)))

#define Dimmer_INTR_ALL	 ((uint16)(Dimmer_0_INTR))


#endif /* End Pins Dimmer_ALIASES_H */


/* [] END OF FILE */
