#include <avr/io.h>

#define SERVO_PORT  PORTB
#define SERVO_DDR   DDRB

// Upto 8 servos (since pulses are generated in
// sequence + only one port is used).
#define N_SERVOS    8

// Servo times (this is Futaba timing).
#define SERVO_MIN    920 // microseconds
#define SERVO_MAX   2100 // microseconds
#define SERVO_MID   (SERVO_MIN + SERVO_MAX) / 2

// Time between servo pulses. 
#define SERVO_FRAME 20000 // microseconds (50Hz)

// Time slot available for each servo.
#define SERVO_TIME_DIV (SERVO_FRAME / N_SERVOS)

#if (SERVO_TIME_DIV < SERVO_MAX + 50)
#warning "Output fewer servo signals or increase SERVO_FRAME"
#endif
#if ((SERVO_TIME_DIV * (F_CPU / 1000000UL)) >= 0xFF00)
#warning "Output more servo signals or decrease SERVO_FRAME (or use the prescaler)"
#endif

// Computing timer ticks given microseconds.
// Note, this version works out ok with even MHz F_CPU (e.g., 1, 2, 4, 8, 16 MHz).
// (Not a good idea to have this end up as a floating point operation)
#define US2TIMER1(us) ((us) * (uint16_t)(F_CPU / 1E6))

// Servo times - to be entered as timer1 ticks (using US2TIMER1).
// This must be updated with interrupts disabled.
volatile uint16_t servoTime[N_SERVOS];
uint16_t servoData[10];
uint8_t tmpCRC[2] ;
// Servo output allocation (on a single port currently).
const static uint8_t servoOutMask[N_SERVOS] = {
    0b00000001, // PX0
    0b00000010, // PX1
    0b00000100, // PX2
    0b00001000, // PX3
    0b00010000, // PX4
    0b00100000, // PX5
    0b01000000, // PX6
    0b10000000, // PX7
};
// Servo mask is just the above masks ored.
#define SERVO_MASK 0xff
