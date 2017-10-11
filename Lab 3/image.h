/*!
 * \file image.h
 * \brief Declaration of Image structure and associated functions
 * \author ...
 * \date ...
 */

#ifndef IMAGE_H_INC
#define IMAGE_H_INC

#include <stdio.h>
#include <stdlib.h>

/** struct typedef to define a Pixel using RGB colour space
* A pixel is defined in RGB space : a byte for each color coponent (Blue, Green, Red)
*/
typedef struct {
  unsigned char blue;   /*!<the blue component */
  unsigned char green;  /*!<the green component */
  unsigned char red;    /*!<the red component */
} Pixel;

/** struct typedef to define an Image using RBG colour space
* An image is defined as a grid of pixels.
* It needs to set its number of columns (width), number of rows (heigth).
* The pixel data is stored continuously in memory, row by row.
*/
typedef struct {
  int width;            /*!<the number of columns in the pixel grid*/
  int height;           /*!<the number of lines in the pixel grid*/
  Pixel * raw_data;     /*!<the pixel grid*/
} Image;

int setPixelxy(Image * image, int x, int y, Pixel p);
Pixel getPixelxy(Image * image, int x, int y);

Image * allocateImage(Image * image, int l, int h);
void freeImage(Image * i);

#endif
