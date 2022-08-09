/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <string.h>
#include <sys/printk.h>
#include <stdio.h>
#include "hdc1010.h"
#include "display.h"

#define SLEEP_TIME_MS   1000

void main(void)
{
	int err;
	int temp[2];
	int humidity;
	//char* displayVal = "T: 28.3 C   RH: 36%";

	err=hdc1010Init();
	if(err!=0)
	{
		printk("hdc1010 init failed");
		return;
	}
	err=displayInit();
	if(err!=0)
	{
		printk("display init failed");
		return;
	}
	while(1)
	{
		err=getData(&temp, &humidity);
		if(err!=0)
		{
			printk("get data failed!");
		}
		char displayVal[] = "T:   .  C   RH:   %";
		displayVal[3] = temp[0]/10 + '0';
		displayVal[4] = temp[0]%10 + '0';;
		displayVal[6] = temp[1] + '0';;
		displayVal[16] = humidity/10 + '0';;
		displayVal[17] = humidity%10 + '0';;
		//printk("%s\n",displayVal);
		err=displayShow(displayVal);
		if(err!=0)
		{
			printk("show data failed!");
		}
		k_msleep(SLEEP_TIME_MS);
	}

}
