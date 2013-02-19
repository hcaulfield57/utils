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
#include <time.h>

#define LAG 1123200

int
main(int argc, char *argv[])
{
	char buf[512], fmt[25];
	time_t jtime;

	jtime = time(NULL);
	jtime -= LAG;

	if(argc > 1 && argv[1][0] == '+') {
		strcpy(fmt, ++argv[1]);
		strftime(buf, sizeof buf, fmt, localtime(&jtime));
		printf("%s\n", buf);
	} else
		printf("%s", ctime(&jtime));

	return 0;
}
