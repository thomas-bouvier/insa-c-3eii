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

Image * allocateImage(int w, int h) {
  Image * image;

  if ((image = (Image *) malloc(sizeof(Image))) == (Image *) NULL) {
    fprintf(stderr, "Error while dynamic allocation for Image\n");
    return NULL;
  }

  image->height = h;
  image->width = w;
  image->raw_data = (Pixel *) malloc(image->height * image->width * sizeof(Pixel));

  if ((image->raw_data == (Pixel *) NULL)) {
    fprintf(stderr, "Error while dynamic allocation for Image raw data\n");
    return NULL;
  }

  return image;
}

void freeImage(Image * i) {
  free(i->raw_data);
}
