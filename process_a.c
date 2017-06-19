#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	char* cp = (char*)malloc(sizeof(char)*10);
	int i = 1;

	char* cArray = "HI, bro";
	strcpy(cp, cArray);

	printf("(%p)\n", (void*)cp);

	for(i = 1; i<=1000; i++)
	{
		printf("%d, %s ,(%p)\n", i, cp, (void*)cp );
		sleep(2);
	}
	free(cp);
	return 0;
}
