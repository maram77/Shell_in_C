#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

int main(int argc, char **argv)
{
    char *cmd;

    do
    {   
        print_prompt1(); //prints the prompt's string

        cmd = read_cmd(); //reads the input

        if(!cmd)
        {
            exit(EXIT_SUCCESS); //exit the shell if there is an error reading command
        }

        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            //command is empty = ENTER, skip input and continue loop
            free(cmd);
            continue;
        }

        if(strcmp(cmd, "quit\n") == 0)
        {   //exit the shell
            free(cmd);
            break;
        }

        printf("%s\n", cmd); //print back the command

        free(cmd);

    } while(1); //Implementing the read event print loop REPL

    exit(EXIT_SUCCESS);
}

char *read_cmd(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while(fgets(buf, 1024, stdin)) //read input in chunks and store it in buf
    {
        int buflen = strlen(buf);

        if(!ptr) //creates buffer for the first chunk
        {
            ptr = malloc(buflen+1);
        }
        else //creates buffer for subsequent chunks
        {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);

            if(ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if(!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr+ptrlen, buf); //copy the chunk of input from user to buffer 

        if(buf[buflen-1] == '\n') //check if input in buffer ends with \n
        {
            if(buflen == 1 || buf[buflen-2] != '\\')
            {
                return ptr; //check if the last \n is not escaped, input is complete

            }


            //else print out PS2 and continue reading
            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_prompt2();
        }

        ptrlen += buflen;
    }

    return ptr;
}