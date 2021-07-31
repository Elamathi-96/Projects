#include "common.h"

//Function definition
int save_database(hash_t data[SIZE])
{
	//Declare variables here
	int i = 0, index;
	FILE *fs;
	hash_t *temp = NULL;
	file *temp1 = NULL;

	//Opening file
	fs = fopen("backup.txt", "w");

	//Checking for errors while opening a file
	if (fs == NULL)
	{
		perror("backup.txt");
		return FAILURE;
	}

	//Traversing through hash table
	while (i < SIZE)
	{
		//If f_count > 0
		if (data[i].f_count)
		{
			//Initializing temp
			temp = &data[i];

			//Writing hash table contents in a file
			fprintf(fs, "#%d;\n", i);
			
			while (temp)
			{

				fprintf(fs, "\t%s; %d; ", temp -> word, temp -> f_count);

				//Initializing temp1
				temp1 = temp -> t_link;

				while (temp1)
				{
					fprintf(fs, "%s; %d; ", temp1 -> file, temp1 -> w_count);
					//Updating temp1
					temp1 = temp1 -> f_link;
				}

				fprintf(fs, "#\n");
				//Updating temp
				temp = temp -> w_link;
			}
		}

		//Incrementing i
		i++;
	}

	//Closing file
	fclose(fs);
}
