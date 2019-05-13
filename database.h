#ifndef DATABASE
#define DATABASE
#include <wiringPi.h>
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "phase.h"

int initSQLite();
int createTablePhasors();
int createTableLinePhasors();
int createTablePowers();
int createTableWaves();
int writeTablePhasors(Phase*, Phase*, Phase*);
int writeTableLinePhasors(Phase*, Phase*, Phase*);
int writeTablePowers(Phase*, Phase*, Phase*);
int writeTableWaves (Phase*, Phase*, Phase*);
int readTableAccumulators (threeP*);
int writeTableAccumulators (threeP*);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
static int callbackE(void *NotUsed, int argc, char **argv, char **azColName);

#endif
