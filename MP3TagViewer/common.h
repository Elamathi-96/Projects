//HAndle the header file iteration
#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
//Include header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

enum status
{
	FAILURE,
	SUCCESS,
	LIST_EMPTY,
	DATA_NOT_FOUND,
	ERROR
};

//Declare Prototypes
int validate_inputs(int , char **);
int format_mp3(char *);
int internal_version_mp3(char *);
int view(FILE *fs, char arr[][6]);
int edit(char *, char *, char *);

#endif
