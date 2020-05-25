/*
 * This program is the implementation of tee command 
 * This program supports only -a option */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void main(int argc, char *argv[])
{
	int fd,opt,append=0;
	char input[4096]={'\0'};
	char filename[20];
	/* To parse the command line arguments*/
	while((opt = getopt(argc, argv, ":a"))!=-1)
	{
		switch(opt)
		{
			case 'a': append =1;
					  break;
			default: printf("Invalid option\n");
		}
	}
	for(;optind<argc;optind++)
		strcpy(filename,argv[optind]);
	fd = open(filename,O_CREAT|O_WRONLY,0666);
	read(STDIN_FILENO,input,4096);
	write(STDOUT_FILENO,input,sizeof(input));
	if(append)
		lseek(fd,0,SEEK_END); /*Another way would be to open the file in append mode with O_AAPEND flag when program is called with -a option*/
	write(fd,input,strlen(input));
}
