#include "common.h"

//Function definition
int file_input(in_file **head, char **argv)
{
	//Declare variables here
	int i;
	char *str;
	in_file *temp = NULL, *new = NULL;

	//Loop for creating linked list of CLA
	for (i = 1; argv[i]; i++)
	{

		//Initialize temp
		temp = *head;

		//Initialize str
		str = argv[i];

		//Loop for traversing through the list
		while (temp)
		{
			//Checking for duplicates
			if (!(strcmp(temp -> f_name, str)))
			{
				return DUPLICATE;
			}

			//Updating temp
			temp = temp -> link;
		}

		//Allocating memory for a node by DMA
		new = malloc(sizeof(in_file));
		
		//Validating memory allocation
		if (new == NULL)
		{
			return FAILURE;
		}

		//Copying str to node
		strcpy(new -> f_name, str);
		//Updating link
		new -> link = *head;
		//Updating head
		*head = new;
	}

}
