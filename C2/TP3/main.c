#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "fichier.h"

#define MY_FILENAME_MAX 16

int createImage(Image * image) {
  int i, j;
  Pixel bluePixel, redPixel;
  if (image == NULL) {
    fprintf(stderr, "The given Image pointer is NULL\n");
    return -1;
  }

  bluePixel.red = 0;
  bluePixel.green = 0;
  bluePixel.blue = 255;

  redPixel.red = 255;
  redPixel.green = 0;
  redPixel.blue = 0;

  for (j = 0; j < image->height; ++j) {
    for (i = 0; i < image->width; ++i) {
      if (i == j || i == (image->height - j)) {
        setPixelxy(image, i, j, bluePixel);
      } else {
        setPixelxy(image, i, j, redPixel);
      }
    }
  }

  return 0;
}

int main() {
  char filename[MY_FILENAME_MAX];
  Image i;

  if (allocateImage(&i, 100, 100) == NULL)
    fprintf(stderr, "Problem occured while allocating memory for image\n");

  createImage(&i);

  sprintf(filename, "image_test.bmp");
  writeBMPFile(filename, &i, 0);

  return 0;
}
