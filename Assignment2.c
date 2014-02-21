/* Assignment2
	
	CSE 220 T/TH 10:30
	Jackson Curless
	Dylan Coyle
	Phillip Day
*/

#include "common.h"

int page_number = 1;

int main (int argc, char *argv[]) 
{
		
	FILE *source_file = fopen(argv[1], "r");				//opens file in argument1
	//char time[DATE_STRING_LENGTH] = ctime();
	//printf("%s", argv[1]);


	char line[MAX_SOURCE_LINE_LENGTH];					//creates char array of size 256	
	while(fgets(line, MAX_SOURCE_LINE_LENGTH -1, source_file) != NULL)	//while loop: reads in characters and stores them to buffer
	{
		printf("%s \n", line);						//prints line
	}
	fclose(source_file);							//closes file

	return 0;
}

char print_header()
{
	printf("Page %d\n", page_number);
	page_number += 1;
}
