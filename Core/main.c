/*
 * Core.c
 *
 * Created: 04/12/2020 08.57.27
 * Author : sofus
 */

#include "main.h"

static _Bool button_pressed = 0;

ISR ( PCINT0_vect )
{
	if ( !button_pressed ) {
		switch_menu();
		button_pressed = 1;
	}
	else {
		button_pressed = 0;
	}
}

// used to initiate interrupt on change.
static void _init_iopc ( void )
{
	// Enable pin change interrupt on PB4
	PCICR |= ( 1<<PCIE0 );
	PCMSK0 |= ( 1<<PCINT4 );
}

static void _init_ports ( void )
{
	DDRE |= ( 1<<PE3 )		// RGB LED - Blue
	        |  ( 1<<PE4 )	// RGB LED - Green
	        |  ( 1<<PE5 );	// RGB LED - Red

	DDRH |= ( 1<<PH3 );		// Pump relay
}

int main ( void )
{
	_init_ports();
  
	_init_iopc();

	init_status_light();

	init_sensors();

	init_menu();

	sei();

	while ( 1 ) {
	}
}
