#include "database.h"

////////////////////////////////////////////////////////
//Funcao responsavel por verificar o acesso do software ao arquivo do banco de dados
int initSQLite () {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;

	sqlite3 *db;
	sqlite3_stmt *res;
	
	//Diretorio do banco de dados
	int rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Found the Database\n");
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}

////////////////////////////////////////////////////////
//Funcao responsavel por inicializar as tabelas de armazenamento de valores de fase no banco de dados
int createTablePhasors () {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char const *sql;
	
	//diretorio do banco de dados
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for table creation \n");
		}
	}

	//Query que inicializa a tabela meterPhasors
	sql = "CREATE TABLE IF NOT EXISTS meterPhasors (indexi integer PRIMARY KEY, Vmagnitude TEXT, Vangle TEXT, Cmagnitude TEXT, Cangle TEXT);" ;
			
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table meterPhasors created successfully \n");
		}
	}
	
	sql = "DELETE FROM meterPhasors;" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPhasors cleared successfully \n");
			}
		}
	
	for(i = 0; i < 3; i++){
	//Query que preenche a tabela meterPhasors na inicializacao
		sql = "INSERT INTO meterPhasors (Vmagnitude, Vangle, Cmagnitude, Cangle) VALUES (0, 0, 0, 0);" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPhasors initialized successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por inicializar as tabelas de armazenamento de valores de linha no banco de dados
int createTableLinePhasors () {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char const *sql;
	
	//diretorio do banco de dados
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for table creation \n");
		}
	}

	//Query que inicializa a tabela meterPhasors
	sql = "CREATE TABLE IF NOT EXISTS meterLinePhasors (indexi integer PRIMARY KEY, Vmagnitude TEXT, Vangle TEXT);" ;
			
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table meterLinePhasors created successfully \n");
		}
	}
	
	sql = "DELETE FROM meterLinePhasors;" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterLinePhasors cleared successfully \n");
			}
		}
	
	for(i = 0; i < 3; i++){
	//Query que preenche a tabela meterPhasors na inicializacao
		sql = "INSERT INTO meterLinePhasors (Vmagnitude, Vangle) VALUES (0, 0);" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterLinePhasors initialized successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}

////////////////////////////////////////////////////////
//Funcao responsavel por inicializar as tabelas de armazenamento de valores de linha no banco de dados
int createTablePowers () {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char const *sql;
	
	//diretorio do banco de dados
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for table creation \n");
		}
	}

	//Query que inicializa a tabela meterPhasors
	sql = "CREATE TABLE IF NOT EXISTS meterPowers (indexi integer PRIMARY KEY, ApparentPower TEXT, ActivePower TEXT, ReactivePower TEXT, PowerFactor TEXT);" ;
			
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table meterPowers created successfully \n");
		}
	}
	
	sql = "DELETE FROM meterPowers;" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers cleared successfully \n");
			}
		}
	
	for(i = 0; i < 3; i++){
	//Query que preenche a tabela meterPhasors na inicializacao
		sql = "INSERT INTO meterPowers (ApparentPower, ActivePower, ReactivePower, PowerFactor) VALUES (0, 0, 0, 0);" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers initialized successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por inicializar as tabelas de armazenamento de valores de linha no banco de dados
int createTableWaves () {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char const *sql;
	
	//diretorio do banco de dados
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for table creation \n");
		}
	}

	//Query que inicializa a tabela meterPhasors
	sql = "CREATE TABLE IF NOT EXISTS meterWaveSamples (indexi integer PRIMARY KEY, SamplesVa TEXT, SamplesVb TEXT, SamplesVc TEXT, SamplesIa TEXT, SamplesIb TEXT, SamplesIc TEXT);" ;
			
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table meterPowers created successfully \n");
		}
	}
	
	sql = "DELETE FROM meterWaveSamples;" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers cleared successfully \n");
			}
		}
	
	for(i = 0; i < 50; i++){
	//Query que preenche a tabela meterPhasors na inicializacao
		sql = "INSERT INTO meterWaveSamples (SamplesVa, SamplesVb, SamplesVc, SamplesIa, SamplesIb, SamplesIc) VALUES (0, 0, 0, 0, 0, 0);" ;
		
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers initialized successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}



