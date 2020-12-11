/*
 * sensors.h
 *
 * Created: 07/12/2020 11.20.20
 *  Author: sofus
 */


#ifndef SENSORS_H_
#define SENSORS_H_

#include <math.h>

#include "../main.h"
#include "../menu/menu.h"
#include "../pump/pump.h"

#ifndef WATER_LOW_VALUE
#define WATER_LOW_VALUE 25
#endif

#ifndef WATER_HIGH_VALUE
#define WATER_HIGH_VALUE 100
#endif

#define WATER_LOW		water_level <= WATER_LOW_VALUE
#define WATER_MIDDLE	water_level <= WATER_HIGH_VALUE && water_level > WATER_LOW_VALUE
#define WATER_HIGH		water_level > WATER_HIGH_VALUE

#ifndef MOISTURE_LOW_VALUE
#define MOISTURE_LOW_VALUE 25
#endif

#ifndef MOISTURE_HIGH_VALUE
#define MOISTURE_HIGH_VALUE 100
#endif

#define MOISTURE_LOW	soil_moisture <= MOISTURE_LOW_VALUE
#define MOISTURE_MIDDLE soil_moisture <= MOISTURE_HIGH_VALUE && soil_moisture > MOISTURE_LOW_VALUE
#define MOISTURE_HIGH	soil_moisture > MOISTURE_HIGH_VALUE

extern unsigned int soil_moisture;
extern unsigned int water_level;

// 0 = Soil moisture
// 1 = Water level

extern unsigned int port_cnt;

void init_sensors ( void );



#endif /* SENSORS_H_ */