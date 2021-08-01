#include "common.h"

//Function definition
int encrypt(char **argv)
{
	//Declare variables here
	FILE *fs, *fd, *fs1;
	int length1, status;

	//Opening source.bmp file
	fs = fopen(argv[2], "rb");

	printf("*ENCRYPTION PROCEDURE STARTED*\n");
	
	//Cheking 4th argument
	if (argv[4] == NULL)
	{
		//Opening file if user hasnt given the destination file
		fd = fopen("destination.bmp", "wb");
		//Checking for error
		if (fd == NULL)
		{
			perror("destination.bmp");
			return -1;
		}

		printf("INFO : Destination file not mentioned..Opening destination.bmp\n");
	}

	else
	{
		//Opening the destination file given by user
		fd = fopen(argv[4], "wb");
		printf("INFO : Opening %s file..\n", argv[4]);
	}

	printf("INFO : Opening %s  file..\n", argv[3]);
	//Opening text file
	fs1 = fopen(argv[3], "r");
	
	//Checking for error
	if (fs1 == NULL)
	{
		perror(argv[3]);
		return -1;
	}
	
	//Function call for copying header
	status = header(fs, fd);
	if (status == ERROR)
	{
		printf("INFO : Invalid source or destination file\n");
		return ERROR;
	}

	//Function call for encrypting passcode
	status = passcode(fs, fd);
	if (status == ERROR)
	{
		printf("INFO : Invalid sorurce or destination file\n");
		return ERROR;
	}
	
	//Function call for encrypting length
	length1 = length(fs, fs1, fd);
	if (length1 == 0)
	{
		printf("INFO : Text file empty\n");
		return ERROR;
	}
	else if (length1 == ERROR)
	{
		printf("INFO : Invalid source or destination file\n");
		return ERROR;
	}

	//Reopening txt file
	fs1 = fopen(argv[3], "r");
	
	//Function call for encrypting information 
	status = txt_encrypt(fs, fs1, fd, length1);
	
	if (status == ERROR)
	{
		printf("INFO : Information Encryption failed\n");
		return ERROR;
	}

	//Function call for copying the remaining part of source file
	status = copy(fs, fd);

	if (status == ERROR)
	{
		printf("INFO : Invalid source or destination file\n");
		return ERROR;
	}
	//Closing all files
	fcloseall();
	return SUCCESS;
}

//Function definition
int header(FILE *fs, FILE *fd)
{
	if (fs == fd)
	{
		return ERROR;
	}

	printf("INFO : Copying header part from source bmp to destination bmp file..\n");
	//Declare variables here
	char buffer[54];
	
	//Reading 54 bytes from source .bmp file
	if (fread(buffer, 1, 54, fs) == 0 )
	{
		return ERROR;
	}
	else
	{
		//Writing 54 bytes to dest .bmp file
		fwrite(buffer, 1, 54, fd);
	}

	printf("INFO : Header copying done\n");
}

//Function definition
int passcode(FILE *fs, FILE *fd)
{
	//Declare variables here
	int passcode, status;
	
	if (fs == fd)
	{
		return ERROR;
	}
	
	//Prompt and read passcode
	printf("ENTER THE PASSCODE:");
	status = scanf("%d", &passcode);
	
	//Validating passcode
	if (!status)
	{
		printf("Passcode must be an integer...Try again\n");
		exit(1);
	}

	printf("INFO : Password encryption started..\n");
	//Function call for encrypting passcode 
	encode(fs, fd, passcode);

	printf("INFO : Password encryption done\n");
	
}

//Function definiton
int length(FILE *fs, FILE *fs1, FILE *fd)
{
	//Declare variables here
	int length = 0;

	if (fs == fd || fs1 == fs || fs1 == fd)
	{
		return ERROR;
	}
	//Calculating the no. of characters in .txt file
	while (fgetc(fs1) != EOF)
	{
		//Incrementing length
		length++;
	}

	//Closing file
	fclose(fs1);
	
	printf("INFO : Encryption of length of txt file started..\n");
	//Function call for encrypting length
	encode(fs, fd, length);

	if (length)
	{
		printf("INFO : Length encryption done\n");
	}

	return length;
}

//Function definiton
void encode(FILE *fs, FILE *fd, int num)
{
	//Declare variables here
	char byte, temp;
	unsigned mask = 1;
	int i = 0, bit;

	//Encrypting num
	while (i < 32)
	{
		//Taking bit by bit from passcode or length
		bit = num & mask;
		bit >>= i;
		mask <<= 1;

		//Reading a byte from source .bmp file
		fread(&byte, 1, 1, fs);
		
		//Getting lsb from byte
		temp = byte & 1;

		if (temp != bit)
		{
			//Changing the byte
			temp ^= 1;
		}

		//Writing in dest .bmp file
		fwrite(&temp, 1, 1, fd);
		
		//Incrementing i
		i++;
	}
}

//Function definition
int txt_encrypt(FILE *fs, FILE *fs1, FILE *fd, int length)
{
	//Declare variables here
	char buffer, bit, byte, temp, temp1;
	int i = 0, j = 0;
	unsigned mask;

	printf("INFO : Information encryption started..\n");
	
	if (fs == fd || fs1 == fd || fs == fs1)
	{
		return ERROR;
	}
	
	//Encrypting secret text into destination
	while (i < length)
	{
		//Getting a byte from txt file
		bit = fgetc(fs1);
		j = 0;
       		mask = 1;
		while (j < 8)
		{

			//Reading a byte from source .bmp file
			if (fread(&byte, 1, 1, fs) == 0 )
			{
				return ERROR;
			}
			temp = bit & mask;
			temp >>= j;
			mask <<= 1;

			temp1 = byte & 1;

			if (temp != temp1)
			{
				byte ^= 1;
			}

			//Wrinting into dest file
			fwrite(&byte, 1, 1, fd);

			//Incrementing j
			j++;
		}
		

		//Incrementing i	
		i++;

	}

	printf("INFO : Information encryption done\n");
}

//Function defintion
int copy(FILE *fs, FILE *fd)
{
	//Declare variables here
	char buffer;
	if (fs == fd)
	{
		return ERROR;
	}

	printf("INFO : Remaining of source bmp is copied to destination bmp file..\n");
	//Reading the remaining part of source
	while (fread(&buffer, 1, 1, fs))
	{
		//Writing into destination
		fwrite(&buffer, 1, 1, fd);
	}

	printf("INFO : Copying done\n");
}
