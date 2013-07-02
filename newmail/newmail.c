/* Copyright (C) 2013 Grant Mather <hcaulfield57@gmail.com>
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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(char *spool);
void usage(void);

int
main(int argc, char *argv[])
{
    char *spool;
    char buf[512];

    spool = NULL;
    memset(buf, 0, 512);
    if(argc == 3 && !strcmp(argv[1], "-s"))
        spool = argv[2];
    else if(argc == 1) {
        spool = getenv("MAIL");
        if(spool == NULL) {
            strncat(buf, "/var/mail/", 512);
            strncat(buf, getenv("USER"), 512); 
            spool = buf;
        }
    } else
        usage();

    printf("%d\n", count(spool));
    return 0;
}

int
count(char *spool)
{
    int msg;
    FILE *fp;
    char buf[1024];

    msg = 0;
    if((fp = fopen(spool, "r")) == NULL)
        err(1, "cannot open %s", spool);
    while(fgets(buf, 1024, fp) != NULL) {
        if(buf[0] != 'F')
            continue;
        else if(buf[1] != 'r')
            continue;
        else if(buf[2] != 'o')
            continue;
        else if(buf[3] != 'm')
            continue;
        else if(buf[4] != ' ')
            continue;
        msg++;
    }

    return msg;
}

void
usage(void)
{
    err(1, "usage: newmail [-s spool]\n");
}
