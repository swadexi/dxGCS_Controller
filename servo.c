#include "all.h"

//Copied From Paparazzy
//for dxAutoPilot URO



void servoStart(void)
{
    // Outputs
    SERVO_DDR |= SERVO_MASK;
    // Setupt a first compare match
    OCR1A = TCNT1 + US2TIMER1(100);
    // start timer 1 with no prescaler
    TCCR1B = (1 << CS10);      
    // Enable interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void servoSet(uint8_t servo, uint16_t time /* microseconds */)
{
    uint16_t ticks = US2TIMER1(time);
    cli();
    servoTime[servo] = ticks;
    sei();
}


void servo_init()
{
 	uint8_t i;
    for(i = 0; i < N_SERVOS; i++) {
        servoTime[i] = US2TIMER1(SERVO_MID);
    }
	#if N_SERVOS > 2   
    servoTime[2] = US2TIMER1(SERVO_MIN);
	#endif
    servoTime[N_SERVOS-1] = US2TIMER1(SERVO_MAX);   
    servoStart();
    sei();


}
ISR(TIMER1_COMPA_vect)
{
    static uint16_t nextStart;
    static uint8_t servo;
    static bool outputHigh = true;
    uint16_t currentTime = OCR1A;
    uint8_t mask = servoOutMask[servo];
   
    if (outputHigh) {
        SERVO_PORT |= mask;
        // Set the end time for the servo pulse
        OCR1A = currentTime + servoTime[servo];
        nextStart = currentTime + US2TIMER1(SERVO_TIME_DIV);
    } else {
        SERVO_PORT &= ~mask;
        if (++servo == N_SERVOS) {
            servo = 0;
        }
        OCR1A = nextStart;
    }
    outputHigh = !outputHigh;
} 

uint8_t degreeServo(unsigned char degree)
{	int min_pulse = 900;
	int max_pulse = 2100;
	int deg = min_pulse+((max_pulse-min_pulse)*degree*1.0/180); // for 0 - 180
//	int deg = min_pulse+((max_pulse-min_pulse)*(degree+90)*1.0/180);
	return deg;
}

