#include <stdio.h>
#include "shell.h"

void print_prompt1(void)
{   //creates a file and writes content to it, PS1
    // standard error, default file where process can write error message
    fprintf(stderr, "$ ");
}

void print_prompt2(void)
    // printed when the user enters a multiline command, PS2
{
    fprintf(stderr, "> ");
}

 