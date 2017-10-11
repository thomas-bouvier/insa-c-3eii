#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv, char **arge) {
  /* flags */
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;

  /* vars */
  int index;
  int c;
  int i;
  int j;

  /* pointer of function */
  int (*fn)(int) = NULL;

  opterr = 0;

  while ((c = getopt (argc, argv, "abc:")) != -1) {
    switch (c) {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'c':
        cvalue = optarg;
        break;
      case '?':
        if (optopt == 'c')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
    }
  }

  /*
  printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);
  */

  /*
  for (index = optind; index < argc; ++index)
    printf("Non-option argument: %s\n", argv[index]);
  */

  /* pointer definition */
  if (cvalue != NULL) {
    if (strcmp(cvalue, "lower") == 0) {
      fn = &tolower;
    }
    else if (strcmp(cvalue, "upper") == 0) {
      fn = &toupper;
    }
  }

  if (fn != NULL) {
    for (index = optind; index < argc; ++index) {
      printf("\033[%dm", bflag ? 34 : 0);
      for (i = 0; i < strlen(argv[index]); ++i)
        printf("%c", (*fn)(argv[index][i]));
      printf("\033[0m%c", (index < argc - 1) ? ' ' : '\n');
    }
  }
  else {
    for (index = optind; index < argc; ++index) {
      printf("\033[%dm%s\033[0m%c", bflag ? 34 : 0, argv[index], (index < argc - 1) ? ' ' : '\n');
    }
  }

	return 0;
}
