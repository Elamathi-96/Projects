#include "common.h"

//Function definition
void create_hashtable(hash_t data[])
{
	//Declare variables here
	int i;

	//Loop for creating hash table by initializing f_count , w_link and t_link
	for (i = 0; i < SIZE; i++)
	{
		data[i].f_count = 0;
		data[i].w_link = NULL;
		data[i].t_link = NULL;
	}
}
