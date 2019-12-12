#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdlib.h>

void main(int argc, char *argv[])
{
	int cpid, ppid, ret, shared_len=100,fd;
	char *command,*shm;
	ppid=getpid();
        printf("Parent's process ID = %d\n", ppid);
	printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps",ppid);
        system(command);
        printf(" ########### End of Parent's memory map before mmap ########### \n");
	fd=open("textdoc",O_RDWR);
	shm=mmap(0, shared_len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, fd, 0);
	close(fd);
	printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps", ppid);
        system(command);
        printf(" ########### End of Parent's memory map after mmap ########### \n");
	printf("Contents of shared region of file:\n");
	for(int i=0;i < shared_len;i++)
	{
		char c;
		c=shm[i];
		printf("%c",c);
	}
	printf("\n===========================\n");
	ret = fork();
	if(ret == 0)
	{
		printf("In child\n");
		cpid = getpid();
        	printf("Parent's process ID = %d\n", cpid);
		printf("\n ############################################################# \n");
        	asprintf(&command,"cat /proc/%d/maps", cpid);
        	system(command);
        	printf(" ########### End of Child's memory map ########### \n");
		shm[20]='f';
		printf(" Contents of shared region of file after child modifying:\n");
		for(int i=0;i < shared_len;i++)
		{
			char c;
			c=shm[i];
			printf("%c",c);
		}
		printf("\n======================\n");
		execve("./hello1", argv, NULL);
/*		for(int i=0;i<75;i++)
                	sleep(1);
	        printf(" Contents of shared region of file in child after a while:\n");
        	for(int i=0;i<shared_len;i++)
        	{	
                	char c;
                	c=shm[i];
                	printf("%c",c);
        	}
        	printf("\n===========================\n");*/
	
	}
	else
	{
		for(int i=0;i<50;i++)
			sleep(1);
		shm[21]='g';
		printf(" Contents of shared region of file after parent modifying:\n");
                for(int i=0;i < shared_len;i++)
                {
                        char c;
                        c=shm[i];
                        printf("%c",c);
                }
                printf("\n======================\n");
		wait(NULL);
	}
}

