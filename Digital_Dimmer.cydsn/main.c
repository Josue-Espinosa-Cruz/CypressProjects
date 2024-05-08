/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

unsigned short count = 0;
unsigned short countSeg = 0;

CY_ISR(Timer) // Timer interruption
{
    count++;
    if(count==12000)
    {
        countSeg++;
    }
}

CY_ISR(Cross) // Cross Interruption
{
    count=0;
}

unsigned char keyBoard (void) // Detect key
{
    unsigned char car;
    
    Control_Write(0x01);
    car = Status_Read() & 0x0F;
    
    switch(car)
    {
        case 0x01:
            return 1;
        break;
        case 0x02:
            return 4;
        break;
        case 0x04:
            return 7;
        break;
        case 0x08:
            return 14;//----------------------------
        break;     
    }
    
    Control_Write(0x02);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 2; 
        break;
        case 0x02:
            return 5;
        break;
        case 0x04:
            return 8;
        break;
        case 0x08:
            return 0;
        break;     
    }
    
    Control_Write(0x04);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 3;
        break;
        case 0x02:
            return 6;
        break;
        case 0x04:
            return 9;
        break;
        case 0x08:
            return 15;
        break;     
    }
    
    Control_Write(0x08);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 10;
        break;
        case 0x02:
            return 11;
        break;
        case 0x04:
            return 12;
        break;
        case 0x08:
            return 13;
        break;     
    }
    return 20;
}

void LCD_Text(unsigned char x, unsigned char y, char8 const text[])
{
    LCD_Position(x,y);
    LCD_PrintString(text);
}

unsigned char General_Menu(unsigned char intensity, unsigned char time)
{
    unsigned char key;
    
    char8 const textInt[]="Intensity(A):   %"; 
    unsigned char lgthInt = sizeof(textInt)/sizeof(textInt[0]);
    char8 const textTime[]="Time(B):   s"; 
    unsigned char lgthTime = sizeof(textTime)/sizeof(textTime[0]);
    
    LCD_Text(0,0,textInt);
    LCD_Position(0,lgthInt);
    LCD_PrintNumber(intensity);
    
    LCD_Text(1,0,textTime);
    LCD_Position(0,lgthTime);
    LCD_PrintNumber(time);
    
    LCD_Text(2,0,"Start Dimmer: C");
    
    for(unsigned char i;i!=1;)
    {
        key = keyBoard();
        if(key>9 && key<13)
        {
            switch (key)
            {
                case 10:
                    return 1;
                break;
                
                case 11:
                    return 2;
                break;
                
                case 12:
                    return 3;
                break;
            }
            i=1;
        }
    }
    return 0;    
}

unsigned char Intensity_Box(unsigned short intensity)
{
    unsigned char number[3]={0,0,0};    //Save numbers to calculate intensity
    unsigned char key=0;                //Assign keyboard values
    unsigned char countNumber=0;        //Count digits
    unsigned char result=0;
    
    char8 const textInt[]="Intensity(%):"; 
    unsigned char lgthInt = sizeof(textInt)/sizeof(textInt[0]);
    
    if(intensity<1000)
    {
        LCD_Text(0,0,textInt);
        LCD_Position(0,lgthInt);
        LCD_PrintNumber(intensity);
    }
    else if(intensity<100)
    {
        LCD_Text(0,0,"Intensity(%):0");
        LCD_Position(0,lgthInt+1);
        LCD_PrintNumber(intensity);
    }
    else if(intensity<10)
    {
        LCD_Text(0,0,"Intensity(%):00");
        LCD_Position(0,lgthInt+2);
        LCD_PrintNumber(intensity);
    }
    
    LCD_Text(1,0,"Enter:*");
    LCD_Text(1,9,"Delete:#");
    LCD_Text(2,0,"Cancel:A");
    
    for(unsigned char i=0;i!=1;)
    {
        key = keyBoard();
     
        if(key>=0 && key<=9)
        {
            if(countNumber==0 && key!=0)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,15);
                LCD_PrintNumber(key);
            }
            else if(countNumber==1)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,14);
                LCD_PrintNumber(key);
            }
            else if(countNumber==2 && number[0]==1 && key==0)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,13);
                LCD_PrintNumber(key);
            }
        }
        else if(key==10)
        {
            i = 1;
            result = 0;
        }
        else if(key==14)
        {
            if(countNumber==1)
            {
                result = number[0];
            }
            else if(countNumber==2)
            {
                result = ((number[0])*10)+number[1];
            }
            else if(countNumber==3)
            {
                result = ((number[0])*100)+(number[1]*10)+number[2];
            }
            
            i = 1;
        }
         else if(key==15)
        {
            if(countNumber==1)
            {
                LCD_Text(0,lgthInt+2,"0");
                countNumber--;
                number[countNumber] = 0;
            }
            else if(countNumber==2)
            {
                LCD_Text(0,lgthInt+1,"0");
                LCD_Position(0,lgthInt+2);
                LCD_PrintNumber(number[0]);
                
                countNumber--;
                number[countNumber] = 0;
            }
            else if(countNumber==3)
            {
                LCD_Text(0,lgthInt,"0");
                LCD_Position(0,lgthInt+1);
                LCD_PrintNumber((number[0]*10)+number[1]);
                
                countNumber--;
                number[countNumber] = 0;
            }
            
        }
    }
    
    return result;
    
}

