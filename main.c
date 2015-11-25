#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "lpd8806lib.h"
#include "simpletools.h"

/*
 * main.c
 *
 * Currently contains a sample demonstration, just to prove the LED library is working correctly.
 */
int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	initLEDStrip();

	int x = 0;
	uint8_t r, g, b;
	while(1)
	{
		if (x == 0)
		{
			r = 127;
			g = b = 0;
		} else if (x == 1)
		{
			g = 127;
			r = b = 0;
		} else
		{
			b = 127;
			r = g = 0;
		}
		int i;
		for(i = 0; i < 32; i++)
			setRGB(i, r, g, b);

		showStrip();
		x++;
		if (x > 2) x = 0;

		SysCtlDelay(20000000);
	}

}
