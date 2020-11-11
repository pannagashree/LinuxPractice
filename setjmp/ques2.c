/*Observing what happens when we try to longjmp() into a function that has already returned
 * Observation: It causes segmentation fault.
 * 		longjmp actually does go to the point of where setjmp was set in the other function 
 * 		but while returning from the function, unwinding of stack causes a problem (since the function has already returned)
 * 		and thus the program crashes*/
#include<stdio.h>
#include<setjmp.h>
jmp_buf env;

void func1()
{
	printf("In func1()\n");
	
	printf("Executing setjmp\n");

	if(setjmp(env) == 0)
	{
		printf("setjmp executed\n");
	}
	else
	{
		printf("Here...After longjmp\n");
	}
}
int main()
{
	printf("In Main\n");

	printf("Calling func1()\n");
	func1();
	
	printf("Executing longjmp\n");
	longjmp(env,1);
}

