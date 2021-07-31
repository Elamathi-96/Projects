#include "common.h"

//Function definition
int validate_inputs(char **argv)
{
	//Declare variables here
	int i, no_of_args = 0, length;
	FILE *fp;
	unsigned short code;

	//Finding the no. of arguments
	for (i = 0; argv[i]; i++)
	{
		no_of_args++;
	}

	//Validating no_of_args for decrytion mode
	if ((no_of_args < 3 || no_of_args > 4) && (strcmp(argv[1], "-d") == 0))
	{
		printf("ERROR :\nInsufficient arguments\n");
		printf("Usage :\n");
		printf("	./steganography <option 1> <option 2> <option 3> <option 4>\n");
		printf("	<option 1> : -e : Encryption\t-d : Decryption\n");
		printf("	<option 2> : Source file must be with .bmp file extension\n");
		printf("	<option 3> : Source file must be with .txt file extension\n");
		printf("	<option 4> : This is optional...Destination file with .bmp file extension\n");
		//Returning error
		return ERROR;
	}

	//Validating no. of arguments for encryption mode
	if ((no_of_args < 4 || no_of_args > 5) && (strcmp(argv[1], "-e") == 0))
	{
		printf("ERROR :\nInsufficient arguments\n");
		printf("Usage :\n");
		printf("	./steganography <option 1> <option 2> <option 3> <option 4>\n");
		printf("	<option 1> : -e : Encryption\t-d : Decryption\n");
		printf("	<option 2> : Source file must be with .bmp file extension\n");
		printf("	<option 3> : Source file must be with .txt file extension\n");
		printf("	<option 4> : This is optional...Destination file with .bmp file extension\n");
		//Returning error
		return ERROR;
	}

	//Validating 2nd argument
	if ((strcmp(argv[1], "-e") != 0) && (strcmp(argv[1], "-d") != 0))
	{
		printf("ERROR :\n<option 1> :\n");
		printf("Usage :\n");
		printf("	-e : Encryption\n");
		printf("	-d : Decryption\n");
		
		//Returning error
		return ERROR;
	}

	//Initializing length to the length of 3rd argument  and validating 3rd argument which must be a .bmp file
	length = strlen(argv[2]);
	if (strcmp(argv[2] + (length - 3), "bmp") != 0)
	{
		printf("ERROR :\n<option 2> :\n");
		printf("	Source file must have .bmp file extension\n");
		
		//Returning error
		return ERROR;
	}

	//Checking whether the 3rd argument an be opened or not
	if ((fp = fopen(argv[2], "rb")) == NULL)
	{
		perror(argv[2]);
		
		//Returning error
		return ERROR;
	}

	//Checking whether 3rd argument is actually a .bmp file
	fread(&code, 2, 1, fp);
	if (code != 0X4d42)
	{
		printf("ERROR :\n<option 2> :\n");
		printf("	It is not a .bmp file\n");
		
		//Returning error
		return ERROR;
	}
	//Closing .bmp file
	fclose(fp);

	if (argv[3] != NULL)
	{
		//Initializing length to the length of 4th argument and validating 4th argument which must be a .txt file
		length = strlen(argv[3]);
		if (strcmp(argv[3] + (length - 3), "txt") != 0)
		{
			printf("ERROR :\n<option 3> :\n");
			printf("	Source file must have .txt file extension\n");
			
			//Returning error
			return ERROR;
		}
	}
	//Checking the 5th argument if it is passed
	if (no_of_args == 5)
	{
		//Initializing length to the length of 3rd argument  and validating 3rd argument which must be a .bmp file
		length = strlen(argv[4]);
		if (strcmp(argv[4] + length - 3, "bmp") != 0)
		{
			printf("ERROR :\n<option 4> :\n");
			printf("	Source file must have .bmp file extension\n");
			
			//Returning error
			return ERROR;
		}
	}

	//Else the input given is valid
	else
	{
		//Returning success
		return SUCCESS;
	}

	fcloseall();
}
