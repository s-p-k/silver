#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void matches(char *tag);

int searchTag(char *fname, char *str);

int countMarks(char *fname, char *str);

void
usage(const char *arg)
{
	printf("Usage: %s [-h] [-c tag]\n", arg);

}

int
main(int argc, char *argv[])
{

	int opt, result;
	int hflag = 0, cflag = 0, nflag = 0, sflag = 0;
	char *tag;

	if (argc == 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	while ((opt = getopt(argc, argv, "cns:h")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		case 'c':
			cflag = 1;
			tag = optarg;
			break;
		case 'n':
			nflag = 1;
			tag = optarg;
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
	if (nflag)
		matches(tag);
	if (cflag) {
		result = countMarks(BOOKMARKS, argv[2]);
		if(result == -1)
			return(EXIT_FAILURE);
	}

	if (sflag) {
		result = searchTag(BOOKMARKS, argv[2]);
		if(result == -1)
			return(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

void
matches(char *tag)
{
	printf("not yet implemented %s\n", tag);
}

int
countMarks(char *fname, char *str)
{
	FILE *fp;
	int nl = 1;
	int found = 0;
	char temp[512];
	
	if((fp = fopen(fname, "r")) == NULL)
		return(-1);

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL)
			found++;
		nl++;
	}

	printf("%d\n", found);
	fclose(fp);

	return(EXIT_SUCCESS);
}

int
searchTag(char *fname, char *str)
{

	FILE *fp;
	char temp[512];

	if((fp = fopen(fname, "r")) == NULL)
		return(-1);

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL)
			/* We need to show the link only, not the whole line */
			printf("\n%s", temp);
	}
	fclose(fp);

	return(EXIT_SUCCESS);
}
