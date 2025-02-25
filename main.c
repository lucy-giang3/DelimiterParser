#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "token.h"

/*
 * main
 */
int
main(int argc, char **argv)
{
    char *ptable[MAXCOL];       /* array of pointers to column starts */
    char buf[BUFSZ];            /* input buffer */
    unsigned long linecnt = 0;  /* input line number (record number) counter */
    unsigned long dropcnt = 0;  /* number of input lines dropped counter */
    int cols = 0;               /* number of columns in the input */
    char *ptr;                  /* pointer for use by strtoul() */


    if ((argv + 1) == NULL) {
        fprintf(stderr, "%s: column value %d, out of range, min %d max is %d\n",                                                                                                                               *argv,
                cols, MINCOL, MAXCOL);
        return EXIT_FAILURE;
    }
    int caseOne = 0; /* -c# */
    int caseTwo = 0; /* -c # */
    if (argc == 3) {
        if (strncmp("-c", *(argv + 1), 2) == 0) {
            /* -c # */
            if (strcmp("\0", (*(argv + 1) + 2)) == 0) {
                caseOne = 1;
            }
        }
    }
    else if (argc == 2) {
        if (strncmp("-c", *(argv + 1), 2) == 0) {
            /* -c# */
            caseTwo = 1;
        }
    }
    /* if not formatted like any of the two cases */
    if (caseOne == 0 && caseTwo == 0) {
        fprintf(stderr, "Usage: %s -c #\n", *argv);
        return EXIT_FAILURE;
    }

    errno = 0;

    if (caseOne)
        cols = (int)strtol(*(argv + 2), &ptr, 10);
    else if (caseTwo)
        cols = (int)strtol(((*(argv + 1) + 2)), &ptr, 10);
    /* if there is error from strtol, print error */
    if (cols == 0) {
        fprintf(stderr, "Usage: %s -c #\n", *argv);
        return EXIT_FAILURE;
    }
    /* if cols is not between MINCOL AND MAXCOL (inclusive), print error */
    else if (cols < MINCOL || cols > MAXCOL) {
        fprintf(stderr, "%s: column value %d, out of range, min %d max is %d\n",                                                                                                                               *argv, cols, MINCOL, MAXCOL);
        return EXIT_FAILURE;
    }
    if ((*ptr != '\0') || (errno != 0)) {
        fprintf(stderr, "%s: improper column value\n", *argv);
        EXIT_FAILURE;
    }

    /*
     * read the input one line at a time, break into tokens and write out the
     * selected columns in a "debugging" format
     */
    while (fgets(buf, BUFSZ, stdin) != NULL) {
        linecnt++;             /* count the records */

        /*
         * break the input into columns (data fields)
         * use INDELIM as the delimiter (see token.h)
         */
        if (token(buf, INDELIM, cols, ptable, linecnt, *argv) != 0)
            dropcnt++;          /* count the dropped rows */
        else {
            /*
             * token returned ok, print out columns the recode one at a time
             */
            for (int i = 0; i < cols; i++)
                printf("Line[%lu],Column[%d]:%s\n", linecnt, i+1, *(ptable + i))                                                                                                                              ;
       }
    }

    fprintf(stderr, "%s: %lu records input, %lu dropped\n", *argv,
            linecnt, dropcnt);
    if (dropcnt > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
