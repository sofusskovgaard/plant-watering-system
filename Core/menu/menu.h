/*
 * menu.h
 *
 * Created: 07/12/2020 11.13.35
 *  Author: sofus
 */

#ifndef MENU_H_
#define MENU_H_

#include "../main.h"
#include "../vendor/lcd.h"
#include "../sensors/sensors.h"

void init_menu ( void );
void switch_menu ( void );
void render_menu ( void );

#endif /* MENU_H_ */