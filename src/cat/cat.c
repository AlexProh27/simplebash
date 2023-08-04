#include "cat.h"

int main(int argc, char **argv) {
  char info[6] = {0, 0, 0, 0, 0, 0};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        Cat_Parser_Long(i, argv, info);
      } else {
        Cat_Parser_Arg(i, argv, info);
      }
    } else {
      if (argv[i][1] != '-') {
        Cat_Print(i, argv, info);
      }
    }
  }
  return 0;
}

void Cat_Parser_Arg(int i, char **argv, char *info) {
  for (size_t it = 1; it < strlen(argv[i]); it++) {
    switch (argv[i][it]) {
      case 'b':
        info[0] = 1;  // flag b
        break;
      case 'e':
        info[1] = 1;  // flag e
        info[5] = 1;  // flag v
        break;
      case 'n':
        info[2] = 1;  // flag n
        break;
      case 's':
        info[4] = 1;  // flag s
        break;
      case 't':
        info[3] = 1;  // flag t
        info[5] = 1;  // flag v
        break;
      case 'v':
        info[5] = 1;  // flag v
        break;
      case 'T':
        info[3] = 1;  // flag t
        info[5] = 1;  // flag v
        break;
      case 'E':
        info[1] = 1;  // flag e
        info[5] = 1;  // flag v
        break;
      default:
        printf("%c is not argument\n", argv[i][it]);
    }
  }
}

void Cat_Parser_Long(int i, char **argv, char *info) {
  if (argv[i][0] == '-' || argv[i][1] == '-') {
    if (strcmp(argv[i], "--number-nonblak") == 0) {
      info[0] = 1;
    } else if (strcmp(argv[i], "--number") == 0) {
      info[2] = 1;
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
      info[4] = 1;
    } else {
      printf("%s is not argument\n", argv[i]);
    }
  }
}

int Cat_Print(int i, char **argv, char *info) {
  FILE *fp;
  if ((fp = fopen(argv[i], "r")) == NULL) {
    perror(argv[i]);
    return 0;
  } else {
    int in = 1;
    int ch_aski;
    char enter = 1;
    char count = 0;
    while ((ch_aski = getc(fp)) != EOF) {
      if (info[4]) check_S(ch_aski, enter, &count);
      if (info[0]) {
        check_B(ch_aski, &in, &enter);
        info[2] = 0;
      }
      if (info[2]) check_N(&in, &enter, &count);
      if (info[3]) check_T(&ch_aski);
      if (info[1]) check_E(ch_aski, &count);
      if (info[5]) check_V(&ch_aski);
      if (ch_aski != '\n') {
        enter = 0;
      } else {
        enter = 1;
      }
      if (count != 2) {
        printf("%c", ch_aski);
      }
    }
  }
  fclose(fp);
  return 0;
}

void check_S(int ch_aski, char enter, char *count) {
  if (ch_aski == '\n' && enter == 1) {
    if (ch_aski == '\n' && *count > 0) {
      *count = 2;
    } else {
      *count = 1;
    }
  } else {
    *count = 0;
  }
}

void check_B(int ch_aski, int *in, char *enter) {
  if (ch_aski != '\n' && *enter == 1) {
    printf("%6d\t", *in);
    *in = *in + 1;
  }
}

void check_N(int *in, char *enter, char *count) {
  if (*enter == 1 && *count != 2) {
    printf("%6d\t", *in);
    *in = *in + 1;
  }
}

void check_T(int *ch_aski) {
  if (*ch_aski == '\t') {
    printf("^");
    *ch_aski += 64;
  }
}

void check_E(int ch_aski, char *count) {
  if (ch_aski == '\n' && *count != 2) {
    printf("$");
  }
}

void check_V(int *ch_aski) {
  if ((*ch_aski >= 0 && *ch_aski < 9) || (*ch_aski > 10 && *ch_aski < 32)) {
    printf("^");
    *ch_aski += 64;
  }
  if (*ch_aski >= 128 && *ch_aski <= 159) {
    printf("M-^");
    *ch_aski -= 64;
  }
  if (*ch_aski == 127) {
    printf("^");
    *ch_aski = '?';
  }
}
