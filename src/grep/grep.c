#include "grep.h"

int main(int argc, char* argv[]) {
  char info[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char ef_arg[BUFFER] = {0};

  if (argc > 1) {
    grep_Arg(argc, argv, info, ef_arg);
    if (info[0] == 0 && info[8] == 0) {
      strcat(ef_arg, argv[optind]);
      optind += 1;
    }
    grep_Print(argc, argv, ef_arg, info);
  }
  return 0;
}

void grep_Arg(int argc, char* argv[], char* info, char* ef_arg) {
  int ch = 0;
  int e_count = 0;
  char* optstring = "eivclnhsfo";

  while ((ch = getopt_long(argc, argv, optstring, 0, 0)) != -1) {
    switch (ch) {
      case 'e':
        info[0] = 1;
        add_e_arg(optarg, &e_count, ef_arg);
        break;
      case 'i':
        info[1] = 1;
        break;
      case 'v':
        info[2] = 1;
        break;
      case 'c':
        info[3] = 1;
        break;
      case 'l':
        info[4] = 1;
        break;
      case 'n':
        info[5] = 1;
        break;
      case 'h':
        info[6] = 1;
        break;
      case 's':
        info[7] = 1;
        break;
      case 'f':
        info[8] = 1;
        add_f_arg(optarg, &e_count, ef_arg, argv);
        break;
      case 'o':
        info[9] = 1;
        break;
      default:
        printf("error");
        break;
    }
  }
}

void add_e_arg(char* optarg, int* e_count, char* ef_arg) {
  if (*e_count != 0) {
    strcat(ef_arg, "|");
  }
  strcat(ef_arg, optarg);
  *e_count += 1;
}

void add_f_arg(char* optarg, int* e_count, char* ef_arg, char* argv[]) {
  FILE* fp_f = NULL;
  char line[BUFFER] = {0};

  if ((fp_f = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], optarg);
    exit(2);
  } else {
    while (fgets(line, BUFFER, fp_f) != NULL) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
      if (*e_count > 0) strcat(ef_arg, "|");
      strcat(ef_arg, line);
    }
    fclose(fp_f);
  }
}

void grep_Print(int argc, char* argv[], char* ef_arg, char* info) {
  FILE* fp;
  int files_count = argc - optind;

  for (; optind < argc; optind++) {
    if ((fp = fopen(argv[optind], "r")) == NULL) {
      if (info[7] == 0) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[optind]);
      }
    } else {
      reg_compile(argv, ef_arg, fp, info, files_count);
      fclose(fp);
    }
  }
}

void reg_compile(char** argv, char* my_reg, FILE* fp, char* info,
                 int files_count) {
  regex_t pattern;
  regmatch_t pmatch[1] = {0};
  size_t nmatch = 1;

  int err;
  char err_msg[MAX_ERR_LENGTH];
  char str[BUFFER];
  size_t n_line = 1;
  int lines_count = 0;
  int i_option = 0;

  if (info[1] != 0) i_option = REG_ICASE;
  err = regcomp(&pattern, my_reg, REG_EXTENDED | i_option);
  if (err != 0) {
    regerror(err, &pattern, err_msg, MAX_ERR_LENGTH);
    fprintf(stderr, "Error analyzing regular expression '%s': %s.\n", my_reg,
            err_msg);
    exit(3);
  }
  while (feof(fp) == 0) {
    if (fgets(str, BUFFER, fp)) {
      int new_line_o_counter = 1;
      err = regexec(&pattern, str, nmatch, pmatch, 0);
      if (info[2] != 0) err = err ? 0 : 1;
      if (err == 0) {
        if (info[3] == 0 && info[4] == 0) {
          if (files_count > 1 && info[6] == 0) {
            printf("%s:", argv[optind]);
          }
          if (info[5] != 0) {
            printf("%lu:", n_line);
          }
          if (info[9] != 0 && info[2] == 0) {
            new_line_o_counter = 0;
            char* ptr = str;
            while (err == 0) {
              if (pmatch[0].rm_eo == pmatch[0].rm_so) break;
              printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                     ptr + pmatch[0].rm_so);
              ptr += pmatch[0].rm_eo;
              err = regexec(&pattern, ptr, nmatch, pmatch, REG_NOTBOL);
            }
          }
          if (!info[9] || info[2]) printf("%s", str);
          if (str[strlen(str) - 1] != '\n' && new_line_o_counter != 0) {
            printf("\n");
          }
        }
        lines_count++;
      }
      n_line++;
    }
  }
  if (info[3] != 0) {
    if (files_count > 1 && !info[6]) {
      printf("%s:", argv[optind]);
    }
    if (info[4] && lines_count)
      printf("1\n");
    else
      printf("%d\n", lines_count);
  }
  if (info[4] && lines_count) {
    printf("%s\n", argv[optind]);
  }
  regfree(&pattern);
}
