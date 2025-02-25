
#ifndef TOKEN_H
#define TOKEN_H
/*
 * Constants (some are for testing only)
 */
#define MINCOL  2       /* min number of columns */
#define MAXCOL  50      /* max number of columns */
#define BUFSZ   8192    /* input buffer size limit */
#define INDELIM ','     /* input column delimiter */

 /*
  * Function prototypes
  */
int token(char *, char, int, char **, unsigned long, char *);
#endif
