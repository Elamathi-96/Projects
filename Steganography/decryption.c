#include "common.h"

int decryption(char **argv)
{
	int passcode, pass = 0, len;
	FILE *fs, *fd;
	char byte, temp;
	int i = 0, status;

	printf("*DECRYPTION PROCEDURE STARTED*\n");
	printf("INFO : Opening %s file..\n", argv[2]);
	fs = fopen(argv[2], "rb");
	fseek(fs, 54, SEEK_SET);


	if (argv[3] == NULL)
	{
		fd =fopen("info.txt", "w");

		if (fd == NULL)
		{
			perror("info.txt");
			exit(1);
		}
		printf("INFO : Output file not mentioned.. Opening info.txt\n");
	}

	else
	{
		fd = fopen(argv[3], "w");

		if (fd == NULL)
		{
			perror(argv[3]);
			exit(1);
		}
		printf("INFO : Opening %s file\n", argv[3]);
	}

	status = pass_decrypt(fs);

	if (status == ERROR)
	{
		printf("INFO : Invalid source or destination file\n");
		return ERROR;
	}

	if (status == ERROR1)
	{
		printf("INFO : Wrong password..Decryption Terminated\n");
		return ERROR;
	}


	printf("INFO : Length decryption started..\n");
	len = length_decrypt(fs);

	if (len == ERROR)
	{
		printf("Invalid source or destination file\n");
		return ERROR;
	}
	printf("INFO : Length decryption done\n");
	
	printf("INFO : Information decryption started..\n");
	status = txt_decrypt(len, fs, fd);
	if (status == ERROR)
	{
		printf("INFO : Invalid source or destination file\n");
		return ERROR;
	}
	printf("INFO : Information decryption done\n");
	
	if (argv[3])
	{
		printf("INFO : Information is kept in %s\n", argv[3]);
	}

	else
	{
		printf("INFO : Information is kept in info.txt\n");
	}

	fcloseall();	

	return SUCCESS;
}
	
//Function definiton
int pass_decrypt(FILE *fs)
{
	//Declare variables here
	char byte, temp;
	int pass  = 0, i = 0;
	int passcode;

	printf("ENTER PASSCODE :");
	scanf("%d", &passcode);
	
	printf("INFO : Passcode decryption started..\n");
	
	//Logic : Reading a byte from the bmp file, ORing with pass and storing in pass
	for (i = 0; i < 32; i++)
	{
		//Reading from bmp file
		if (fread(&byte, 1, 1, fs) == 0)
		{
			return ERROR;
		}

		//Getting lsb
		temp = byte & 1;

		if (temp)
		{
			//ORing with pass
			pass = pass | (temp << i); 
		}

	}

	if (passcode != pass)
	{
		return ERROR1;
	}
	
	printf("INFO : Passcode decryption done..Entered passcode is correct\n");
}

//Function definiton
int length_decrypt(FILE *fs)
{
	//Declare variables here
	char byte;
	int len  = 0, i = 0;

	//Logic : Reading a byte from the bmp file, ORing with pass and storing in pass
	while (i < 32)
	{
		//Reading from bmp file
		if (fread(&byte, 1, 1, fs) == 0)
		{
			return ERROR;
		}

		//Getting lsb
		byte = byte & 1;

		if (byte)
		{
			//ORing with pass
			len = len | (byte << i); 
		}

		//Incrementing i
		i++;
	}

	//Returning length
	return len;
}

//Function definiton
int txt_decrypt(int len, FILE *fs, FILE *fd)
{
	//Declare variables here
	char byte, temp = 0;
	int i = 0, j = 0;
	char text[len];
	
	//Logic : Reading a byte from the bmp file, ORing with pass and storing in pass
	while(i < len)
	{
		j = 0;
		while (j < 8)
		{
			//Reading from bmp file
			if (fread(&byte, 1, 1, fs) == 0)
			{
				return ERROR;
			}

			//Getting lsb
			byte = byte & 1;

			//ORing with pass
			temp = temp | (byte << j);
		
			//Incrementing j
			j++;

		}

		
		//Incrementing i
		i++;
		//Storing in destination txt file
		fwrite(&temp, 1, 1, fd);
		temp = 0;
	}


}
