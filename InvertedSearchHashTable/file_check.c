#include "common.h"

//Function definition
int file_check(in_file **head, char *file, in_file **head1)
{
	//Declare variables here
	in_file *temp = NULL,  *p = NULL, *new = NULL;

	//Initialize temp
	temp = *head;

	//Traversing through the list
	while (temp)
	{
		//Comparing file name with node data
		if (!(strcmp(temp -> f_name, file)))
		{
			return DUPLICATE;
		}

		//Initialize p
		p = temp;
		//Updating temp
		temp = temp -> link;
	}

	//Allocate memory for node
	new = malloc(sizeof(in_file));

	//Validating memory allocation
	if (new == NULL)
	{
		return FAILURE;
	}

	//Copying file name to node data
	strcpy(new -> f_name, file);
	//Updating link
	new -> link = *head1;
	//Updating head
	*head1 = new;
}
