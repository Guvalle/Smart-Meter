#include "sampler.h"

////////////////////////////////////////////////////////
//Funcao responsavel por identficar a fase de referencia
int findReferenceWave(Phase* phA, Phase* phB, Phase* phC, int MY_PIN)
{
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;

	//variaveis para incrementacao de listas
	int index = 0; //0=A 1=B 2=C 
	
	clearPointers(phA, phB, phC);
	
	phA->findPeak();
	phB->findPeak();
	phC->findPeak();

	if (debug == 1){
		printf("%i\n\n %i\n\n %i\n\n", phA->voltagePeak.value, phB->voltagePeak.value, phC->voltagePeak.value);
	}
	
	if(abs(phA->voltagePeak.value) > 100)
	{
		index = 0;
		return index;
	}
	else if(abs(phB->voltagePeak.value) > 100)
	{
		index = 1;
		return index;
	}
	else if(abs(phC->voltagePeak.value) > 100)
	{
		index = 2;
		return index;
	}
	else
	{ 
		index = -1;
		return index;
	}
}


////////////////////////////////////////////////////////
//Funcao responsavel por identficar o inicio do periodo
int findPeriodStart(Phase* phase, int referenceWave, int MY_PIN)
{
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	int count = 0;

	//variaveis para incrementacao de listas
	int flag = 1;
	int index = referenceWave;
	
	int value1, value2;
	
	//Loop que realiza a leitua das amostras e armazena nos arrays
	while(flag == 1)
	{
		value1 = analogRead(MY_PIN + index);
		sleep(0.0005);
		value2 = analogRead(MY_PIN + index);
		
		if(((((value2 - phase->voltageOffset) * (value1 - phase->voltageOffset)) < 0) && (((value2 - phase->voltageOffset) + (value1 - phase->voltageOffset)) < (value2 - phase->voltageOffset))) || count > 10000)
		{
			flag = 0;
		}
		count++;
	}
	
	return 1;
}	


////////////////////////////////////////////////////////
//Funcao responsavel pela amostragem das formas de onda
int samplePeriod(Phase* phA, Phase* phB, Phase* phC, int MY_PIN)
{
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;	
	int simulation = 0;

	//variaveis para incrementacao de listas
	int index = 0; 
	int sample = 0;
	int waveIndex = 0;
	
	//lista para buffer dos valores dos canais do conversor AD
	int ADCRead[6];
	
	//Loop que realiza a leitua das amostras e armazena nos arrays
	if (simulation == 1){	
		
		for(sample = 0; sample < phA->samplesPerPeriod; sample++)
		{
			
			*(phA->voltageSamples + sample) = (512 + (360 * sin((((2 * 3.1415) / (50)) * sample) + ((0 * 3.1415)/1)))) - phA->voltageOffset;
			*(phB->voltageSamples + sample) = (512 + (360 * sin((((2 * 3.1415) / (50)) * sample) - ((2 * 3.1415)/3)))) - phB->voltageOffset;
			*(phC->voltageSamples + sample) = (512 + (360 * sin((((2 * 3.1415) / (50)) * sample) + ((2 * 3.1415)/3)))) - phC->voltageOffset;
			*(phA->currentSamples + sample) = (512 + (128 * sin((((2 * 3.1415) / (50)) * sample) + ((2 * 3.1415)/8)))) - phA->currentOffset;
			*(phB->currentSamples + sample) = (512 + (128 * sin((((2 * 3.1415) / (50)) * sample) + ((7 * 3.1415)/8)))) - phB->currentOffset;
			*(phC->currentSamples + sample) = (512 + (128 * sin((((2 * 3.1415) / (50)) * sample) + ((12 * 3.1415)/3)))) - phC->currentOffset;
			
		}		
	}
	
	else {
		for(sample = 0; sample < phA->samplesPerPeriod; sample++)
		{
			for (index=0; index<6; index++)
			{
				ADCRead[index] = analogRead(MY_PIN + index);
			}
			*(phA->voltageSamples + sample) = ADCRead[0] - phA->voltageOffset;
			*(phB->voltageSamples + sample) = ADCRead[1] - phB->voltageOffset;
			*(phC->voltageSamples + sample) = ADCRead[2] - phC->voltageOffset;
			*(phA->currentSamples + sample) = ADCRead[3] - phA->currentOffset;
			*(phB->currentSamples + sample) = ADCRead[4] - phB->currentOffset;
			*(phC->currentSamples + sample) = ADCRead[5] - phC->currentOffset;
		}
	}
			
	return 0;
}
