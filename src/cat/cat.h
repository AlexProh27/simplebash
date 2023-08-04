#ifndef CAT_H
#define CAT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Cat_Parser_Arg(int i, char **argv, char *info);
void Cat_Parser_Long(int i, char **argv, char *info);
int Cat_Print(int i, char **argv, char *info);
void check_V(int *ch_aski);
void check_E(int ch_aski, char *count);
void check_T(int *ch_aski);
void check_N(int *in, char *enter, char *count);
void check_B(int ch_aski, int *in, char *enter);
void check_S(int ch_aski, char enter, char *count);

#endif
