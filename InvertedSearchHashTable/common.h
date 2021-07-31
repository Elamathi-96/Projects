#ifndef COMMON_H
#define COMMON_H

//Include header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Macro definition
#define SIZE 26

//Structure definitions

//Structure for storing file_info
typedef struct node
{
	char *file;
	int w_count;
	struct node *f_link;
}file;

//Structure for storing word
typedef struct node1
{
	char *word;
	int f_count;
	struct node1 *w_link;
	file *t_link;
}hash_t;

//Structure for storing arguments
typedef struct node2
{
	char f_name[20];
	struct node2 *link;
}in_file;

//Enum declaration
enum status
{
	SUCCESS, FAILURE, DUPLICATE, WORD_NOT_FOUND
};

//Function declarations
int create_database(hash_t [SIZE], in_file **, file **);
int print_database(hash_t [SIZE]);
void create_hashtable(hash_t [SIZE]);
int file_input(in_file **, char **);
int file_check(in_file **, char *, in_file **);
int search_database(char *, hash_t [SIZE]);
int save_database(hash_t [SIZE]);

#endif
