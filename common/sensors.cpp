#include "sensors.h"


int readSensor(SensorType sensor, uint8_t *data)
{
    switch(sensor) {
	case TEMP:
	    getTemp(data);
	    break;
	case SDCARD:
	    detectSD(data);
	    break;
	case BUTTON:
	    getButton(data);
	    break;
    }

    return 0;
}

int getTemp(uint8_t *temperature)
{
    //TODO:implement detection!!
    *temperature = 20; //placeholder

    return 0;
}

int detectSD(uint8_t *cardDetected)
{
    //TODO:implement detection!!
    *cardDetected = 1; //placeholder

    return 0;
}

int getButton(uint8_t *pushed)
{
    //TODO:implement detection!!
    *pushed = 1; //placeholder

    return 0;
}
