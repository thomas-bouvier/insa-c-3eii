#include "fichier.h"

void readFileHeader(FILE * f, FileHeader * fileHeader) {
  rewind(f);
  fread(&fileHeader->identity, sizeof(char), 2, f);
  fread(&fileHeader->file_size, sizeof(uint32_t), 1, f);
  fread(&fileHeader->application_id, sizeof(char), 4, f);
  fread(&fileHeader->raster_address, sizeof(uint32_t), 1, f);
}

void readDIBHeader(FILE * f,  DIBHeader * dibHeader) {
  fseek(f, sizeof(FileHeader), SEEK_SET);
  fread(dibHeader, sizeof(DIBHeader), 1, f);
}

Image * readRawImage(FILE * f, unsigned int adresse, int l, int h) {
  int padding = l % 4;
  int i;
  Image * image;

  if ((image = allocateImage(l, h)) == (Image *) NULL) {
    fprintf(stderr, "Erreur lors de l'allocation mémoire de l'image\n");
    return NULL;
  }

  image->width = l;
  image->height = h;

  // cursor at beginning of raw data

  fseek(f, adresse, SEEK_SET);

  // reading data line per line, decreasing order

  for (i = h - 1; i >= 0; i--) {
    fread(&(image->raw_data[i * l]), sizeof(Pixel), l, f);

    // padding
    fseek(f, padding, SEEK_CUR);
  }

  return image;
}

Image * readBMPFile(char * nomFichier, int verbose) {
  FILE * f = NULL;
  FileHeader fileHeader;
  DIBHeader dibHeader;

  if (verbose) {
    printf("\nReading %s...\n", nomFichier);
    printf("---------------------------------------\n");
  }

  if ((f = fopen(nomFichier, "rb")) == (FILE *) NULL) {
    fprintf(stderr, "Erreur lors de l'ouverture du fichier");
    return NULL;
  }

  if (verbose)
    printf("%s successfully opened\n", nomFichier);

  if (verbose)
    printf("Reading FileHeader...\n");
  readFileHeader(f, &fileHeader);
  if (verbose)
    displayFileHeader(&fileHeader);

  if (verbose)
    printf("Reading DIBHeader...\n");
  readDIBHeader(f, &dibHeader);
  if (verbose)
    displayDIBHeader(&dibHeader);

  return readRawImage(f, fileHeader.raster_address, dibHeader.image_width, dibHeader.image_height);
}

void writeBMPFile(char * nomFichier, Image * image, int verbose) {
  int j;
  int uncomplete;
  int fill;
  FILE * f = NULL;
  FileHeader fileHeader;
  DIBHeader dibHeader;

  if (verbose) {
    printf("\nWriting %s...\n", nomFichier);
    printf("---------------------------------------\n");
  }

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

  // ouput if verbose enabled

  if (verbose) {
    displayFileHeader(&fileHeader);
    displayDIBHeader(&dibHeader);
  }

  // writing the headers

  fwrite(&fileHeader, sizeof(FileHeader), 1, f);
  fwrite(&dibHeader, sizeof(DIBHeader), 1, f);

  /* how many missing bytes to complete the width (in order to have % 0) */

  uncomplete = (dibHeader.image_width * sizeof(Pixel)) % 4;
  fill = (4 - uncomplete) % 4;

  // output if verbose enabled

  if (verbose)
    printf("uncomplete: %d, fill: %d\n", uncomplete, fill);

  // writing data line per line, decreasing order

  for (j = dibHeader.image_height - 1; j >= 0; --j) {
    fwrite(&(image->raw_data[j * dibHeader.image_width]), sizeof(Pixel), dibHeader.image_width, f);

    // padding
    char missing[3];
    fwrite(missing, sizeof(char), fill, f);
  }
}

void displayFileHeader(FileHeader * fileHeader) {
  int i;

  printf("FileHeader\n");

  if (fileHeader == (FileHeader *) NULL) {
    fprintf(stderr, "Null FileHeader pointer");
    return;
  }

  printf("\tidentity: ");
  for (i = 0; i < 2; ++i)
    printf("%c ", fileHeader->identity[i]);
  printf("\n");

  printf("\tfile_size: %d\n", fileHeader->file_size);
  printf("\traster_address: %d\n", fileHeader->raster_address);
}

void displayDIBHeader(DIBHeader * dibHeader) {
  printf("DIBHeader\n");

  if (dibHeader == (DIBHeader *) NULL) {
    fprintf(stderr, "Null DIBHeader pointer");
    return;
  }

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
