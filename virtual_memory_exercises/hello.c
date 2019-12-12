#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void main()
{
	char *command;
	for(int i=0;i<10;i++)
		printf("Hello\n");
	int pid = getpid();
	printf("Child's process ID after exec = %d\n",pid);
	asprintf(&command,"cat /proc/%d/maps", pid);
        system(command);	
}
