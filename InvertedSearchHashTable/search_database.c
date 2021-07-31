#include "common.h"

//Function definition
int search_database(char *word, hash_t data[SIZE])
{
	//Declare variables here
	int dat, i;
	hash_t *temp = NULL;
	file *temp1 = NULL;

	//Initialize dat
	dat = word[0];

	//If dat > 97
	if (dat >= 97)
	{
		//Updating dat
		dat -= 32;
	}

	//Finding i
	i = (dat - 13) % SIZE;
	
	//Initializing temp
	temp = &data[i];

	//If f_count = 0
	if (!(temp -> f_count))
	{
		return WORD_NOT_FOUND;
	}


	else
	{
		//Traversing through the node
		while (temp)
		{
			//Comparing word and node word
			
			//If both the words are same printing that node
			if (!(strcmp(temp -> word, word)))
			{
				printf("[%d]\n", i);

				printf("\t%s in %d files ", temp -> word, temp -> f_count);

				//Initializing temp1
				temp1 = temp -> t_link;

				while (temp1)
				{
					printf("FILE_INFO : %s : occurs %d times", temp1 -> file, temp1 -> w_count);
					//Updating temp1
					temp1 = temp1 -> f_link;
				}
				
				printf("\n");
				return SUCCESS;

			}

			//Updating temp
			temp = temp -> w_link;

		}
	}

	//Word is not found
	return WORD_NOT_FOUND;

}
