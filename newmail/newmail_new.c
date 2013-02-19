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
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>

int count_msg(char *spoolfile);
char *userfmt(char *fmt, ...);

int msg;
extern char **environ;

int
main(int argc, char *argv[])
{
	char user[25], spool[104];	

	if(argc == 3 && !strcmp(argv[1], "-s"))
		strncpy(spool, argv[2], 104);
	else if(argc == 1) {
		if((strncpy(spool, getenv("MAIL"), 104)) == NULL) {
			fprintf(stderr, "Usage %s: [ -s spoolfile ]\n", argv[0]);
			exit(1);
		}
	} else {
		fprintf(stderr, "Usage %s: [ -s spoolfile ]\n", argv[0]);
		exit(1);
	}

	printf("%d\n", count_msg(spool));

	return 0;
}

int
count_msg(char *spoolfile)
{
	FILE *fp;
	int from;
	regex_t preg;
	char buf[1024];

	msg = 0;
	if((fp = fopen(spoolfile, "r")) == NULL) {
		fprintf(stderr, "can't open spoolfile: %s\n", spoolfile);
		exit(1);
	}
	while(fgets(buf, 1024, fp) != NULL) {
		if((from = regcomp(&preg, "^From:.*", 0))) {
			fprintf(stderr, "could not compile regular expression\n");
			exit(1);
		}
		if(!(from = regexec(&preg, buf, 0, NULL, 0)))
			msg++;
	}

	return msg;
}
