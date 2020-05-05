/*
 * This is the cp command implementation using lseek's new SEEK_DATA approach
 * */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
void main(int argc, char *argv[])
{
	int fd1 = open(argv[1],O_RDONLY);
	int fd2 = open(argv[2],O_CREAT|O_EXCL|O_WRONLY,0666);
	if(fd2 == -1)
		fd2 = open(argv[2],O_CREAT|O_WRONLY,0666);
	int buf_size=4096,n_read;
	char buf[buf_size];
	memset(buf,'\0',buf_size);
	/*SEEK_DATA seeks the file offset from current position to a place 
	 * where next data is found, skipping the file holes*/
	int offset = lseek(fd1,0,SEEK_DATA);
	lseek(fd2,offset,SEEK_SET);
	while((n_read = read(fd1,buf,buf_size))>0)
	{
		write(fd2,buf,n_read);
		offset = lseek(fd1,offset+n_read,SEEK_DATA);
		lseek(fd2,offset,SEEK_SET);
		memset(buf,'\0',buf_size);

	}
}
