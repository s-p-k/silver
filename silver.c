#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void matches(char *tag);

/* void searchTag(const char *tag);

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
	int hflag = 0, nflag = 0, cflag = 0;
	char *tag;

	if (argc == 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	while ((opt = getopt(argc, argv, "cn:h")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		case 'n':
			nflag = 1;
			tag = optarg;
			break;
		case 'c':
			cflag = 1;
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
		if(!result)
			return(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

void
matches(char *tag)
{
	printf("not yet implemented %s\n", tag);
}

/* void */
/* searchTag(const char *tag) */
/* { */
/* 	char line[LINE_MAX]; */
/* 	FILE *fl; */
	
/* 	fl = fopen(BOOKMARKS, "r"); */
/* 	if(!fl) */
/* 		warn("%p", fl); */
/* 	while(fgets(line, sizeof(line), fl) != NULL) { */
/* 		if (strstr(line, tag)) */
/* 			printf("%s", line); */
/* 	} */
/* 	fclose(fl); */
/* 	return; */
/* } */


/* count bookmarks that are tagged with "tag" */

int
countMarks(char *fname, char *str)
{
	FILE *fp;
	int nl = 1;
	int found = 0;
	char temp[512];
	
	if((fp = fopen(fname, "r")) == NULL)
		return(EXIT_FAILURE);

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL)
			found++;
		nl++;
	}

	printf("%d\n", found);
	fclose(fp);

	return(EXIT_SUCCESS);
}
