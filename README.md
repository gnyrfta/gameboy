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
- [ ] Add more colours to the fractal program. :art:

### After that
- [X] Implement an 'etch a sketch' as the next item on the menu.
- [X] Figure out a good way to exit the etchasketch.
- [X] Implement Pong
  - [X] Make ball direction after impact depend on where on the padel it hit.
  - [X] Add score at end of game.
  - [X] Add second padel
  - [X] Optimize ball speed and padel speed. Redraw only top and bottom pixels of rectangle. Make rectangle thinner. Could be optimized more. 
  - [ ] Add high score. Is there any way to store this between restarts in Arduino? 
  - [X] Increase ball size.
  - [X] Fix bug where there are two padels on one side when moving below the middle. Disappears when returning past middle.
  - [X] Fix collision logic, it bounces off nothing sometimes now. Seems to be fixed. Will reopen if reappears. 
  - [X] Put type conversion into a separate file. 

- [ ] Implement Asteroids clone (of old game from 70:s) :milky_way:
  - [ ]The shots seem to work now, but the game crashes after a few shots. Should try running with verbose output.
  - [ ] Detect collision of bullets with asteroid.
  - [ ] Delete asteroid upon collision.
  - [ ] Detect collision of ship with asteroid.
  - [ ] Life minus upon collision.
  - [ ] Display life as three ships in top left corner.
  - [ ] Display asteroids destroyed as score.
  - [ ] Display 'game over' and quit to main menu after delay when ship is destroyed.
  Weird bug 2 - the game quits quickly when asteroid velocities are randomized in both directions (-4 -> 4). 
  

### Whenever someone is inspired
- Build (3D-print?) a holder for the screen. Or use a shoebox.
- Screensaver using some of the cool pixel art from that person I follow on Mastodon, if its gpl or so. Thats probably not going to work, since the arduino can't store more than one 70x70 px picture. No memory.
Maybe with an external SD-card. 


Try removing adapter cord and just adding that little metal thing to the cable.

Problems asteroids:
	 Double shots every time the button is pressed and one of the shots gets stuck instead of being erased.
	 Freezes sometimes. Possibly connected to that activeShots outputs a negative number, which it shouldnt.
	 Probably has to do with the shots, when not shooting the program runs smoothly.
	 After a hit, activeShots decreases. How can there be a hit when activeShots is -3? 
	 Asteroids are only partially deleted when hit.

	 One asteroid is fixed in place.

	 The freeze seems to happen sometimes when a shot exits.
	 Gets stuck in translationMotionShots, when i = 0.

	 Maybe the problem is gone now. Probably not.

	 Start here: print 'game over' and score when collision occurs.
	 Then start debugging from the top.