#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //для функции strcat()
#include <unistd.h>

#define BUFFER 4096
#define MAX_ERR_LENGTH 500

void grep_Arg(int argc, char* argv[], char* info, char* ef_arg);
void add_e_arg(char* optarg, int* e_count, char* ef_arg);
void add_f_arg(char* optarg, int* e_count, char* ef_arg, char* argv[]);
void grep_Print(int argc, char* argv[], char* ef_arg, char* info);
void reg_compile(char* argv[], char* my_reg, FILE* fp, char* info,
                 int files_count);

#endif
