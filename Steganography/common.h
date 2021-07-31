#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR -1
#define ERROR1 -2
#define SUCCESS 0

int validate_inputs(char **argv);
int encrypt(char **argv);
int header(FILE *, FILE *);
int passcode(FILE *, FILE *);
int length(FILE *, FILE *, FILE *);
void encode (FILE *, FILE *, int);
int txt_encrypt(FILE *, FILE *, FILE *, int);
int copy(FILE *, FILE *);
int decryption(char **argv);
int pass_decrypt(FILE *);
int length_decrypt(FILE *);
int txt_decrypt(int, FILE *, FILE *);

#endif
