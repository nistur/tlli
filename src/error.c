#include "tlli.h"

tlliReturn g_tlliError;
const char* g_tlliErrors[] = 
{
    "Success",
    "Null context",
    "No input",
    "Out of memory",
    "Parse error"
};