////////////////////////////////////////////////////////
//Funcao responsavel por atualizar a tabela meterPhasors com os valores coletados pelo medidor
int writeTablePhasors (Phase* phA, Phase* phB, Phase *phC) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[150], sql2[20], sql3[20], sql4[20], sql5[20], sql6[20];
	char VmagnitudeString[7], VangleString[7], CmagnitudeString[7], CangleString[7], indexiString[2];
	
	float phasor[12] = {phA->RMSVoltage, phA->voltage.angle, phB->RMSVoltage, phB->voltage.angle, phC->RMSVoltage, phC->voltage.angle, phA->RMSCurrent, phA->current.angle, phB->RMSCurrent, phB->current.angle, phC->RMSCurrent, phC->current.angle};
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	for (i = 0; i < 3; i++){
		
		snprintf(VmagnitudeString, sizeof(VmagnitudeString), "%.2f", phasor[i*2]);
		snprintf(VangleString, sizeof(VangleString), "%.2f", phasor[(i*2)+1]);
		snprintf(CmagnitudeString, sizeof(CmagnitudeString), "%.2f", phasor[(i*2)+6]);
		snprintf(CangleString, sizeof(CangleString), "%.2f", phasor[(i*2)+1+6]);
		snprintf(indexiString, sizeof(indexiString), "%i", i+1);

		strcpy(sql, "UPDATE meterPhasors SET Vmagnitude = ");
		strcpy(sql2, ", Vangle = ");
		strcpy(sql3, ", Cmagnitude = ");
		strcpy(sql4, ", Cangle = ");  
		strcpy(sql5, " WHERE indexi = ");
		strcpy(sql6, ";");
		
		strcat(sql, VmagnitudeString);
		strcat(sql, sql2);
		strcat(sql, VangleString);
		strcat(sql, sql3);
		strcat(sql, CmagnitudeString);
		strcat(sql, sql4);
		strcat(sql, CangleString);
		strcat(sql, sql5);
		strcat(sql, indexiString);
		strcat(sql, sql6);
		
		//if (debug == 1){
		//	printf(sql);
		//}
				
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPhasors updated successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por atualizar a tabela meterPhasors com os valores coletados pelo medidor
int writeTableLinePhasors (Phase* phA, Phase* phB, Phase *phC) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[150], sql2[20], sql3[20], sql4[20], sql5[20], sql6[20];
	char VmagnitudeString[7], VangleString[7], indexiString[2];
	
	float phasor[6] = {phA->lineVoltage.magnitude, phA->lineVoltage.angle, phB->lineVoltage.magnitude, phB->lineVoltage.angle, phC->lineVoltage.magnitude, phC->lineVoltage.angle};
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	for (i = 0; i < 3; i++){
		
		snprintf(VmagnitudeString, sizeof(VmagnitudeString), "%.2f", phasor[i*2]);
		snprintf(VangleString, sizeof(VangleString), "%.2f", phasor[(i*2)+1]);
		snprintf(indexiString, sizeof(indexiString), "%i", i+1);

		strcpy(sql, "UPDATE meterLinePhasors SET Vmagnitude = ");
		strcpy(sql2, ", Vangle = ");
		strcpy(sql3, " WHERE indexi = ");
		strcpy(sql4, ";");
		
		strcat(sql, VmagnitudeString);
		strcat(sql, sql2);
		strcat(sql, VangleString);
		strcat(sql, sql3);
		strcat(sql, indexiString);
		strcat(sql, sql4);
		
		//if (debug == 1){
		//	printf(sql);
		//}
				
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterLinePhasors updated successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por atualizar a tabela meterPhasors com os valores coletados pelo medidor
int writeTablePowers (Phase* phA, Phase* phB, Phase *phC) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[150], sql2[20], sql3[20], sql4[20], sql5[20], sql6[20];
	char ApparentPowerString[7], ActivePowerString[7], ReactivePowerString[7], PowerFactorString[7], indexiString[2];
	
	float phasor[12] = {phA->apparentPower, phA->activePower, phA->reactivePower, phA->powerFactor, phB->apparentPower, phB->activePower, phB->reactivePower, phB->powerFactor, phC->apparentPower, phC->activePower, phC->reactivePower, phC->powerFactor};
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	for (i = 0; i < 3; i++){
		
		snprintf(ApparentPowerString, sizeof(ApparentPowerString), "%.2f", phasor[i*4]);
		snprintf(ActivePowerString, sizeof(ActivePowerString), "%.2f", phasor[(i*4)+1]);
		snprintf(ReactivePowerString, sizeof(ReactivePowerString), "%.2f", phasor[(i*4)+2]);
		snprintf(PowerFactorString, sizeof(PowerFactorString), "%.2f", phasor[(i*4)+3]);
		snprintf(indexiString, sizeof(indexiString), "%i", i+1);

		strcpy(sql, "UPDATE meterPowers SET ApparentPower = ");
		strcpy(sql2, ", ActivePower = ");
		strcpy(sql3, ", ReactivePower = ");
		strcpy(sql4, ", PowerFactor = ");  
		strcpy(sql5, " WHERE indexi = ");
		strcpy(sql6, ";");
		
		strcat(sql, ApparentPowerString);
		strcat(sql, sql2);
		strcat(sql, ActivePowerString);
		strcat(sql, sql3);
		strcat(sql, ReactivePowerString);
		strcat(sql, sql4);
		strcat(sql, PowerFactorString);
		strcat(sql, sql5);
		strcat(sql, indexiString);
		strcat(sql, sql6);
		
		//if (debug == 1){
		//	printf(sql);
		//}
				
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers updated successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por atualizar a tabela meterPhasors com os valores coletados pelo medidor
int writeTableWaves (Phase* phA, Phase* phB, Phase *phC) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[200], sql2[20], sql3[20], sql4[20], sql5[20], sql6[20], sql7[20], sql8[20];
	char SampleVAString[10], SampleVBString[10], SampleVCString[10], SampleIAString[10], SampleIBString[10], SampleICString[10], indexiString[3];
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	for (i = 0; i < 50; i++){
		
		snprintf(SampleVAString, sizeof(SampleVAString), "%.2f", (phA->voltageSamples[i] * phA->voltageConversion));
		snprintf(SampleVBString, sizeof(SampleVBString), "%.2f", (phB->voltageSamples[i] * phB->voltageConversion));
		snprintf(SampleVCString, sizeof(SampleVCString), "%.2f", (phC->voltageSamples[i] * phC->voltageConversion));
		snprintf(SampleIAString, sizeof(SampleIAString), "%.2f", (phA->currentSamples[i] * phA->currentConversion));
		snprintf(SampleIBString, sizeof(SampleIBString), "%.2f", (phB->currentSamples[i] * phB->currentConversion));
		snprintf(SampleICString, sizeof(SampleICString), "%.2f", (phC->currentSamples[i] * phC->currentConversion));
		
		snprintf(indexiString, sizeof(indexiString), "%i", i+1);

		strcpy(sql, "UPDATE meterWaveSamples SET SamplesVA = ");
		strcpy(sql2, ", SamplesVB = ");
		strcpy(sql3, ", SamplesVC = ");
		strcpy(sql4, ", SamplesIA = ");
		strcpy(sql5, ", SamplesIB = ");
		strcpy(sql6, ", SamplesIC = ");  
		strcpy(sql7, " WHERE indexi = ");
		strcpy(sql8, ";");
		
		strcat(sql, SampleVAString);
		strcat(sql, sql2);
		strcat(sql, SampleVBString);
		strcat(sql, sql3);
		strcat(sql, SampleVCString);
		strcat(sql, sql4);
		strcat(sql, SampleIAString);
		strcat(sql, sql5);
		strcat(sql, SampleIBString);
		strcat(sql, sql6);
		strcat(sql, SampleICString);
		strcat(sql, sql7);
		strcat(sql, indexiString);
		strcat(sql, sql8);
		
		//if (debug == 1){
		//	printf(sql);
		//}
				
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		
		if (debug == 1){
			if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
			}
			else{
					fprintf(stdout, "Table meterPowers updated successfully \n");
			}
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por ler os valores de energia da tabela Accumulators
int readTableAccumulators (threeP* triPhase) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[150];
	
	//Limpa os ponteiros
	triPhase->eneApp = 0;
	triPhase->eneAct = 0;
	triPhase->eneReact = 0;
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	strcpy(sql, "SELECT eneApp, eneAct, eneReact FROM Accumulators;");	
	rc = sqlite3_exec(db, sql, callbackE, triPhase, &zErrMsg);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table Accumulators read successfully \n");
				fprintf(stdout, "eneApp = %f \n", triPhase->eneApp);
				fprintf(stdout, "eneAct = %f \n", triPhase->eneAct);
				fprintf(stdout, "eneReact = %f \n", triPhase->eneReact);
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
//Funcao responsavel por escrever os valores de energia na tabela Accumulators
int writeTableAccumulators (threeP* triPhase) {
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	int i = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[150], sql2[20], sql3[20], sql4[20];
	char EneAppString[7], EneActString[7], EneReactString[7];	
	
	rc = sqlite3_open("../../../var/www/html/phpsqliteconnect/db/meterDB.db", &db);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
				sqlite3_close(db);
		}
		else{
				printf("Database is opened for writing \n");
		}
	}

	snprintf(EneAppString, sizeof(EneAppString), "%.2f", triPhase->eneApp);
	snprintf(EneActString, sizeof(EneActString), "%.2f", triPhase->eneAct);
	snprintf(EneReactString, sizeof(EneReactString), "%.2f", triPhase->eneReact);
	
	strcpy(sql, "UPDATE Accumulators SET eneApp = ");
	strcpy(sql2, ", eneAct = ");
	strcpy(sql3, ", eneReact = ");
	strcpy(sql4, " WHERE indexi = 1 ;");
	
	strcat(sql, EneAppString);
	strcat(sql, sql2);
	strcat(sql, EneActString);
	strcat(sql, sql3);
	strcat(sql, EneReactString);
	strcat(sql, sql4);
	
	if (debug == 1){
		if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
		}
		else{
				fprintf(stdout, "Table Accumulators updated successfully \n");
		}
	}
	
	sqlite3_close(db);
		
	return 0;
}


////////////////////////////////////////////////////////
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	
	int i;
	
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	
	return 0;
}

////////////////////////////////////////////////////////
static int callbackE(void *veryUsed, int argc, char **argv, char **azColName) {
	
	int i;
	threeP *triPhase = (threeP *)veryUsed;
	
	for (i = 0; i<argc; i++) {
		triPhase->eneApp = atof(argv[0]);
		triPhase->eneAct = atof(argv[1]);
		triPhase->eneReact = atof(argv[2]);
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	
	return 0;
}
