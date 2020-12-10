/*
 * menu.c
 *
 * Created: 07/12/2020 11.13.02
 *  Author: sofus
 */

#include "menu.h"

unsigned int menu_cnt = 0;

static void _render_value ( unsigned int val, int y )
{
	int _value = val;
	unsigned int digits = 0;

	while ( _value!=0 ) {
		_value = _value / 10;
		digits++;
	}

	lcd_gotoxy ( ( 15 - ( digits > 0 ? digits - 1 : digits ) ), y );
}

static void _render_soil_moisture ( int y )
{
	char *str[4];
	itoa ( soil_moisture, str, 10 );

	lcd_gotoxy ( 0,y );

	lcd_puts ( "Moisture:" );

	_render_value ( soil_moisture, y );
	//lcd_gotoxy ( 15, y );

	lcd_puts ( str );
}

static void _render_water_level ( int y )
{
	char *str[4];
	itoa ( water_level, str, 10 );

	lcd_gotoxy ( 0,y );

	lcd_puts ( "Water:" );

	_render_value ( water_level, y );
	//lcd_gotoxy ( 15, y );

	lcd_puts ( str );
}



void render_menu ( void )
{
	switch ( menu_cnt ) {

		case 0: // Soil moisture
			lcd_clrscr();
			_render_soil_moisture ( 0 );
			_render_water_level ( 1 );
			break;

		case 1: // Water level
			lcd_clrscr();
			_render_water_level ( 0 );
			_render_soil_moisture ( 1 );
			break;

		default:
			lcd_clrscr();
			_render_soil_moisture ( 0 );
			_render_water_level ( 1 );
			menu_cnt = 1;
			break;

	}
}

void init_menu ( void )
{
	lcd_init ( LCD_DISP_ON );
	render_menu();
}

void switch_menu ( void )
{
	menu_cnt++;
	render_menu();
}