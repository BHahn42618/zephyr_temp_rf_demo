# zephyr_temp_rf_demo
demo application for zephyr reel_board_v2 that uses the hdc1010 sensor and writes the temperature and humidity to the display

HOW TO USE:

NOTE: the $ sign means the line is a linux console command

go to your zephyr folder

$ cd ~/zephyrproject/zephyr


clone the repo:

$ git clone https://github.com/BHahn42618/zephyr_temp_rf_demo.git


go to the repo:

$ cd zephyr_temp_rf_demo


build the application:

$ west build -b reel_board_v2


flash the application to the board:

$ west flash
