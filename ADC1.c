#include <avr/io.h>
uint16_t sensorT();
int suhu;

uint16_t suhuA()
{
		
		ADMUX= 0b01000000;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		suhu = ADCW /2;
		return suhu;
}

uint16_t suhuB()
{
		ADMUX= 0b01000001;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		suhu = ADCW /2;
		return suhu;
}

uint16_t suhuC()
{
		ADMUX= 0b01000010;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		suhu = ADCW /2;
		return suhu;
}


uint16_t sensorT()
{
		ADMUX= 0b01000100;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		return ADCW;
}

uint16_t TargetSuhu()
{
		ADMUX= 0b01000101;			// inisialisasi ADC 0
		ADCSRA= 0x84;				// set ADCSRA dengan nilai prescaller 16
		ADCSRA |=(1<<ADSC);						// start konversi ADC
		loop_until_bit_is_set(ADCSRA, ADIF);	// pantau nilai ADIF
		ADCSRA |=(1<<ADIF);		
		return ADCW;
}


