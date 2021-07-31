#include "common.h"

int edit(char *origin_fil, char *action, char *change)
{
	char * act = malloc(sizeof(char) * 10);
	char * name = malloc(sizeof(char) * 10);
printf("Entered edit function\n");	
	switch(action[1])
	{
		case 't':
		{
			strcpy(act,"TIT2");
			strcpy(name,"title");
			break;
		}
		case 'T':
		{
			strcpy(act, "TRCK");
			strcpy(name,"track");
			break;
		}
		case 'a':
		{
			strcpy(act, "TPE1");
			strcpy(name,"artist");
			break;
		}
		case 'A':
		{
			strcpy(act, "TALB");
			strcpy(name,"Album");
			break;
		}
		case 'c':
		{
			strcpy(act, "TCON");
			strcpy(name,"comment");
			break;
		}
		case 'y':
		{
			strcpy(act, "TYER");
			strcpy(name,"year");
			break;
		}
		//case 'g':
		{
			//strcpy(act, "");
			break;
		}
		default:
		{
			printf("Enter a valid action\n");
			exit(0);

		}
	}
	printf("Copied action\n");
	FILE *f1, *f2, *f3;

	char *temp = malloc(sizeof(char) * 30);
	strcpy(temp, change);
	char *buffer = malloc(sizeof(char) * 30);
	char file1[100] = "k.mp3", file2[100], file3[100] = "k.mp3";

	f1 = fopen(file1, "wb");
	f2 = fopen(origin_fil, "rb");

	char length;
	char lam;// = malloc(sizeof(char));;
	int size, ch;
	unsigned char pad1[7] = { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
	unsigned char pad2[3] = { 0x00, 0x00, 0x00 }; 
	//char artist[31], song[31], album[31], year[4], comment[31], genre[4]; 
	char changesize30[31];
	char changesize4[4];
	int flag = 0;

	fprintf(f1, "ID3"); 
	fwrite(pad1, sizeof(pad1), 1, f1);
	fseek(f2,10,SEEK_SET);//went to 10th
	int count = 8;
	while(1)
	{
	//	fread(buffer, 1, 4, f2);
		fread(buffer, 4, 1, f2);

		fseek(f2, 3, SEEK_CUR);//next three dots
		//fscanf(f2, "%s", &lam);//get the size from original
		fread(&lam, 1, 1, f2);
		//fread(length, 1, 1, f2);
		//fwrite(f1, 1, 10, f2);//atoi(length) + 3, f2);	
	
		fseek(f2,-8,SEEK_CUR);//go 4 bytes back from cur pos
		printf("Buffer %s\taction %s\n", buffer, act);		
		if(strcmp(buffer, act) == 0)
		{
	printf("In while loop\n");
			//fseek(f2,-4,SEEK_CUR);//go 4 bytes back from cur pos

			fprintf(f1, "%s", act); 

			// Essential 3 NULL bits required for seperation. 
			fwrite(pad2, sizeof(pad2), 1, f1); 

			size = strlen(temp); 
			size++; // Calculating size. 

			// Appending the size of the track number to tag. 
			fprintf(f1, "%c", size); 

			// Essential 3 NULL bits required for seperation. 
			fwrite(pad2, sizeof(pad2), 1, f1); 

			// Adding tag number entered by the user. 
			fprintf(f1, "%s", temp); 
			if((strcmp(buffer, "TYER") == 0))
			{
				flag = 1;
				strcpy(changesize4, temp);
			}
			else
			{
				strcpy(changesize30, temp);
			}
			fseek(f2, lam + 10, SEEK_CUR);
			break;
		}
		else
		{
			char *buff1 = malloc(sizeof(char) * 30);
			fread(buff1, 1, 7, f2);
			fwrite(buff1, 1, 7, f1);
			fread(&length, 1, 1, f2);
			fseek(f2, -1, SEEK_CUR);
			//fwrite(f1, 1, 10, f2);//atoi(length) + 3, f2);
			char *buff2 = malloc(sizeof(char) * 30);
			fread(buff2, 1, length + 3, f2);
			fwrite(buff2, 1, length + 3, f1);
		}
	count --;
	}
	printf("remaining info\n");
	while ((ch = fgetc(f2)) != EOF) // Appending tagging info. 
	{
		fputc(ch, f1); 
	}
printf("Head edited\n");
	//////////////////////////////////////////tail

	switch(action[1])
	{
		case 't'://TIT2
		{
			fseek(f1, -125, SEEK_END);
			fwrite(changesize30,30,1,f1);
			break;
		}
		case 'a'://TPE1
		{
			fseek(f1, -95, SEEK_END);
			fwrite(changesize30,30,1,f1);
			break;
		}
		case 'A'://TALB
		{
			fseek(f1, -65, SEEK_END);
			fwrite(changesize30,30,1,f1);
			break;
		}
		case 'y'://TYER
		{
			fseek(f1, -35, SEEK_END);
			fwrite(changesize4,4,1,f1);
			break;
		}
		case 'c'://COMM
		{

			fseek(f1, -31, SEEK_END);
			fwrite(changesize30,30,1,f1);
			break;
		}
		default:
		{
			printf("enter valid\n");
		}
	}
	fcloseall();

	FILE *fz, *fd;

	fz = fopen("k.mp3", "rb");
	fd = fopen(origin_fil, "wb");

	while((ch = fgetc(fz)) != EOF)
	{
		fputc(ch, fd);
	}
	remove("k.mp3");

	fcloseall();

	//fclose(f1);
	//fclose(f2);
	//fclose(f3);
return SUCCESS;
}
