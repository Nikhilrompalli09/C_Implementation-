//other user end is in  end1 in project day11_june6 

include<stdio.h>
include<stdlib.h>
include<string.h>
include<pthread.h>
struct message
{
	int size;
	char msg[256];
};

FILE* fRead, *fWrite;
char* readInput()
{
	char* input = (char*)malloc(256 * sizeof(char));
	gets(input);
	return input;
}
void* readMsg(void*)
{
	while (1)
	{
		char* len = (char*)malloc(4 * sizeof(char));
		fseek(fRead, 0, SEEK_END);
		while (fread(len, sizeof(int), 1, fRead) == 0){
		}
		char* messg = (char*)malloc(*(int*)len* sizeof(char));
		int l = *(int*)len;
		if (l == 0)
		{
			char msg[] = "Message read by other end";
			printf("-%s\n",msg);
		}
		else
		{
			fread(messg, *(int*)len, 1, fRead);
			messg[l] = '\0';
			printf("\t\t\t\t\t\t\t\t%s\n", messg);
			int len = 0;
			char* str = (char*)malloc(4*sizeof(char));
			memcpy(str,&len, sizeof(int));			//int will convert into 4 bytes of string
			fwrite(str, sizeof(len), 1, fWrite);
			fflush(fWrite);
		}
	}
	pthread_exit(NULL);
	return NULL;
}
void* writeMsg(void*)
{
	while (1)
	{
		char* msg = readInput();
		int len = strlen(msg);
		char* str = (char*)malloc((4 + len)*sizeof(char));
		memcpy(str, &len, sizeof(int));			//int will convert into 4 bytes of string
		memcpy(str + sizeof(int), msg, len);	//msg will be appened after int
		fwrite(str, sizeof(len) + len, 1, fWrite);
		fflush(fWrite);
	}
	pthread_exit(NULL);
	return NULL;
}
int main()
{
	fWrite = fopen("file2.disk", "ab+");
	fRead = fopen("C:\\Users\\lenovo\\Documents\\Visual Studio 2013\\Projects\\day11_june7\\day11_june7\\file1.disk", "ab+");
	pthread_t t1, t2;
	pthread_create(&t1, NULL, writeMsg, NULL);
	pthread_create(&t2, NULL, readMsg, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	fclose(fWrite);
	fclose(fRead);
	system("pause");
}
