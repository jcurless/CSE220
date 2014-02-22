/* Assignment2
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#include "common.h"	//include the file common.h

int page_number = 1; 	//intializes the page number at 1
int line_number = 51;  	//initalizes the line number at 51
char path[MAX_FILE_NAME_LENGTH];	//creates char array "path" of length MAX_FILE_NAME_LENGTH

int main (int argc, char *argv[])
{

	if (realpath (argv[1], path) == 0) //if there is no file 
	{ 
		fprintf (stderr, "Path failed: %s\n", strerror (errno));
		printf("Exiting now. OKAY BUHBYE, YOU STINKER!\n");	//prints errar message
		exit(0); //exits cleanly if there is no such file
	}
	realpath(argv[1], path); //retrieves the absolute file path
	FILE *source_file = fopen(argv[1], "r");	//opens file in argument1

	char line[MAX_SOURCE_LINE_LENGTH];	//creates char array of size 256
	
	while(fgets(line, MAX_SOURCE_LINE_LENGTH -1, source_file) != NULL)	//while loop: reads in characters and stores them to buffer
	{

		if (line_number > MAX_LINES_PER_PAGE) 	//quality check to make sure line number is less the MAX_LINES_PER_PAGE
			{
				print_header();		//calls the print_header function
			}
			
		printf("%d: ", line_number);	//lists the line numbers
		line_number +=1;		//increments the line number by 1
		
		
		printf("%s \n", line);	//prints line
	}
	fclose(source_file);	//closes file

}

void print_header() //called every time there is a new page
{
		printf("\nPage  %d ", page_number); 	//prints the page number
		line_number = 1;
		page_number += 1;			//increments
		
		printf("%s  ", path); 			//prints the file path
		time_t now;	//declares a time	
		time(&now); 	//calls the time function for the address of now
		printf("%s\n\n", ctime(&now));		//prints the formatted time
}

