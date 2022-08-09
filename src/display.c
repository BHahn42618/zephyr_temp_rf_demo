#include <zephyr.h>
#include <device.h>
#include <display/cfb.h>
#include <stdio.h>
#include "display.h"

const struct device *dev;
uint16_t rows;
uint8_t ppt;
uint8_t font_width;
uint8_t font_height;

int displayInit(void)
{
	dev = device_get_binding(DISPLAY_DRIVER);

        if (dev == NULL) {
                printf("Device not found\n");
                return -1;
        }

        if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0) {
                printf("Failed to set required pixel format\n");
                return -1;
        }

        printf("initialized %s\n", DISPLAY_DRIVER);

        if (cfb_framebuffer_init(dev)) {
                printf("Framebuffer initialization failed!\n");
                return -1;
        }

        cfb_framebuffer_clear(dev, true);

        display_blanking_off(dev);

        rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);
        ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);

        for (int idx = 0; idx < 42; idx++) {
                if (cfb_get_font_size(dev, idx, &font_width, &font_height)) {
                        break;
                }
                cfb_framebuffer_set_font(dev, idx);
                printf("font width %d, font height %d\n",
                       font_width, font_height);
        }

        printf("x_res %d, y_res %d, ppt %d, rows %d, cols %d\n",
               cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH),
               cfb_get_display_parameter(dev, CFB_DISPLAY_HEIGH),
               ppt,
               rows,
               cfb_get_display_parameter(dev, CFB_DISPLAY_COLS));
	return 0;
}

int displayShow(char val[])
{
	cfb_framebuffer_clear(dev, false);
	if (cfb_print(dev,val,0, ppt)) {
		printf("Failed to print a string\n");
		return -1;
	}
	cfb_framebuffer_finalize(dev);
	return 0;
}

