#include "handleRequest.h"

int match(char * string, char * pattern)
{
    int result;
    regex_t reg;

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    result = regexec(&reg, string, (size_t) 0, NULL, 0);                         
    regfree(&reg);                                                               
    if (result != 0) {                                                         
        return(0);                                                              
    }
    return(1);        
}        