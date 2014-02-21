#include "common.h"

int main (int argc, char *argv[]) 
{
		
	FILE *source_file = fopen(argv[1], "r");
	//char time[DATE_STRING_LENGTH] = ctime();
	//printf("%s", argv[1]);


	char line[MAX_SOURCE_LINE_LENGTH];
	while(fgets(line, MAX_SOURCE_LINE_LENGTH -1, source_file) != NULL)
	{
		printf("%s \n", line);
	}
	fclose(source_file);

	return 0;
}