unsigned short Time_Box(unsigned short time)
{
    unsigned char number[3]={0,0,0};    //Save numbers to calculate intensity
    unsigned char key=0;                //Assign keyboard values
    unsigned char countNumber=0;        //Count digits
    unsigned short result=0;
    
    char8 const textTime[]="Time(s):"; 
    unsigned char lgthTime = sizeof(textTime)/sizeof(textTime[0]);
    
    if(time<1000)
    {
        LCD_Text(0,0,textTime);
        LCD_Position(0,lgthTime);
        LCD_PrintNumber(time);
    }
    else if(time<100)
    {
        LCD_Text(0,0,"Time(s):0");
        LCD_Position(0,lgthTime+1);
        LCD_PrintNumber(time);
    }
    else if(time<10)
    {
        LCD_Text(0,0,"Time(s):00");
        LCD_Position(0,lgthTime+2);
        LCD_PrintNumber(time);
    }
    
    LCD_Text(1,0,"Enter:*");
    LCD_Text(1,9,"Delete:#");
    LCD_Text(2,0,"Cancel:B");
    
    for(unsigned char i=0;i!=1;)
    {
        key = keyBoard();
     
        if(key>=0 && key<=9)
        {
            if(countNumber==0 && key!=0)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,lgthTime+2);
                LCD_PrintNumber(key);
            }
            else if(countNumber==1)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,lgthTime+1);
                LCD_PrintNumber((number[0]*10)+number[1]);
            }
            else if(countNumber==2)
            {
                number[countNumber] = key;
                countNumber++;
                LCD_Position(0,lgthTime);
                LCD_PrintNumber(100+(number[1]*10)+number[2]);
            }
        }
        else if(key==11)
        {
            i = 1;
            result = 0;
        }
        else if(key==14)
        {
            if(countNumber==1)
            {
                result = number[0];
            }
            else if(countNumber==2)
            {
                result = ((number[0])*10)+number[1];
            }
            else if(countNumber==3)
            {
                result = ((number[0])*100)+(number[1]*10)+number[2];
            }
            
            i = 1;
        }
        else if(key==15)
        {
            if(countNumber==1)
            {
                LCD_Text(0,lgthTime+2,"0");
                countNumber--;
                number[countNumber] = 0;
            }
            else if(countNumber==2)
            {
                LCD_Text(0,lgthTime+1,"0");
                LCD_Position(0,lgthTime+2);
                LCD_PrintNumber(number[0]);
                
                countNumber--;
                number[countNumber] = 0;
            }
            else if(countNumber==3)
            {
                LCD_Text(0,lgthTime,"0");
                LCD_Position(0,lgthTime+1);
                LCD_PrintNumber((number[0]*10)+number[1]);
                
                countNumber--;
                number[countNumber] = 0;
            }
            
        }
    }
    
    return result;
    
}

