#include "Button.h"

void Button::button_interrupt()
{
	/*
	if (millis() >= last_interrupt + debounce_time) {
		last_interrupt = millis(); //update last_interrupt time
		button_pushed = true;
	}
	*/
}

void Button::do_something()
{
	//change current LED state
	//digitalWrite(LED_pin, !digitalRead(LED_pin));
}

void Button::setup()
{
	/*
	wiringPiSetup();	// Initiates library, connecting pins.
		//	WiringPi's millis() function also starts counting here.
	pinMode(LED_pin, OUTPUT);		// LED_pin as output
	pinMode(button_pin, INPUT);		// button_pin as input
	//Setting up interrupt service routine for button:
	wiringPiISR(button_pin, INT_EDGE_RISING, &button_interrupt);
	//Parameters: int wiringPiISR (int pin, int edgeType,  void (*function)(void))
	*/
}
