/*******************************************************************************
* File Name: isrEntrada.h
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
#if !defined(CY_ISR_isrEntrada_H)
#define CY_ISR_isrEntrada_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrEntrada_Start(void);
void isrEntrada_StartEx(cyisraddress address);
void isrEntrada_Stop(void);

CY_ISR_PROTO(isrEntrada_Interrupt);

void isrEntrada_SetVector(cyisraddress address);
cyisraddress isrEntrada_GetVector(void);

void isrEntrada_SetPriority(uint8 priority);
uint8 isrEntrada_GetPriority(void);

void isrEntrada_Enable(void);
uint8 isrEntrada_GetState(void);
void isrEntrada_Disable(void);

void isrEntrada_SetPending(void);
void isrEntrada_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrEntrada ISR. */
#define isrEntrada_INTC_VECTOR            ((reg32 *) isrEntrada__INTC_VECT)

/* Address of the isrEntrada ISR priority. */
#define isrEntrada_INTC_PRIOR             ((reg32 *) isrEntrada__INTC_PRIOR_REG)

/* Priority of the isrEntrada interrupt. */
#define isrEntrada_INTC_PRIOR_NUMBER      isrEntrada__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrEntrada interrupt. */
#define isrEntrada_INTC_SET_EN            ((reg32 *) isrEntrada__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrEntrada interrupt. */
#define isrEntrada_INTC_CLR_EN            ((reg32 *) isrEntrada__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrEntrada interrupt state to pending. */
#define isrEntrada_INTC_SET_PD            ((reg32 *) isrEntrada__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrEntrada interrupt. */
#define isrEntrada_INTC_CLR_PD            ((reg32 *) isrEntrada__INTC_CLR_PD_REG)



#endif /* CY_ISR_isrEntrada_H */


/* [] END OF FILE */
