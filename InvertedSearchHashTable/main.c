#include "common.h"

int main(int argc, char *argv[])
{
	//Declare variables here
	in_file *head = NULL;
	in_file *head1 = NULL;
	file *f_head = NULL;
	int choice, status;	
	char file[10];
	char word[50];

	//Declaring hash table
	hash_t data[SIZE];

	//Checking the CLA
	if (argc == 1)
	{
		printf("Insufficient arguments\n");
		return -1;
	}

	printf("INFO : Storing inputs in a structure\n");
	//Function call for storing the input files in a linked list
	status = file_input(&head, argv);

	//Checking the return call and prompting the user about duplicate input
	if (status == DUPLICATE)
	{
		printf("ERROR : Duplicate inputs are not allowed\n");
		return -1;
	}
	printf("INFO : Storing inputs done\n");
	printf("INFO : Creating hash_table\n");
	//Function call for creating hash table
	create_hashtable(data);
	
	printf("INFO : Hash_table creation done\n");
	while (1)
	{

		//Prompt and read user choice
		printf("1) Create Database\n2)Print database\n3)Update database\n4)Search database\n5)Save database\n6)Exit\nEnter your choice:\n");
		scanf("%d", &choice);
		
		//Switch case for user choice
		switch (choice)
		{

			case 1 :
				
				//Case for creating database
				
				printf("CREATE DATABASE\n");
				printf("INFO : Creating database\n");
				
				//Function call
				status = create_database(data, &head, &f_head);
				
				//Checking the return value of function call and prompting the user
				if (status == FAILURE)
				{
					printf("ERROR : Database creation failure\n");
				}

				else
				{
					printf("INFO : Database created\n");
				}
				break;

			case 2 :

				//Case for printing database
			
				//Function call
				print_database(data);

				printf("INFO : Database printing done\n");
				break;

			case 3 :

				//Case for updating database
			
				printf("UPDATE DATABASE\n");

				//Prompt and read the file name from user
				printf("Enter the file to update database : ");
				scanf("%s", file);
				
				printf("INFO : Checking for duplicates in file structure\n");
				
				//Function call
				status = file_check(&head, file, &head1);
				
				//Checking the return value of function call and prompting the user
				if (status == DUPLICATE)
				{
					printf("ERROR :Database is already updated with that file\n");
				}
				
				else
				{
					printf("INFO : Checking for duplicates done\n");
					printf("INFO : Creating database\n");
					
					//Function call
					create_database(data, &head1, &f_head);
					
					printf("INFO : Database created\n");
				}
				break;

			case 4 :
			
				//Case for searching word in database
		
				//Prompt and read word from user
				printf("Enter the word to search:");
				scanf("%s", word);
				
				printf("INFO : Word is being searched in the database\n");
				
				//Function call
				status = search_database(word, data);

				//Checking the return value of function call and prompting the user
				if (status == WORD_NOT_FOUND)
				{
					printf("INFO : Word is not present in the database\n");
				}
				break;

			case 5 :

				//Case for saving database
				
				printf("INFO : Getting backup of database\n");

				//Function call
				status = save_database(data);

				printf("INFO : Backup is available in backup.txt file\n");
				
				//Checking the return value of function call and prompting the user
				if (status == FAILURE)
				{
					return -1;
				}
				break;
			
			case 6 :

				//Case for exiting from function
				exit(1);

			default :

				printf("Invalid choice..Try again..\n");
		}
	}
}
