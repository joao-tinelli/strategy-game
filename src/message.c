#include "libraries.h"

void msg_error(char *S, char *function)
{
    fprintf(stderr, "Error in: '%s'.\n", function);
    fprintf(stderr, "Message: '%s'\n", S);
}

