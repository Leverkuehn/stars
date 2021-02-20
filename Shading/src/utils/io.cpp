#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>

char* ReadStringFromFile(const char *filename)
{
	char *buffer = 0;
	FILE *file = fopen(filename, "r");
	long length;
	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = (char*)malloc(length);
		memset(buffer, 0, length);

		if (buffer)
			fread(buffer, 1, length, file);

		fclose(file);
	}

	return(buffer);
}