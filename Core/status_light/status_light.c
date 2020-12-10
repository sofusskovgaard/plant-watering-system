/*
 * status_light.c
 *
 * Created: 07/12/2020 12.59.07
 *  Author: sofus
 */

#include "status_light.h"

void set_status ( unsigned int status_code )
{
	switch ( status_code ) {
		case 0: // No issues
			OCR3A = 0;		// Red
			OCR3B = 255;	// Green
			OCR3C = 0;		// Blue
			break;

		case 1: // Running low on water
			OCR3A = 255;	// Red
			OCR3B = 165;	// Green
			OCR3C = 0;		// Blue
			break;

		case 2: // Almost no water left
			OCR3A = 255;	// Red
			OCR3B = 16;		// Green
			OCR3C = 0;		// Blue
			break;

		default:
			OCR3A = 255;	// Red
			OCR3B = 255;	// Green
			OCR3C = 255;	// Blue
			break;
	}
}

static void _init_timer ( void )
{
	TCCR3A |= ( 1<<WGM30 ) | ( 1<<COM3A1 ) | ( 1<<COM3B1 ) | ( 1<<COM3C1 );
	TCCR3B |= ( 1<<WGM32 ) | ( 1<<CS31 ) | ( 1<<CS30 );
}

void init_status_light ( void )
{
	//_init_iopc();
	_init_timer();
}