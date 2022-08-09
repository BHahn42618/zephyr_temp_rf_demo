#include <zephyr.h>
#include <string.h>
#include <soc.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <sys/printk.h>
#include "hdc1010.h"

static struct device *hdc1010_dev;


int get_hdc1010_val(struct sensor_value *val)
{
	if (sensor_sample_fetch(hdc1010_dev)) {
		printk("Failed to fetch sample for device %s\n",
		       DT_LABEL(DT_INST(0, ti_hdc1010)));
		return -1;
	}

	if (sensor_channel_get(hdc1010_dev,
			       SENSOR_CHAN_AMBIENT_TEMP,
			       &val[0])) {
		return -1;
	}

	if (sensor_channel_get(hdc1010_dev,
			       SENSOR_CHAN_HUMIDITY,
			       &val[1])) {
		return -1;
	}

	return 0;
}

int hdc1010Init(void)
{
	struct sensor_value hdc1010_val[2];
	hdc1010_dev = device_get_binding(DT_LABEL(DT_INST(0, ti_hdc1010)));
	if (hdc1010_dev == NULL) {
		printk("Failed to get %s device\n", DT_LABEL(DT_INST(0, ti_hdc1010)));
		return -1;
	}

	if (get_hdc1010_val(hdc1010_val)) {
		printk("Failed to fetch T|RH value\n");
		return -1;
	}
	return 0;

}

int getData(int (*temp)[2], int *humidity)
{
	struct sensor_value hdc1010_val[2];
	int err;
	err=get_hdc1010_val(hdc1010_val);
	if(err!=0){
		return -1;
	}
	if (!get_hdc1010_val(hdc1010_val)) {
		*(*temp + 0) = hdc1010_val[0].val1;
		//temp++;
		*(*temp + 1) = hdc1010_val[0].val2/100000;
		*humidity = hdc1010_val[1].val1;
		printk("T: %d.%d C | RH: %d%%\n",
		       hdc1010_val[0].val1,
		       hdc1010_val[0].val2/100000,
		       hdc1010_val[1].val1);
	} else {
		printk("Failed to fetch T|RH values\n");
		return -1;
	}
	return 0;
}

