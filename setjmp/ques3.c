/*Implementation of setenv() and unsetenv() using getenv() and putenv()*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int setenv(const char *name, const char *value, int overwrite)
{
	int nbytes = sizeof(name)+sizeof(value)+2;
	char *buffer = (char *)malloc(nbytes);
	
	sprintf(buffer,"%s=%s",name,value);
	printf("Name=Value pair to be added: %s\n",buffer);
	
	char *val = getenv(name);
	if(val == NULL || (val !=NULL && overwrite == 1))
	{
		int ret = putenv(buffer);
		printf("Environment list after setenv\n\n");
		system("printenv");
		if(ret != 0)
			return -1;
		else
			return 0;

	}
	else
	{
		printf("Environment list after setenv [in else part] \n\n");
		system("printenv");
	}

}

int unsetenv(const char *name)
{
	char *val = getenv(name);
	
	if(val != NULL)
	{
		printf("Name=Value pair that is getting unset: %s=%s\n\n", name, val);
		int ret = putenv(name);
		printf("Environment list after unsetenv\n");
		system("printenv");
		if(ret != 0)
			return -1;
		else
			return 0;
	}

}

int main(int argc, char *argv[])
{
	int choice;
	while(1)
	{
		printf("Operation to be performed?\n 1. setenv \n 2. unsetenv\n 3.exit\n");
		scanf("%d", &choice);
		char name[20];
		char val[20];
		char overwriteOption[4];
	       	int ret;
		switch(choice)
		{
			case 1: printf("Enter the name & value thst needs to be added to the enviornment\n");
				scanf("%s %s", name, val);
				printf("Do you want to overwrite if the value already exists??\n");
				scanf("%s", overwriteOption);	
				printf("Calling setenv...\n");
				if(strcasecmp(overwriteOption, "yes") == 0)
					ret = setenv(name, val, 1);
				else
					ret = setenv(name, val, 0);
				if(ret != 0)
					printf("setenv failed with error: %s\n",strerror(errno));
				printf("**********************************************************************************************************\n");
				break;
			case 2: printf("Enter the variable name that needs to be removed from the enviornment\n");
				scanf("%s", name);
				printf("Calling unsetenv...\n");
				ret = unsetenv(name);
				if(ret != 0)
					printf("unsetenv failed with error: %s\n",strerror(errno));
				printf("**********************************************************************************************************\n");
				break;
			case 3: exit(0);
			default: printf("Invalid option\n");
		}
	}
}
