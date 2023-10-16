# README

Uses Arduino Uno, [joystick](https://arduinogetstarted.com/tutorials/arduino-joystick) for Arduino and [waveshare 2.4 inch screen](https://www.waveshare.com/2.4inch-lcd-module.htm).

This code is based off the example LCD code that waveshare distributes with its 2.4 inch lcd-screen:
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_hardware_connection
https://www.waveshare.com/wiki/2.4inch_LCD_Module#Arduino_software_description

The 'gameboy' runs an Etch-a-Sketch, a Pong clone and an Asteroids clone and you can also control a strip of Neopixels with it.
Originally it also ran a program that displayed the Mandelbrot set and continually zoomed in on the border region, but the arduinos memory ran over 100% so had to comment out something.

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
- [ ] Add more colours to the fractal program. :art:

### After that
- [X] Implement an 'etch a sketch' as the next item on the menu.
- [X] Figure out a good way to exit the etchasketch.
- [X] Implement Pong
  - [X] Make ball direction after impact depend on where on the padel it hit.
  - [X] Add score at end of game.
  - [X] Add second padel
  - [X] Optimize ball speed and padel speed. Redraw only top and bottom pixels of rectangle. Make rectangle thinner. Could be optimized more. 

  - [X] Increase ball size.
  - [X] Fix bug where there are two padels on one side when moving below the middle. Disappears when returning past middle.
  - [X] Fix collision logic, it bounces off nothing sometimes now. Seems to be fixed. Will reopen if reappears. 
  - [X] Put type conversion into a separate file. 

- [X] Implement Asteroids clone (of old game from 70:s) :milky_way:
  - [X] Detect collision of bullets with asteroid.
  - [X] Delete asteroid upon collision.
  - [X] Detect collision of ship with asteroid.
  - [X] Display asteroids destroyed as score.
  - [X] Display 'game over' and quit to main menu after delay when ship is destroyed.
 The Asteroids game isn't completely stable, but leaving it as is. 
  

### Whenever someone is inspired
- [X] Build (3D-print?) a holder for the screen. Or use a shoebox. Used a shoebox.
- Screensaver using some of the cool pixel art from that person I follow on Mastodon, if its gpl or so. Thats probably not going to work, since the arduino can't store more than one 70x70 px picture. No memory.
Final debug Neopixels
Colours randomized when moving far to the right with the colours. <- This might be fixed now. cursorXPixel was maxing out at 255. 
Takes 5-6 presses before 'off' is registered.
Same for on.
The cursor moves very slowly up and down.
Both the menus (main and Neopixel) should not have vertical emptyness. 
Maybe with an external SD-card. 
  - [ ] Add high score. Is there any way to store this between restarts in Arduino? Maybe later. 
  - [ ] Asteroids - Life minus upon collision. -> You just have one life, decided to simplify it.
  - [ ] Asteroids - Display life as three ships in top left corner. - Possibly some other time.

Problems asteroids:
	 Double shots every time the button is pressed.
	 Freezes sometimes. Possibly connected to that activeShots outputs a negative number, which it shouldnt.
	 Probably has to do with the shots, when not shooting the program runs smoothly.
	 After a hit, activeShots decreases. How can there be a hit when activeShots is -3? 


	 The freeze seems to happen sometimes when a shot exits.
	 Gets stuck in translationMotionShots, when i = 0.



