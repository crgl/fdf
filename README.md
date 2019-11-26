# fdf

![42.fdf](images/42-fdf.png)

This program takes in files of a particular format (essentially a matrix of evenly spaced heights) and translates them into a rotatable wireframe model, with an even color gradient from minimum to maximum height. Several different options are exhibited below - the C1 and C2 macros represent minimum height color and maximum height color respectively in 0RGB format.

## Build

### Mac

Clone or download, navigate to the root directory (fdf), and run `make`.

To run the program, run `./fdf test_maps/your_map_here.fdf`, or write your own `map.fdf` file if you so choose. Static images of some of the provided maps are shown here.

### Windows, Linux, Desktop Browser

See the [rust version](https://github.com/crgl/fdf_rust). The [web version](https://crgl.dev/rust/fdf/) is admittedly slow, but it's kind of incredible that WASM allows you to use the same source code to build for web and desktop.

## Controls

* Arrow keys for rotation
* Click and drag to move the wireframe in space
* Ctrl + click and drag to zoom in and out
* Command + click and drag to change the height scaling

## Results

This was my first real experience with interactive programs and graphics of any kind. The idea of building a program that projected a 3D wireframe and responded naturally to user input building off of a utility to place individual pixels was initially fairly intimidating.

### Implementing user input has a high reward / work ratio

An interactive program feels a lot more impressive than a static one, but is often not that much additional work. Getting something to respond smoothly and correctly is still an interesting problem, but in general the vast majority of the work of actually accepting input has already been done for you and you can get away with building hooks or using conditionals/match/switch statements in a loop.

### Graphics debugging is an adventure

There's an additional layer of indirection here between what you see and what the problem is, I think. Outside of graphics, I had been off by one, off by a factor of two, or filling a whole sudoku box with nines. With fdf, I found that missing a pair of parentheses could result in a fisheye lens effect, and replacing a + sign with a - sign was a surprisingly beautiful disaster. The experience of connecting visual bugs to code typos or math errors was both more challenging and more enjoyable.

### Building in stages is critical

Obviously I wouldn't generally recommend placing each individual pixel (fractals excepted); it's guaranteed to be slow. However, for something relatively simple like this, it's great to write your own line-drawing functions and call them with wild abandon.

![el-col.fdf](images/el-col-fdf.png)

![t2.fdf](images/t2-fdf.png)

![mars.fdf](images/mars-fdf.png)

![julia.fdf](images/julia-fdf.png)
