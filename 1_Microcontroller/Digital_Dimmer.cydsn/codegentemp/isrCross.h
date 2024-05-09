/*******************************************************************************
* File Name: isrCross.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isrCross_H)
#define CY_ISR_isrCross_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrCross_Start(void);
void isrCross_StartEx(cyisraddress address);
void isrCross_Stop(void);

CY_ISR_PROTO(isrCross_Interrupt);

void isrCross_SetVector(cyisraddress address);
cyisraddress isrCross_GetVector(void);

void isrCross_SetPriority(uint8 priority);
uint8 isrCross_GetPriority(void);

void isrCross_Enable(void);
uint8 isrCross_GetState(void);
void isrCross_Disable(void);

void isrCross_SetPending(void);
void isrCross_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrCross ISR. */
#define isrCross_INTC_VECTOR            ((reg32 *) isrCross__INTC_VECT)

/* Address of the isrCross ISR priority. */
#define isrCross_INTC_PRIOR             ((reg32 *) isrCross__INTC_PRIOR_REG)

/* Priority of the isrCross interrupt. */
#define isrCross_INTC_PRIOR_NUMBER      isrCross__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrCross interrupt. */
#define isrCross_INTC_SET_EN            ((reg32 *) isrCross__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrCross interrupt. */
#define isrCross_INTC_CLR_EN            ((reg32 *) isrCross__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrCross interrupt state to pending. */
#define isrCross_INTC_SET_PD            ((reg32 *) isrCross__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrCross interrupt. */
#define isrCross_INTC_CLR_PD            ((reg32 *) isrCross__INTC_CLR_PD_REG)



#endif /* CY_ISR_isrCross_H */


/* [] END OF FILE */
