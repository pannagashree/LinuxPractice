#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void main(int argc, char* argv[])
{
	printf("Demonstrating that child gets a copy of parents's address space\n");
	int pid, ppid, ret, cpid;
	char *command;
	ret=fork();
	if(ret==0)
	{
		printf("In child\n");
		pid=getpid();
		printf("Child's process ID = %d\n", pid);
		asprintf(&command,"cat /proc/%d/maps", pid);
		system(command);
		printf("########### End of Child's memory map ########### \n");
		execve("./hello",argv,NULL);
	}
	else
	{
		printf("In Parent\n");
		ppid=getpid();
		printf("Parent's process ID =%d\n", ppid);
		asprintf(&command,"cat /proc/%d/maps", ppid);
		system(command);
		cpid = wait(NULL);
		printf("The pid of terminated child = %d\n", cpid);
		printf("########### End of Parent's memory map ########### \n");
	}
}
