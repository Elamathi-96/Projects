#include "common.h"

int main(int argc, char *argv[])
{
	//Declare variables here
	int status;

	status = validate_inputs(argv);

	if (status == ERROR)
	{
		return -1;
	}

	if (strcmp(argv[1], "-e") == 0)
	{
		status = encrypt(argv);
		if (status == ERROR)
		{
			printf("INFO : Encryption unsuccessfull");
			return -1;
		}
		else
		{
			printf("INFO : Encryption done successfully\n");
		}
	}
	
	else
	{
		status = decryption(argv);

		if (status == ERROR)
		{
			printf("INFO : Decryption unsuccessfull\n");
		}
		else
		{
			printf("INFO : Decryption done successfully\n");
		}

	}
}
