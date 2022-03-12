#include <stdio.h>
#include <string.h>


int main()
{
	char array[255];
	printf("plese enter text: ");
	fgets(array, 255, stdin);
	char ans[255];
	strcpy(ans, array);
	for(int i = 0; i < strlen(array); i++)
	{
		printf("place %i: %c\n", i, array[i]); 
	}

	return 0; 
}
