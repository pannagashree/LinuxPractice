#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<fcntl.h>

void main()
{
	printf("Executing hello1....\n");
	int shared_len=100, fd, pid;
	char *command;
	pid = getpid();
	printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps", pid);
        system(command);
        printf(" ########### End of Child's memory map after exec ########### \n");
	fd=open("textdoc",O_RDWR);
        char* shm = mmap(0, shared_len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, fd, 0);
	close(fd);
	printf("\n ############################################################# \n");
        asprintf(&command,"cat /proc/%d/maps", pid);
        system(command);
        printf(" ########### End of Child's memory map after mmap ########### \n");
	printf(" Contents of shared region of file from exec process:\n");
	for(int i=0;i<shared_len;i++)
	{
		char c;
                c=shm[i];
                printf("%c",c);
	}
	printf("\n===========================\n");
	for(int i=0;i<75;i++)
		sleep(1);
	printf(" Contents of shared region of file from exec process after a while:\n");
        for(int i=0;i<shared_len;i++)
        {
                char c;
                c=shm[i];
                printf("%c",c);
        }
        printf("\n===========================\n");
}
