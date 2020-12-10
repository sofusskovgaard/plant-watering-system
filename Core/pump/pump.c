/*
 * pump.c
 *
 * Created: 08/12/2020 12.40.52
 *  Author: sofus
 */

#include "pump.h"

void start_pump(void)
{
	PUMP_REGISTRY |= (1<<PUMP_PORT);
}

void stop_pump(void)
{
	PUMP_REGISTRY &= ~(1<<PUMP_PORT);
}

_Bool is_pump_running(void)
{
	return bit_is_set(PUMP_REGISTRY, PUMP_PORT);
}