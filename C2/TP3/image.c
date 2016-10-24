#include "image.h"

int setPixelxy(Image * image, int x, int y , Pixel p) {
    if (x < 0 || x > image->width - 1 || y < 0 || y > image->height - 1)
        return -1;

    image->raw_data[y * image->width + x] = p;

    return 0;
}

Pixel getPixelxy(Image * image, int x, int y) {
  if (x < 0 || x > image->width - 1 || y < 0 || y > image->height - 1) {
    Pixel blackPixel;

    blackPixel.red = 0;
    blackPixel.green = 0;
    blackPixel.blue = 0;

    return blackPixel;
  }

  return image->raw_data[y * image->width + x];
}

Image * allocateImage(Image * i, int h, int w) {
  i->height = h;
  i->width = w;
  i->raw_data = (Pixel *) malloc(i->height * i->width * sizeof(Pixel));

  return i;
}

void freeImage(Image * i) {
  free(i->raw_data);
}
