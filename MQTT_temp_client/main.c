#include "temp.h"

int main() {
    MQTTAsync temp_sensor;
    temp_init(&temp_sensor);

    while (1) {
        int sensor_data = (int) (random() % 80) + 20;
        temp_publish(temp_sensor, sensor_data);
        sleep(1);
    }

    return 0;
}
