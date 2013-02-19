/* Copyright (C) 2013, Grant Mather <hcaulfield57@gmail.com>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>

void usage(void);
int count(char *spoolfile);

int
main(int argc, char *argv[])
{
	char *spool;

	if(argc == 3 && !strcmp(argv[1], "-s"))
		spool = argv[2];
	else if(argc == 1) {
		spool = getenv("MAIL");
		if(spool == NULL)
			usage();
	} else
		usage();

	printf("%d\n", count(spool));
	return 0;
}

int
count(char *spoolfile)
{
	int reg, msg;
	char buf[1024];
	regex_t preg;
	FILE *fp;

	if((fp = fopen(spoolfile, "r")) == NULL) {
		fprintf(stderr, "can't open spoolfile: %s\n", spoolfile);
		exit(1);
	}
	msg = 0;
	while(fgets(buf, 1024, fp) != NULL) {
		if((reg = regcomp(&preg, "^From:.*", 0)) != 0) {
			fprintf(stderr, "could not compile regex\n");
			exit(1);
		}
		if(!(reg = regexec(&preg, buf, 0, NULL, 0)))
			msg++;
	}
	return msg;
}

void
usage(void)
{
	fprintf(stderr, "Usage newmail: [ -s spoolfile ]\n");
	exit(1);
}
