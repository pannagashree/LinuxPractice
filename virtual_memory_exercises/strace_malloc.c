#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>

void main()
{
	int pid;
	char *command;
        pid = getpid();
        printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps", pid);
        system(command);
        printf(" ########### End of Process memory map before malloc ########### \n");
//	mmap(NULL, 150000, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	void *ptr=malloc(132000);
	printf("Returned address is %p\n", ptr);
        printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps", pid);
        system(command);
        printf(" ########### End of Child's memory map after malloc ########### \n");
}

