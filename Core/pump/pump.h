/*
 * pump.h
 *
 * Created: 08/12/2020 12.40.58
 *  Author: sofus
 */


#ifndef PUMP_H_
#define PUMP_H_

#include <avr/sfr_defs.h>

#include "../main.h"

#define PUMP_PORT		PH3
#define PUMP_REGISTRY	PORTH

void start_pump(void);
void stop_pump(void);
_Bool is_pump_running(void);

#endif /* PUMP_H_ */