#if defined(CONFIG_SSD16XX)
#define DISPLAY_DRIVER          "SSD16XX"
#endif

#if defined(CONFIG_SSD1306)
#define DISPLAY_DRIVER          "SSD1306"
#endif

#ifndef DISPLAY_DRIVER
#define DISPLAY_DRIVER          "DISPLAY"
#endif

int displayInit(void);
int displayShow(char val[]);
