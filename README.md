# PPM Canvas in C

This is an example of a C program that can be used to generate PPM images.
I created it to know more about ppm images and how to generate them in C.

![The generated PPM image](./image.png)

## Build

Use the make file to build the program:

### Makefile rules

- **build**: To build the executable.
- **exec**: To build and execute.
- **open**: To build, execute and preview the generated image.

By default **feh** will be used to preview the image, set the `open_with` make argument to change it.

### Makefile arguments

- `command`: The name of the executable that will be build.
- `image_file`: The name of the image file that will be generated.
- `open_with`: The program that will be used to preview the image.
