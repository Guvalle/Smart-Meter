#ifndef CALCULATOR
#define CALCULATOR
#include <wiringPi.h>
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phase.h"
#include "database.h"

int calculator(Phase*, Phase*, Phase*);
int findAccumulators(Phase*, Phase*, Phase*, long int);


#endif