void Dimmer(unsigned char intensity,unsigned char time)
{
    unsigned char key;
    unsigned char Seg = 0;
    unsigned short resta = 0;
    
    char8 const textInt[]="Intensity(%):"; 
    unsigned char lgthInt = sizeof(textInt)/sizeof(textInt[0]);
    LCD_Text(0,0,textInt);
    LCD_Position(0,lgthInt);
    LCD_PrintNumber(intensity);
    
    char8 const textTime[]="Time(s):"; 
    unsigned char lgthTime = sizeof(textTime)/sizeof(textTime[0]);
    LCD_Position(1,lgthTime);
    LCD_PrintNumber(time);
    
    LCD_Text(0,2,"Cancel: C"); 
    
    Timer_Wakeup();
    
    isrTimer_StartEx(Timer);
    isrCross_StartEx(Cross);
    
    for(unsigned char i=0;i!=1;)
    {
        key = keyBoard();
        
        if(countSeg==time || key==12)
        {
            Dimmer_Write(1);
            i++;
        }
        
        if(intensity==0)        //Pin "Salida" is on pull-down configuration
        {
            Dimmer_Write(1);
        }
        else if(count<=intensity)
        {
            Dimmer_Write(0);
        }
        else
        {
            Dimmer_Write(1);
        }
        
        if(Seg != countSeg)
        {
            resta = time - Seg;
            
            if(resta<10)
            {
                LCD_Position(1,lgthTime+2);
                LCD_PrintNumber(time-countSeg);
            }
            else if(resta<100)
            {
                LCD_Position(1,lgthTime+1);
                LCD_PrintNumber(time-countSeg);
            }
            else if(resta<1000)
            {
                LCD_Position(1,lgthTime);
                LCD_PrintNumber(time-countSeg);
            }
            
            Seg = countSeg;
        }
    }
    
    isrTimer_Disable();
    isrCross_Disable();
    isrTimer_Stop();
    
    Timer_Sleep();
}

int main(void)
{
    unsigned char State = 0;
    unsigned char Intensity = 0;
    unsigned char Time = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    
    LCD_Start();
    Timer_Start();
    Timer_Sleep();
    
    for(;;)
    {
        switch(State)
        {
            case 0:
                State = General_Menu(Intensity,Time);
            break;
            
            case 1:
                Intensity = Intensity_Box(Intensity);
                State = 0;
            break;
            
            case 2:
                Time = Time_Box(Time);
                State = 0;
            break;
            
            case 3:
                Dimmer(Intensity,Time);
                State = 0;
            break;
        }       
    }

    
}


/* [] END OF FILE */




