# README

Uses Arduino Uno, [joystick](https://arduinogetstarted.com/tutorials/arduino-joystick) for Arduino and [waveshare 2.4 inch screen](https://www.waveshare.com/2.4inch-lcd-module.htm).

This code is based off the example LCD code that waveshare distributes with its 2.4 inch lcd-screen:
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_hardware_connection
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_software_description

The mandelbrot code and the functions for colouring the graph are based on Filips program:
https://github.com/FilipBerglund/Fractals
Filips program is for c++ and some of the libraries didn't work on arduino, so that makes some parts of the programs 
kind of different.

Complex is an arduino library for Complex math. 
In DEV_Config the baud rate is set to 115200 bit/second, so the serial monitor needs to be set to the same. 

## Todo

### Menu and fractal program
- [X] Make cursor faster. Did this, but later removed the cursor from the main menu. The trick is to only rewrite the pixels in the + where the cursor just was. Also, increments by 3 px instead of one per loop.
- [X] Blank screen and delay for a second or so before launching fractal program, so the menu doesn't look like its 'eaten' from below.
- [X] Figure out why only the contours of the set are showing - why is the inside of the figure black instead of max colour?
- [X] Possible to escape fractal program by pressing button.
- Add more colours to the fractal program. :art:

### After that
- Implement an 'etch a sketch' as the next item on the menu.
- Implement Filips 'Asteroids' game as the fourth item on the menu.
:milky_way:
### Whenever someone is inspired
- Build (3D-print?) a holder for the screen. Or use a shoebox.
- Screensaver using some of the cool pixel art from that person I follow on Mastodon, if its gpl or so.
