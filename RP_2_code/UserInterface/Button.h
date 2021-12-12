#include <iostream>
//#include <wiringPi.h>


class Button //setup and action related to button
{
private:
	const int LED_pin{ 0 }; // LED_pin on GPIO.0, physical pin 11
	const int button_pin{ 1 }; //button_pin on GPIO.1, physical pin 12
	volatile unsigned long last_interrupt{ 0 }; //time of last interrupt (ms)
	const int debounce_time{ 50 }; /*time to ignore repeated interrupt
	signals after last interrupt: 15 ms*/

public:
	Button() {
		setup();
	}
	bool button_pushed{ false };	/* will switch to true upon button push.
	*  Will reset to false once associated button task has begun */
	void button_interrupt(); //Interrupt routine
	void do_something(); //What happens uppon interrupts
	void setup();

};

