/**
 * Author: Dominik Egger
 * Copyright: Distributed Organisms B.V. (DoBots)
 * Date: Oct 23, 2014
 * License: LGPLv3+, Apache, and/or MIT, your choice
 */
#pragma once

#include "nrf_soc.h"

#include "util/cs_BleError.h"

/*
 * get temperature from softdevice
 */
inline int32_t getTemperature() {
	int32_t temperature;
	uint32_t err_code;

	err_code = sd_temp_get(&temperature);
	APP_ERROR_CHECK(err_code);

//	LOGd("raw temp: %d", temperature);
//	LOGi("temp: %d", temperature / 4);

	temperature = (temperature / 4);

	return temperature;
}
