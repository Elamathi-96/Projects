#include "common.h"

//Function definition
int create_database(hash_t data[SIZE], in_file **head, file **f_head)
{
	//Declare variables herre
	FILE *fs;
	file *temp = NULL;
	in_file *temp1 = NULL;
	hash_t *new = NULL;
	hash_t *temp2 = NULL;
	file *temp3 = NULL;
	file *new1 = NULL;
	char buffer[50];
	int i, dat, flag = 0;
	hash_t *p, *ptr1;
	file *p1;
	
	//Initialize temp1
	temp1 = *head;

	//Traversing through in_file list
	while (temp1)
	{
		//Opening a file in read mode
		fs = fopen(temp1 -> f_name, "r");

		//Checking for error in opening a file
		if (fs == NULL)
		{
			perror(temp1 -> f_name);
			return FAILURE;
		}

		//Reading a word from file and storing in buffer
		while(fscanf(fs, "%s", buffer) != EOF)
		{
			//Initialize dat
			dat = buffer[0];

			//Checking dat for special characters
			if (dat < 48 || (dat > 57 && dat < 65) || (dat > 90 && dat < 97))
			{
				continue;
			}

			//If dat >= 97
			if (dat >= 97)
			{
				//Updating dat
				dat -= 32;
			}

			//Finding index
			i = (dat - 13) % SIZE;

			//Checking the file count of i
			if (!(data[i].f_count))
			{
				//Initializing p
				p = &data[i];

				//Allozting memory for word
				p -> word = malloc(sizeof(buffer));

				//Copying buffer to word of node
				strcpy(p -> word, buffer);

				//Updating f_count and w_link
				data[i].f_count++;
				data[i].w_link = NULL;

				//Creating node for file structure by DMA
				new1 = malloc(sizeof(file));

				//Validating memory allocation
				if (new1 == NULL)
				{
					return FAILURE;
				}
				
				//Initializing p1
				p1 = new1;

				//Allocating memory for nodefile
				p1 -> file = malloc(10);

				//Copying file name to file node
				strcpy(p1 -> file, temp1 -> f_name);

				//Updating w_count and f_link
				new1 -> w_count = 1;
				new1 -> f_link = NULL;

				//Updating head of file structure
				*f_head = new1;

				//Updating node t_link
				data[i].t_link = *f_head;

			}

			else
			{
				//Initialize temp2
				temp2 = &data[i];

				//Traversing through the nodes
				while(temp2)
				{
					//Comparing node word and buffer
					
					//if word and buffer different
					if (strcmp(buffer, temp2 -> word))
					{
						//Clear the flag
						flag = 0;
					}
					else
					{
						//Set the flag and break from loop
						flag = 1;
						break;
					}
					
					//Initialize p
					p = temp2;
					//Updating temp2
					temp2 = temp2 -> w_link;
					
				}

				//If buffer and word are different
				if (!flag)
				{
					//Create new node by DMA
					new = malloc(sizeof(hash_t));

					//Validating memory allocation
					if (new == NULL)
					{
						return FAILURE;
					}
					
					//Initialize ptr1
					ptr1 = new;

					//Allocating memory for word
					ptr1 -> word = malloc(sizeof(buffer));

					//Copying buffer to word
					strcpy(ptr1 -> word, buffer);

					//Updating f_count, w_link
					new -> f_count = 1;
					new -> w_link = NULL;

					//Allocating new node for file structure
					new1 = malloc(sizeof(file));

					//Validating memory allocation
					if (new1 == NULL)
					{
						return FAILURE;
					}

					//Initialize p1
					p1 = new1;

					//Allocating memory for file
					p1 -> file = malloc(10);

					//Copying file name to file node
					strcpy(p1 -> file, temp1 -> f_name);

					//Updating w_count and f_link
					new1 -> w_count = 1;
					new1 -> f_link = NULL;

					//Initializing f_head
					*f_head = new1;

					//Updating t_link
					new -> t_link = *f_head;

					//Updating w_link
					p -> w_link = new;

				}

				//If buffer and word is same
				else
				{

					//Initialize temp3
					temp3 = temp2 -> t_link;

					//Traversing through the file structure
					while (temp3)
					{
						//Comparing the file names
					
						//If file names are different
						if (strcmp(temp3 -> file, temp1 -> f_name))
						{
							//Clear flag
							flag = 0;
						}

						//If file names are same
						else
						{
							//Setting flag and break
							flag = 1;
							break;
						}
						
						//Initialize p1
						p1 = temp3;
						//Updating temp3
						temp3 = temp3 -> f_link;
					}

					//If filenames are same
					if (flag)
					{
						//Incrementing w_count
						temp3 -> w_count++;
					}

					//If filenames are different
					else
					{
						//Allocating node for file structure
						new1 = malloc(sizeof(file));
						
						//Validating memory allocation
						if (new1 == NULL)
						{
							return FAILURE;
						}

						//Allocating memory for file node
						new1 -> file = malloc(10);

						//Copying file name to file node
						strcpy(new1 -> file, temp1 -> f_name);

						//Updating w_count and f_link
						new1 -> w_count = 1;
						new1 -> f_link = NULL;

						//Updating f_link
						p1 -> f_link = new1;

						//Incrementing f_count
						temp2 -> f_count++;
					}
				}

			}
		}

		//Updating temp1
		temp1 = temp1 -> link;
	}

	//Closing fs
	fclose(fs);
}
