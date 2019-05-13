#include <unistd.h>
#include <time.h>
#include "phase.h"
#include "mcp3008.h"
#include "sampler.h"
#include "calculator.h"
#include "util.h"
#include "database.h"

#define SPI_CHAN 0
#define MY_PIN 100

int main(void)
{
	//Define a prioridade do software em relacao aos outros processos da Rpi para garantir estabilidade da amostragem
	piHiPri (99);
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	int cycle = 0;
	
	//Inicializa a variavel que armazena o instante
	long int startTime;
	long int currentTime;
	long int timeDifference;
	struct timespec gettime_now;
	
	//Chama a funcao em mcp3008.cpp que inicialia os setups do amostrados
	startMCP(SPI_CHAN, MY_PIN);
	
	Phase phaseA, phaseB, phaseC;
	
	//Declara os ponteiros que apontam para as classes Phase em phase.h
	Phase* ptrA = &phaseA;
	Phase* ptrB = &phaseB;
	Phase* ptrC = &phaseC;
	
	//Chama a funcao que conecta o software ao banco de dados para exibicao dos valores
	initSQLite();
	
	//Chama as funcoes em database.cpp que gera as tabelas de valores para a pagina
	createTablePhasors();
	createTableLinePhasors();
	createTablePowers();
	createTableWaves();
	
	//Encontra o instante inicial
	clock_gettime(CLOCK_REALTIME, &gettime_now);
	startTime = gettime_now.tv_sec;
	
	//Loop geral do medidor
	while(1)
	{
		//Zera os offsets para uma nova amostragem
		phaseA.voltageOffset = 0;
		phaseB.voltageOffset = 0;
		phaseC.voltageOffset = 0;
		
		phaseA.currentOffset = 0;
		phaseB.currentOffset = 0;
		phaseC.currentOffset = 0;
		
		//Chama a funcao em sampler.cpp que armazena as amostras do periodo das ondas		
		samplePeriod(ptrA, ptrB, ptrC, MY_PIN);
		
		//Chama a funcao em sampler.cpp que encontra a fase a ser usada como referencia
		int referenceWave = findReferenceWave(ptrA, ptrB, ptrC, MY_PIN);
		
		//Chama a funcao dentro da classe Phase que calcula os valores de offset das ondas de cada fase	
		phaseA.findOffset();
		phaseB.findOffset();
		phaseC.findOffset();
		
		printf("\n\n============================== \n");
		//DEBUG PRINT FOR TEST
		if (debug == 1){
			printf("Reference wave: %i \n \n", referenceWave);
			printf("VoltageA Offset: %i, VoltageB Offset: %i, VoltageC Offset: %i \n", phaseA.voltageOffset, phaseB.voltageOffset, phaseC.voltageOffset);
			printf("CurrentA Offset: %i, CurrentB Offset: %i, CurrentC Offset: %i \n\n", phaseA.currentOffset, phaseB.currentOffset, phaseC.currentOffset);
		}	
		sleep(0.5);
		
		if(referenceWave != -1)
		{
			if(referenceWave == 0)
			{
				//Chama a funcao em sampler.cpp que encontra o inicio do peiodo da fase de referencia
				findPeriodStart(ptrA, referenceWave, MY_PIN);
			}
			if(referenceWave == 1)
			{
				//Chama a funcao em sampler.cpp que encontra o inicio do peiodo da fase de referencia
				findPeriodStart(ptrB, referenceWave, MY_PIN);
			}
			if(referenceWave == 2)
			{
				//Chama a funcao em sampler.cpp que encontra o inicio do peiodo da fase de referencia
				findPeriodStart(ptrC, referenceWave, MY_PIN);
			}
		}
			
		//Chama a funcao em sampler.cpp que armazena as amostras do periodo das ondas
		samplePeriod(ptrA, ptrB, ptrC, MY_PIN);
		
		//DEBUG PRINT FOR TEST
		if (debug == 1){
			for(int i=0; i<phaseA.samplesPerPeriod; i++)
			{
				printf("AD sample %i: = %4d %4d %4d %4d %4d %4d\n", i, phaseA.voltageSamples[i], phaseB.voltageSamples[i], phaseC.voltageSamples[i], phaseA.currentSamples[i], phaseB.currentSamples[i], phaseC.currentSamples[i]);
			}
		}
		
		//Chama a funcao em calculator.cpp que utiliza as amostras para obter os valores das grandezas eletricas
		calculator(ptrA, ptrB, ptrC);
		
		writeTablePhasors(ptrA, ptrB, ptrC);
		writeTableLinePhasors(ptrA, ptrB, ptrC);
		writeTablePowers(ptrA, ptrB, ptrC);
		writeTableWaves(ptrA, ptrB, ptrC);
		
		clock_gettime(CLOCK_REALTIME, &gettime_now);
		currentTime = gettime_now.tv_sec;
		timeDifference = currentTime - startTime;
		
		if (debug == 1) {
			printf("Main Time difference: %i\n\n", timeDifference);
		}
		
		if (timeDifference >= 15){
			startTime = currentTime;
			findAccumulators(ptrA, ptrB, ptrC, timeDifference);
		}
		
		printf ("%i cycles of the program completed\n\n", cycle);
		cycle++;
	}
}
