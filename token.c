#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "token.h"

/*
 * token
 *
 * usage:   input buffer in dsv format, builds table of pointers to each field
 * args:
 *  buf     DSV data record stored in an array of characters, '\0' terminated
 *  delim   the field delimiter
 *  cnt     number of data fields that a proper data record has
 *  ptable  points at array of pointers each element points at a data field
 *  lineno  line number of this record for printing error messages
 *  argv0   name of program used when printing errors
 * returns:
 *          0 if no errors founds
 *         -1 otherwise
 */
int
token(char *buf, char delim, int cnt, char **ptable, unsigned long lineno,
            char *argv0)
{
    int colCount = 0;
    char **endptr = ptable + cnt;
    *ptable = buf;
    /* outer loop to update ptable */
    while ((ptable < endptr) && (*buf != '\0')) {
        *ptable++ = buf;
        colCount++;
        /* walk through buf */
        while (*buf != '\0') {
            /* process chars, inc buff*/
            if (*(buf) == delim || *(buf) == '\n') {
               *(buf) = '\0';
               buf++;
            }
            else if (*buf == '\"') {
                fprintf(stderr, "%s: drop line %lu, \" in unquoted field\n", argv0, lineno);
                return -1;
            }
            else {
                buf++;
            }
        }
    }
    /* check for errors */
    if (colCount > cnt) {
        fprintf(stderr, "%s: drop line %lu, too many columns\n", argv0,
                        lineno);
    }
    else if (colCount < cnt) {
        fprintf(stderr, "%s: drop line %lu, too few columns\n", argv0,
                        lineno);
    }

    return 0;
}
