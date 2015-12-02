#include "lpd8806lib.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

/*
 * This library is not particulary robust at the moment, as it only supports LED strips 32 LEDs in length.
 * For some reason there no data is saved if I attempt to use a dynamically allocated array.
 * Feel free to PR this repository if you find a way to support an indeterminate number of LEDs,
 * as it will make the library more robust, although that was not required for the scope of this project.
 * - Sam Beckmann (@samvbeckmann) 11/25/15
 *
 * Original implemntation courtesy Zach Archer. (@zkarcher)
 */

uint8_t buffer[97];
uint16_t bufferLen = 97;
uint16_t numLEDs = 32;

void initLEDStrip() {
	// Prep the GPIO for transmitting.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Send an empty byte to clear any buffer, prepare the strip to recieve information.
	GPIOPinWrite(GPIO_PORTB_BASE, DATA_PIN, 0);
	int i;
	for (i = 0; i < 8; i++) {
		GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, CLOCK_PIN);  // clock high
		GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, 0);  		   // clock low
	}
}

void showStrip() {
	// Step through the passed buffer, pushing the whole thing to the strip
	uint16_t i;
	for (i = 0; i < bufferLen; i++) {
		uint8_t aByte = buffer[i];

		// MSB first
		uint8_t b;
		for (b = 7;; b--) {
			GPIOPinWrite( GPIO_PORTB_BASE, DATA_PIN, (aByte >> b));

			GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, CLOCK_PIN);  // clock high
			GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, 0);  // clock low

			if (b == 0)
				break; // Can't use for loop since b is unsigned.
		}
	}
}

uint32_t getPixelColor(uint16_t idx) {
	if (idx < numLEDs) {
		uint16_t offset = idx * 3;
		return ((uint32_t) (buffer[offset] & 0x7f) << 16)
				| ((uint32_t) (buffer[offset + 1] & 0x7f) << 8)
				| (uint32_t) (buffer[offset + 2] & 0x7f);
	}

	return 0; // Pixel # is out of bounds
}

void setRGBCompact(uint16_t idx, uint32_t color) {
	if (idx < numLEDs) { // Arrays are 0-indexed, thus NOT '<='
		uint16_t offset = idx * 3;
		buffer[offset] = (color >> 16) | 0x80;
		buffer[offset + 1] = (color >> 8) | 0x80;
		buffer[offset + 2] = color | 0x80;
	}
}

// Valid color ranges: 0x0...0x7f
void setRGB(uint16_t idx, uint8_t r, uint8_t g, uint8_t b) {
	if (idx < numLEDs) {
		uint16_t offset = idx * 3;
		buffer[offset] = g | 0x80;
		buffer[offset + 1] = r | 0x80;
		buffer[offset + 2] = b | 0x80;
	}

}
