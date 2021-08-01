#include "temp.h"

int main() {
    MQTTAsync temp_sensor;
    temp_init(&temp_sensor);

    while (1) {
        sleep(1);

        int sensor_data = (int) (random() % 80) + 20;
        printf("sensor data is %d\n", sensor_data);
        temp_publish(temp_sensor, sensor_data);
    }

    return 0;
}