/*

#include "project.h"
int contador=0;
int contador2=0;
int contador3=0;
int valor=0;
int valor2=0;
int tecla=0;
int numero[3]={0,0,0};
int numeroT[3]={0,0,0};
int num=0;
int numT=0;
int t1=0;
int resta=0;
int a=0;
int b=0;
int num2=0;
char permisoPWM2=0;
char inte=0;
char permisoPWM=0;
char permisoT=0;
char permisoT2=0;


CY_ISR(Timer)
{
    contador++;
    if(permisoT2==1)
    {
        contador2++;
        if(contador2==12000)
        {
            contador3++;
            contador2=0;
        }
    }
}

CY_ISR(R)
{
    contador=0;
}

unsigned char teclado (void)
{
    unsigned char car;
    
    Control_Write(0x01);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 2;
        break;
        case 0x02:
            return 5;
        break;
        case 0x04:
            return 8;
        break;
        case 0x08:
            return 15;//----------------------------
        break;     
    }
    
    Control_Write(0x02);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 3; 
        break;
        case 0x02:
            return 6;
        break;
        case 0x04:
            return 9;
        break;
        case 0x08:
            return 1;
        break;     
    }
    
    Control_Write(0x04);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 4;
        break;
        case 0x02:
            return 7;
        break;
        case 0x04:
            return 10;
        break;
        case 0x08:
            return 16;
        break;     
    }
    
    Control_Write(0x08);
    car = Status_Read() & 0x0F;
    switch(car)
    {
        case 0x01:
            return 11;
        break;
        case 0x02:
            return 12;
        break;
        case 0x04:
            return 13;
        break;
        case 0x08:
            return 14;
        break;     
    }
    return 20;
}

int main(void)
{
    CyGlobalIntEnable; // Enable global interrupts

    Timer_Start();
    
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("% Velocidad");
    LCD_Position(0,13);
    LCD_PrintString("000");
    LCD_Position(1,0);
    LCD_PrintString("Tiempo");
    
    isrTimer_StartEx(Timer);
    isrEntrada_StartEx(R);
    
    for(;;)
    {
        tecla=teclado();
       
        if (tecla==20 && inte==0)
        {
            inte=1;
        }
        if (tecla!=20 && inte==1)
        {
            inte=0;
            if (tecla==11 && permisoT==0)   //Enable dimmer 
            {
                if (permisoPWM==0)
                {
                    permisoPWM=1;
                    LCD_Position(0,13);
                    LCD_PrintString("000");
                }
                else
                {
                    permisoPWM=0;
                }
            }
            else if(tecla!=11 && tecla!=12 && tecla!=13 && tecla!=14 && tecla!=15 && tecla!=16 && permisoPWM==1 && a<=2)//Ingresar PWM
            {
                
                numero[a]=tecla-1;
                a+=1;
                if (a==1)
                {
                    LCD_Position(0,15);
                    num=numero[0];
                    LCD_PrintNumber(num);
                }
                else if (a==2)
                {
                    num=((numero[0])*10)+numero[1];
                    LCD_Position(0,14);
                    LCD_PrintNumber(num);
                }
                else if (a==3)
                {
                    if(numero[0]==1 && numero[1]==0 && numero[2]==0)
                    {
                        num=((numero[0])*100)+(numero[1]*10)+numero[2];
                        LCD_Position(0,13);
                        LCD_PrintNumber(num);
                        numero[0]=0;
                        numero[1]=0;
                        numero[2]=0;
                    }
                    else
                    {
                        a=2;
                    }
                }
            }
            else if (tecla==12 && permisoPWM==1 && permisoPWM2==0) //Select dimmer
            {
                permisoPWM2=1;
                num2=num;
                a=0;
                permisoPWM=0;
                num=0;
                numero[0]=0;
                numero[1]=0;
                numero[2]=0;
                resta=100-num2;
            }
            
            else if(tecla ==13 && permisoPWM==0) //Enable time
            {
                if (permisoT==0)
                {
                    permisoT=1;
                }
                else
                {
                    permisoT=0;
                }
            }
            else if (tecla==14 && permisoT==1 && permisoT2==0)//Ejeutar tiempo
            {
                permisoT2=1;
                t1=numT;
                b=0;
                permisoT=0;
                numT=0;
                numeroT[0]=0;
                numeroT[1]=0;
                numeroT[2]=0;
               
            }
            else if(tecla!=11 && tecla!=12 && tecla!=13 && tecla!=14 && tecla!=15 && tecla!=16 && permisoT==1 && b<=2)//Ingresar tiempo
            {
                numeroT[b]=tecla-1;
                b+=1;
                
                if (b==1)
                {
                    LCD_Position(1,15);
                    numT=numeroT[0];
                    LCD_PrintNumber(numT);
                }
                else if (b==2)
                {
                    numT=((numeroT[0])*10)+numeroT[1];
                    LCD_Position(1,14);
                    LCD_PrintNumber(numT);
                }
                else if (b==3)
                {
                    numT=((numeroT[2]*100)+(numeroT[0])*10)+numeroT[1];
                    LCD_Position(1,13);
                    LCD_PrintNumber(numT);
                }
            }
            
            
        }
        if(permisoPWM2==1 && permisoT2==1) // Ejecuta tiempo y velocidad
        {
            if(contador3<=t1)
            {
                    if(resta==100)
                    {
                        Salida_Write(0);
                    }
                    else if(resta==0)
                    {
                        Salida_Write(1);
                    }
                    else if(contador<=resta)
                    {
                        Salida_Write(0);
                    }
                    else
                    {
                        Salida_Write(1);
                    }
            }
            else
            {
                Salida_Write(0);
                permisoT=0;
                permisoT2=0;
                contador3=0;
                permisoPWM2=0;
                permisoPWM=0;
            }
        }
    }
}

*/
/* [] END OF FILE */
