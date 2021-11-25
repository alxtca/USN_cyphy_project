#include "send-distance-request.h"

//calculate height ( based on data.xml )
int calculateHeight(int & d);

int takeHeightMeasurement() {

    //request distance from RP1
    char request_message[] = "height";
    int distance = sendRequest(request_message);

    return calculateHeight(distance);
}

int calculateHeight(int & distance) {
    //get sensor position from data.xml
    int sensor_position_height = 230; //replace dummy 230 with data reading from data.xml

    return (sensor_position_height - distance);
}