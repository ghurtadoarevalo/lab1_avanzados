#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "struct.h"

char** readData(char* fp_source_name_1);
investments ** powerSet(investment ** set, int set_size);
investments * bestCase(investments ** investmentCombinations, int set_size, int budget);
investment ** readInvestments ();



#endif
