/*
* sensors.c
*
* Created: 07/12/2020 11.20.13
*  Author: sofus
*/

#include "sensors.h"

unsigned int soil_moisture;
unsigned int water_level;

unsigned int port_cnt = 0;	// used to determine current port in use

// used to initiate the Auto Trigger timer.
static void _init_timer ( void )
{
	TCCR1B |= ( 1<<WGM12 );		// Specify mode of operation - CTC
	TCCR1B |= ( 1<<CS12 );		// Set prescaler
	TIMSK1 |= ( 1<<OCIE1A );	// Enable Compare B Match Interrupt
	OCR1A = 3124;				// Specify when timer should throw interrupt
	OCR1B = 1562;
}

// used to initiate the ADC.
void init_sensors ( void )
{
	_init_timer();

	ADMUX  |= ( 1<<REFS0 );													// Voltage reference selection
	ADCSRA |= ( 1<<ADSC );													// Start conversion
	ADCSRA |= ( 1<<ADIE );													// Enable Interrupt
	ADCSRA |= ( 1<<ADEN );													// Enable ADC
	ADCSRA |= ( 1<<ADATE );													// Enable Auto Trigger
	ADCSRA |= ( 1<<ADPS2 ) | ( 1<<ADPS1 ) | ( 1<<ADPS0 );					// Specify ADC prescaler division factor
	ADCSRB |= ( 1<<ADTS2 ) | ( 1<<ADTS0 );									// Specify Auto Trigger Source - Timer/Counter1 Compare Match B
	ADCSRB |= ( 1<<MUX5 );
	DIDR1  |= ( 1<<ADC10D ) | ( 1<<ADC11D );	// Disable digital input on ports
}

// used to calculate the soil moisture and to populate the global soil_moisture variable.
static void _calcualte_soil_moisture ( unsigned int adc_data )
{
	soil_moisture = adc_data;
}

// used to calculate the water level and to populate the global water_level variable.
static void _calculate_water_level ( unsigned int adc_data )
{
	water_level = adc_data;
}

// used to change ports based on the current active port.
static void _change_ports ( void )
{
	ADCSRA &= 0b01111111;

	switch ( port_cnt ) {

		case 0: // Soil moisture
			ADMUX &= 0b11100000;
			ADMUX |= ( 1<<MUX0 ) | ( 1<<MUX1 ); // Enable water level
			port_cnt++;
			break;

		case 1: // Water level
			ADMUX &= 0b11100000; // Enable thermistor
			ADMUX |= ( 1<<MUX1 );
			port_cnt = 0;
			break;

		default: // Fail safe
			port_cnt = 0;
			break;
	}

	ADCSRA |= ( 1<<ADEN ) | ( 1<<ADSC );
}

// used to handle all ADC calculation.
static void _handle_calculation ( unsigned int adc_data )
{
	switch ( port_cnt ) {
		case 0: // Soil moisture
			_calcualte_soil_moisture ( adc_data );
			break;

		case 1: // Water level
			_calculate_water_level ( adc_data );
			break;
	}
}

// used to handle status changes.
static void _handle_status ( void )
{
	if ( WATER_HIGH ) {
		set_status ( 0 );
	}
	else if ( WATER_MIDDLE ) {
		set_status ( 1 );
	}
	else if ( WATER_LOW ) {
		set_status ( 2 );
	}
}

// used to handle pump
static void _handle_pump ( void )
{
	if ( WATER_LOW || MOISTURE_HIGH ) {

		if ( is_pump_running() ) {
			stop_pump();
		}

	}
	else {

		if ( MOISTURE_LOW ) {
			start_pump();
		}

	}
}

ISR ( ADC_vect )
{
	_handle_calculation ( ADC );
	_handle_pump();
	_handle_status();
	render_menu();
}

ISR ( TIMER1_COMPA_vect )
{
	_change_ports();
}