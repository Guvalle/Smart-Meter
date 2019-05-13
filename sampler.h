#ifndef SAMPLER
#define SAMPLER
#include <wiringPi.h>
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "phase.h"
#include "util.h"

int findReferenceWave(Phase*, Phase*, Phase*, int);
int findPeriodStart(Phase*, int, int);
int samplePeriod(Phase*, Phase*, Phase*,int);

#endif
