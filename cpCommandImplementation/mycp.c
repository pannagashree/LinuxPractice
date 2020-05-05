/*
 * This program provides the implementation of cp command using fiemap ioctl approach.
 * It just has the basic structure to implement the functionality. 
 * However it doesn't do error handling.
 * */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/fs.h>
#include<sys/ioctl.h>
#include<string.h>
#include "fiemap.h"

void main(int argc, char *argv[])
{
	off_t last_ext_logical=0;
	int last_ext_len =0, last_read_size =0,last=0,size,i;
	char command[80],value[100];
	/*Gets the disk space used by the file in KB*/
	snprintf(command,sizeof(command),"du -k %s|cut -f1",argv[1]);
	FILE *fp=popen(command,"r");
	fgets(value,sizeof(value),fp);
	size=atoi(value);
	/*Converting the disk usage by the file into bytes*/
	size= size*1024;
	int fd1 = open(argv[1],O_RDWR);
	int fd2 = open(argv[2],O_CREAT|O_WRONLY,0666);
	int buf_size=4096;
	char buf[buf_size];
	char fiemap_buf[4096];
	struct fiemap *fiemap = (struct fiemap*)fiemap_buf;
	struct fiemap_extent *fm_extents = &fiemap->fm_extents[0];
	int count = (sizeof(fiemap_buf) - sizeof (*fiemap))/sizeof (struct fiemap_extent);
	memset (&fiemap_buf, 0, sizeof fiemap_buf);

	fiemap->fm_start = 0;
	do
	{

		fiemap->fm_extent_count = count;
		fiemap->fm_length = FIEMAP_MAX_OFFSET;

		ioctl (fd1, FS_IOC_FIEMAP, fiemap);
		
		if(fiemap->fm_mapped_extents == 0)
			break;
		for(i=0; i< fiemap->fm_mapped_extents; i++)
		{
			off_t ext_logical = fm_extents[i].fe_logical;
			int ext_len=fm_extents[i].fe_length;
			if(fm_extents[i].fe_flags & FIEMAP_EXTENT_LAST)
			{
				last_ext_logical=ext_logical;
				last_ext_len=ext_len;
				last = 1;
			}
			lseek(fd1,ext_logical,SEEK_SET);
			/*File offset of dest file is seeked to a position where the next actual disk space is allocated on src file*/
			lseek(fd2,ext_logical,SEEK_SET);
			while(0<ext_len)
			{
				if(ext_len<buf_size)
					buf_size=ext_len;
				memset(buf,'\0',buf_size);
				ssize_t n_read=read(fd1,buf,buf_size);
				if(n_read==0)
				{
					last_read_size = last_ext_len-ext_len;
					break;
				}
				ext_len -=n_read;
				write(fd2,buf,n_read);
			}
		}
		fiemap->fm_start =  fm_extents[i-1].fe_logical + fm_extents[i-1].fe_length; 
	}while(!last);
	/*Restores the null bytes at the end of the dest file, just to maintain the length as that of src file */
	if(last_ext_logical+last_read_size < size)
		ftruncate(fd2,size);
}
