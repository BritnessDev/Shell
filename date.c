#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
	time_t t;
	t = time(NULL);
	struct tm *current_time;

	if(argv[1]==NULL)
	{ 
		current_time = localtime(&t);
		printf("%s", asctime(current_time));
	}

	else if(strcmp(argv[1],"--help") == 0)
	{
		printf("Usage : date [OPTION]... [+FORMAT] \n or:  date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]] \n "
		"Current time in the specified FORMAT \n   -u, --utc, --universal     print or set Coordinated "
		"Universal Time (UTC)\n   --help     \t\t      display helps and exit\n");
	}

	else if(!strcmp(argv[1], "-u") || !strcmp(argv[1],"--utc") || !strcmp(argv[1],"--universal"))
	{  
		current_time = gmtime(&t);
		printf("%s", asctime(current_time));
	}

	else {
		fprintf(stderr, "uwu: Fomate is incorrect\n");
	}

	return 1;
}