#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define bmarks "/home/spk/bookmarks.txt"

void searchTag(const char *tag);

void
usage(const char *arg)
{
	printf("Usage: %s [-h] [-s tag]\n", arg);

}

int
main(int argc, char *argv[])
{
	int opt;
	int hflag = 0, sflag = 0;
	char *tag;

	if (argc == 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	while ((opt = getopt(argc, argv, "s:sh")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		case 's':
			sflag = 1;
			tag = optarg;
			break;
		default:
			errx(EXIT_FAILURE, "see %s -h", argv[0]);		
		}
	}

	if (hflag)
		usage(argv[0]);
	if (sflag)
		searchTag(tag);


	return EXIT_SUCCESS;
}

void
searchTag(const char *tag)
{
	char line[LINE_MAX];
	FILE *fl;
	
	fl = fopen(bmarks, "r");
	if (!fl)
		warn("%p", fl);
	while(fgets(line, sizeof(line), fl) != NULL) {
		if (strstr(line, tag))
		    printf("%s", line);
	}
	fclose(fl);
	return;
}
