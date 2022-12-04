#include <errno.h>
#include "shell.h"
#include "source.h"

void unget_char(struct source_s *src)
{
    
     /* returns (or ungets) the last character we've retrieved from input*/
    if(src->curpos < 0)
    {
        return;
    }

    src->curpos--;
}


char next_char(struct source_s *src)

/* returns the next character of input and updates the source pointer*/
{
    if(!src || !src->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }

    char c1 = 0;
    if(src->curpos == INIT_SRC_POS) /* -2 but whyy */
    {
        src->curpos  = -1; /* whyy */
    }
    else
    {
        c1 = src->buffer[src->curpos]; /* getting the char et curspos */
    }

    if(++src->curpos >= src->bufsize) /* incrementing to get next char */
    {
        src->curpos = src->bufsize; /* if curspos exceeded the input size, we put it at the last char*/
        return EOF;
    }

    return src->buffer[src->curpos];
}


char peek_char(struct source_s *src)
/* checks the nextchar without retrieving it and updationg pointers*/
{
    if(!src || !src->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }

    long pos = src->curpos;

    if(pos == INIT_SRC_POS)
    {
        pos++;
    }
    pos++;

    if(pos >= src->bufsize)
    {
        return EOF;
    }

    return src->buffer[pos];
}


void skip_white_spaces(struct source_s *src)
{
    char c;

    if(!src || !src->buffer)
    {
        return;
    }

    while(((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
    {
        next_char(src);
    }
}