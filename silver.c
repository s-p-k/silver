#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"

void prinTags(char *fname);

void searchTag(char *fname, char *str);

void countMarks(char *fname);

int charPosition(char *str);

void partOfString(char *str, int position);

void
usage(const char *arg)
{
	printf("Usage: %s [-h] [-n] [-c tag] [-s tag]\n", arg);
}

int
main(int argc, char *argv[])
{

	int opt;
	int hflag = 0, /* cflag = 0, */ nflag = 0, pflag = 0, sflag = 0;
	char *tag;

	if (argc == 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	while ((opt = getopt(argc, argv, "cns:nhp")) != -1) {
		switch (opt) {
		case 'h':
			hflag = 1;
			break;
		/* case 'c': */
		/* 	cflag = 1; */
		/* 	tag = optarg; */
		/* 	break; */
		case 'n':
			nflag = 1;
			break;
		case 's':
			sflag = 1;
			tag = optarg;
			break;
		case 'p':
			pflag = 1;
			break;
		default:
			errx(EXIT_FAILURE, "see %s -h", argv[0]);
		}
	}

	if (hflag)
		usage(argv[0]);
	/* if (cflag) { */
	/* 	if (argc <= 2) { */
	/* 		usage(argv[0]); */
	/* 		return(EXIT_FAILURE); */
	/* 	} */
		/* countMarks(BOOKMARKS, argv[2]); */
	/* 	countMarks(BOOKMARKS); */
	/* 	return(EXIT_SUCCESS); */
	/* } */
	if (sflag) {
		searchTag(BOOKMARKS, tag);
		return(EXIT_SUCCESS);
	}
	if (pflag) {
		prinTags(BOOKMARKS);
		return(EXIT_SUCCESS);
	}
	if (nflag)
		countMarks(BOOKMARKS);
	return(EXIT_SUCCESS);
}

void
prinTags(char *fname)
{
	FILE *fp;
	int ch;

	if (!(fp = fopen(fname, "r")))
		err(1, "%s", fname);
	(ch = fgetc(fp));
	while (ch != EOF) {
		/* putchar(ch); */
		if (ch == '\n') {
			ch = fgetc(fp);
			continue;
		}
		if (ch == '@')
			printf("duck\n");
		ch = fgetc(fp);
	}
	return;
}

void
countMarks(char *fname)
{
	FILE *fp;
	int found = 0;
	int ch;
	
	if(!(fp = fopen(fname, "r")))
		err(1, "%s", fname);
	(ch = fgetc(fp));
	while (ch != EOF) {
		if (ch == '@')
			found++;
		ch = fgetc(fp);
	}
        printf("%d\n", found);
	fclose(fp);

	return;
}

int
charPosition(char *str)
{
	char c = ':';
	int position = 0;
	int i, l;

	l = strlen(str);
	for (i = 0; i <= l; i++) {
		if (str[i] == c)
			break;
		position++;
	}
	return position + 2;
}

void
partOfString(char *str, int position)
{
	int l = strlen(str);
	int i;

	for (i = position; i <= l; i++)
		printf("%c", str[i]);
	return;
}

void
searchTag(char *fname, char *str)
{

	FILE *fp;
	char temp[512];
	int c;
	char *s = temp;

	if(!(fp = fopen(fname, "r")))
		err(1, "%s", fname);

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			c = charPosition(temp);
			partOfString(s, c);
		}
	}
	fclose(fp);
	return;
}
