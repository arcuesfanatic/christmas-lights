/*
 * main.h
 *
 *  Created on: Nov 26, 2015
 *      Author: Sam
 */

#ifndef CHRISTMAS_LIGHTS_MAIN_H
#define CHRISTMAS_LIGHTS_MAIN_H

void
	Wheel(uint16_t pixel, uint16_t WheelPos),
	simpleChase(uint8_t rainbow, int delay, uint8_t currentPattern),
	performChase(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowChase(int delay, uint8_t currentPattern),
	theatreChase(uint8_t rainbow, int delay, uint8_t currentPattern),
	performTheatre(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowTheatre(int delay, uint8_t currentPattern),
	rainbow(uint8_t cycle, int delay, uint8_t currentPattern),
	pong(uint8_t rainbow, int delay, uint8_t currentPattern),
	performPong(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowPong(int delay, uint8_t currentPattern);

int main(void);

#endif /* MAIN_H_ */
