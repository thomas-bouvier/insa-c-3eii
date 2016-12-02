#include "fichier.h"

void writeBMPFile(char * nomFichier, Image * image, int verbose) {
  int j;
  int uncomplete;
  int fill;
  FILE * f = NULL;
  FileHeader fileHeader;
  DIBHeader dibHeader;

  fileHeader.identity[0] = 'B';
  fileHeader.identity[1] = 'M';
  fileHeader.raster_address = sizeof(FileHeader) + sizeof(DIBHeader);

  dibHeader.size_DIBHeader = sizeof(DIBHeader);
  dibHeader.image_width = image->width;
  dibHeader.image_height = image->height;
  dibHeader.nbColorPlanes = 1;
  dibHeader.nbBitPerPixel = 24;
  dibHeader.typeCompression = 0;
  dibHeader.size_raw_image = image->width * image->height * sizeof(Pixel);
  dibHeader.hResolution = 2800;
  dibHeader.vResolution = 2800;
  dibHeader.nbUsedColours = 0;
  dibHeader.nbImportantColours = 0;

  fileHeader.file_size = sizeof(FileHeader) + sizeof(DIBHeader) + dibHeader.size_raw_image;

  if ((f = fopen(nomFichier, "wb")) == (FILE *) NULL) {
    fprintf(stderr, "Erreur lors de l'ouverture du fichier");
    return;
  }

  if (verbose) {
    displayFileHeader(&fileHeader);
    displayDIBHeader(&dibHeader);
  }

  fwrite(&fileHeader, sizeof(FileHeader), 1, f);
  fwrite(&dibHeader, sizeof(DIBHeader), 1, f);

  /* how many missing bytes to complete the width (in order to have % 0) */

  uncomplete = (dibHeader.image_width * sizeof(Pixel)) % 4;
  fill = (4 - uncomplete) % 4;

  if (verbose)
    printf("uncomplete: %d, fill: %d\n", uncomplete, fill);

  for (j = dibHeader.image_height - 1; j >= 0; --j) {
    fwrite(&(image->raw_data[j * dibHeader.image_width]), sizeof(Pixel), dibHeader.image_width, f);
    char missing[3];
    fwrite(missing, sizeof(char), fill, f);
  }
}

void displayFileHeader(FileHeader * fileHeader) {
  int i;

  printf("FileHeader\n");

  printf("\tidentity: ");
  for (i = 0; i < 2; ++i)
    printf("%c ", fileHeader->identity[i]);
  printf("\n");

  printf("\tfile_size: %d\n", fileHeader->file_size);
  printf("\traster_address: %d\n", fileHeader->raster_address);
}

void displayDIBHeader(DIBHeader * dibHeader) {
  printf("DIBHeader\n");

  printf("\tsize_DIBHeader: %d\n", dibHeader->size_DIBHeader);
  printf("\timage_width: %d\n", dibHeader->image_width);
  printf("\timage_height: %d\n", dibHeader->image_height);
  printf("\tnbColorPlanes: %d\n", dibHeader->nbColorPlanes);
  printf("\tnbBitPerPixel: %d\n", dibHeader->nbBitPerPixel);
  printf("\ttypeCompression: %d\n", dibHeader->typeCompression);
  printf("\tsize_raw_image: %d\n", dibHeader->size_raw_image);
  printf("\thResolution: %d\n", dibHeader->hResolution);
  printf("\tvResolution: %d\n", dibHeader->vResolution);
  printf("\tnbUsedColours: %d\n", dibHeader->nbUsedColours);
  printf("\tnbImportantColours: %d\n", dibHeader->nbImportantColours);
}
