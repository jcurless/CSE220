/* Assignment2
CSE 220 T/TH 10:30
Jackson Curless
Dylan Coyle
Phillip Day
*/

#include "common.h"

int page_number = 1;
int line_number = 51;//initialized to 51 to print a header upon starting
char path[MAX_FILE_NAME_LENGTH];

int main (int argc, char *argv[])
{
	if (realpath (argv[1], path) == 0)//Does the file even???
	  { 
		fprintf (stderr, "Path failed: %s\n", strerror (errno));//Tells the user exactly how they screwed up.
		printf("Exiting now. OKAY BUHBYE, YOU STINKER!\n");//Humorous anecdote ;)
		exit(0); //exits cleanly if there is no such file
	  }
realpath(argv[1], path); //retrieves the absolute file path
FILE *source_file = fopen(argv[1], "r");//opens the file specified in the command line
char line[MAX_SOURCE_LINE_LENGTH];//creates char array of size 256

while(fgets(line, MAX_SOURCE_LINE_LENGTH -1, source_file) != NULL)//while loop: reads in characters and stores them to buffer
	{
		if (line_number > MAX_LINES_PER_PAGE) //checks to see if a new header is needed
			{
				print_header();//calls the print_header function
			}
			
		printf("%d: ", line_number);//lists the line number
		line_number +=1;//increments the line number
		
		if (strlen(line) > 80)//deals with lines in excess of 80 characters
			{
				char *blah = line+79;//points to the address of the 80th character
				char blah2 = *blah;//sets blah2 to the dereferenced value of 80th
				
				sprintf (line, "%.79s", line);//formats so only 80 chars are printed
				puts(line);//prints characters 1 through 80
				*blah = blah2;//dereferenced value gets put back in to its place	
					if (line_number > MAX_LINES_PER_PAGE-1) 
						{//tests for cases where the long line falls on last line of the page
							print_header();//calls the print_header function
						}
				printf("%d: ", line_number);//prints the line number
				printf("%s", blah);//prints the 80th+ characters
				line_number += 1;//increment
			}

		else//used when lines are less than 80 characters
			{
				printf("%s", line);//prints the lines less than 80 characters
			}

	}
printf("\nThe end of the file has been reached.\n");
fclose(source_file);	//closes file cleanly

}

void print_header() //called every time there is a new page
{
		printf("\nPage  %d ", page_number); //prints the page number
		line_number = 1;//the first page is number 1
		page_number += 1;//increments the page number as needed
		
		printf("%s  ", path); //prints the file path
		time_t now;	//declares a time	
		time(&now); //calls the time function for the address of now
		printf("%s\n", ctime(&now));//prints the formatted time
}

