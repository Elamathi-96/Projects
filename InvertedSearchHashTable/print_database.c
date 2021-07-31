#include "common.h"

//Function definition
int print_database(hash_t data[SIZE])
{
	//Declare variables here
	int i = 0;
	hash_t *temp1 = NULL;
	file *temp = NULL;
	printf("DATABASE_INFO:\n");

	//Traversing through the hash table
	while (i < SIZE)
	{
		//If f_count > 0
		if (data[i].f_count)
		{
			//Initialize temp1
			temp1 = &data[i];

			printf("[%d]\n", i);
			
			//Traversing the node
			while (temp1)
			{

				printf("\t%s in %d files ", temp1 -> word, temp1 -> f_count);
				//Initializing temp
				temp = temp1 -> t_link;

				while (temp)
				{
					printf("FILE_INFO : %s	: occurs %d times ", temp -> file, temp -> w_count);
					//Updating temp
					temp = temp -> f_link;
				}
				
				//Updating temp1
				temp1 = temp1 -> w_link;
				printf("\n");

			}
		}

		//Incrementing i
		i++;
	}
}
