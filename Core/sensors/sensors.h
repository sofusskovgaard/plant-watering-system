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

#define WATER_LOW		water_level <= 128
#define WATER_MIDDLE	water_level <= 200 && water_level > 128
#define WATER_HIGH		water_level > 200

#define MOISTURE_LOW	soil_moisture <= 200
#define MOISTURE_MIDDLE soil_moisture <= 300 && soil_moisture > 200
#define MOISTURE_HIGH	soil_moisture > 300

extern unsigned int soil_moisture;
extern unsigned int water_level;

// 0 = Soil moisture
// 1 = Water level

extern unsigned int port_cnt;

void init_sensors ( void );



#endif /* SENSORS_H_ */