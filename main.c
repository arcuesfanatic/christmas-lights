#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#define C4 261
#define D4 293
#define E4 329
#define F4 349
#define G4 392

/*
 * main.c
 */
int main(void) {
    
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput( GPIO_PORTD_BASE, GPIO_PIN_0);

    while(1) {
    	//Plays each of the notes in the tune Jingle Bells, in a half-scale pattern
    	playNote(C4);   
        SysCtlDelay(5000000);
    	playNote(D4);
        SysCtlDelay(5000000);
    	playNote(E4);
        SysCtlDelay(5000000);
        playNote(F4);
        SysCtlDelay(5000000);
        playNote(G4);
        SysCtlDelay(5000000);
    }

    
}

void playNote(uint32_t delay) {
    	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
        SysCtlDelay(16000000/delay);
}
