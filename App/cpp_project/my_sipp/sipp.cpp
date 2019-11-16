#include "sipp.hpp"

void help()
{
	printf("need two para.");
}

int main(int argc, char *argv[])
{
    if(argc < 2)
	{
		help();
		exit(EXIT_OTHER);
	}

    return 0;
}

