#include <wiringPi.h>
#include "gpio.h"

#define true 1
#define false 0

int isGpioInit=false;

void InitGpio()
{
    wiringPiSetup();
    printf("#####init gpio#####\n");
    isGpioInit=true;
}

void SetGPIO(int pin,int value)
{
    digitalWrite(pin,value) ;
}

void SetSide(int pin1,int pin2,int value)
{
    if(value==0)
    {
        SetGPIO(pin1,value);
        SetGPIO(pin2,value);
    }
    if(value==1)
    {
        SetGPIO(pin1,1);
        SetGPIO(pin2,0);
    }
    if(value==-1)
    {
        SetGPIO(pin1,0);
        SetGPIO(pin2,1);
    }
}

void SetCarWheel(int left,int right)
{
    if(!isGpioInit)
    {
        InitGpio();
    }
    SetSide(25,24,left);
    SetSide(23,22,left);
}