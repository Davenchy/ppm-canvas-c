#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} color_t;


typedef struct {
  uint32_t width;
  uint32_t height;
  color_t color;
  color_t *pixels;
} canvas_t;

void color_rgb(color_t *color, uint8_t red, uint8_t green, uint8_t blue) {
  if (!color) return;
  color->red = red;
  color->green = green;
  color->blue = blue;
}

void color_black(color_t *color) {
  color_rgb(color, 0, 0, 0);
}

void color_white(color_t *color) {
  color_rgb(color, 255, 255, 255);
}

void color_copy(color_t *dst, color_t *src) {
  if (!dst || !src) return;

  dst->red = src->red;
  dst->green = src->green;
  dst->blue = src->blue;
}

color_t *canvas_get_pixel(canvas_t *canvas, uint32_t x, uint32_t y) {
  if (!canvas || x >= canvas->width || y >= canvas->height) return NULL;
  return &canvas->pixels[y * canvas->width + x];
}

void canvas_set_pixel(canvas_t *canvas, uint32_t x, uint32_t y, color_t *color) {
  if (!canvas || !color || x >= canvas->width || y >= canvas->height) return;
  color_t *dst_color = canvas_get_pixel(canvas, x, y);
  color_copy(dst_color, color);
}

canvas_t *canvas_create(uint32_t width, uint32_t height, color_t *default_color) {
  color_t black;

  if (!default_color) {
    color_black(&black);
    default_color = &black;
  }

  uint32_t canvas_size = width * height;
  canvas_t *canvas = malloc(sizeof(canvas_t) + canvas_size * sizeof(color_t));
  if (!canvas) return NULL;

  canvas->width = width;
  canvas->height = height;
  color_copy(&canvas->color, default_color);
  canvas->pixels = (color_t *)(canvas + 1);

  for (uint32_t i = 0; i < canvas_size; i++)
    canvas->pixels[i] = *default_color;
  return canvas;
}

void canvas_set_color(canvas_t *canvas, color_t *color) {
  if (!canvas || !color) return;
  color_copy(&canvas->color, color);
}

void canvas_write_ppm(canvas_t *canvas, FILE *file) {
  if (!canvas || !file) return;
  fprintf(file, "P6\n%u %u\n255\n", canvas->width, canvas->height);
  for (uint32_t y = 0; y < canvas->height; y++) {
    for (uint32_t x = 0; x < canvas->width; x++) {
      color_t *color = canvas_get_pixel(canvas, x, y);
      fprintf(file, "%c%c%c", color->red, color->green, color->blue);
    }
  }
}

void canvas_destroy(canvas_t *canvas) {
  if (!canvas) return;
  free(canvas);
}

int main() {
  uint32_t i, j;
  canvas_t *canvas = canvas_create(800, 800, NULL);
  FILE *file;

  if (!canvas) return 1;

  for (i = 0; i < canvas->width; i++) {
    for (j = 0; j < canvas->height; j++) {
      color_t color = { i % 255, j % 255, (i + j) % 255 };
      canvas_set_pixel(canvas, i, j, &color);
    }
  }

  file = fopen("image.ppm", "w");
  if (file) {
    canvas_write_ppm(canvas, file);
    fclose(file);
  }

  canvas_destroy(canvas);
  return 0;
}
