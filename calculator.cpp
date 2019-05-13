#include "calculator.h"
#include "util.h"

int calculator(Phase* phA, Phase* phB, Phase*phC)
{
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;	
		
	clearPointers(phA, phB, phC);
	
	//Chama a funcao dentro da classe Phase que calcula os valores e instantes de pico das ondas de cada fase	
	phA->findPeak();
	phB->findPeak();
	phC->findPeak();
	
	//Chama a funcao dentro da classe Phase que calcula os valores dos fasores de cada fase
	phA->findPhasor();
	phB->findPhasor();
	phC->findPhasor();
	
	//Chama a funcao dentro da classe Phase que calcula os valores RMS de cada fase
	phA->findRMS();
	phB->findRMS();
	phC->findRMS();
	
	//Chama a funcao dentro da classe Phase que calcula o fator de potência de cada fase
	phA->findPowerFactor();
	phB->findPowerFactor();
	phC->findPowerFactor();
	
	//Chama a funcao dentro da classe Phase que calcula os valores das potências de cada fase
	phA->findPowers();
	phB->findPowers();
	phC->findPowers();
	
	//Calcula os valores RMS das linhas
	float retVa[2], retVb[2], retVc[2];
	float retVAB[2], retVBC[2], retVCA[2];
	
	retVa[0] = phA->voltage.magnitude * cos((phA->voltage.angle)*(3.1415 / 180));
	retVa[1] = phA->voltage.magnitude * sin((phA->voltage.angle)*(3.1415 / 180));
	retVb[0] = phB->voltage.magnitude * cos((phB->voltage.angle)*(3.1415 / 180));
	retVb[1] = phB->voltage.magnitude * sin((phB->voltage.angle)*(3.1415 / 180));
	retVc[0] = phC->voltage.magnitude * cos((phC->voltage.angle)*(3.1415 / 180));
	retVc[1] = phC->voltage.magnitude * sin((phC->voltage.angle)*(3.1415 / 180));
	
	retVAB[0] = retVa[0] - retVb[0];
	retVAB[1] = retVa[1] - retVb[1];
	retVBC[0] = retVb[0] - retVc[0];
	retVBC[1] = retVb[1] - retVc[1];
	retVCA[0] = retVc[0] - retVa[0];
	retVCA[1] = retVc[1] - retVa[1];
	
	phA->lineVoltage.magnitude = sqrt(pow(retVAB[0], 2) + pow(retVAB[1], 2))/sqrt(2);
	phA->lineVoltage.angle = (atan2(retVAB[1], retVAB[0])*(180 / 3.1415));
	phB->lineVoltage.magnitude = sqrt(pow(retVBC[0], 2) + pow(retVBC[1], 2))/sqrt(2);
	phB->lineVoltage.angle = (atan2(retVBC[1], retVBC[0])*(180 / 3.1415));
	phC->lineVoltage.magnitude = sqrt(pow(retVCA[0], 2) + pow(retVCA[1], 2))/sqrt(2);
	phC->lineVoltage.angle = (atan2(retVCA[1], retVCA[0])*(180 / 3.1415));
	////////////////////////////
		
	if (debug == 1){
		
		printf("\nThe Positive peak value for V1 is: %i at sample %i \n", phA->voltagePeakPos.value, phA->voltagePeakPos.time);
		printf("The Positive peak value for V2 is: %i at sample %i \n", phB->voltagePeakPos.value, phB->voltagePeakPos.time);
		printf("The Positive peak value for V3 is: %i at sample %i \n", phC->voltagePeakPos.value, phC->voltagePeakPos.time);
		
		printf("\nThe Negative peak value for V1 is: %i at sample %i \n", phA->voltagePeakNeg.value, phA->voltagePeakNeg.time);
		printf("The Negative peak value for V2 is: %i at sample %i \n", phB->voltagePeakNeg.value, phB->voltagePeakNeg.time);
		printf("The Negative peak value for V3 is: %i at sample %i \n", phC->voltagePeakNeg.value, phC->voltagePeakNeg.time);
		
		printf("\nThe ABS peak value for V1 is: %i \n", phA->voltageAbs);
		printf("The ABS peak value for V2 is: %i \n", phB->voltageAbs);
		printf("The ABS peak value for V3 is: %i \n", phC->voltageAbs);
		
		printf("\nThe Positive peak value for C1 is: %i at sample %i \n", phA->currentPeakPos.value, phA->currentPeakPos.time);
		printf("The Positive peak value for C2 is: %i at sample %i \n", phB->currentPeakPos.value, phB->currentPeakPos.time);
		printf("The Positive peak value for C3 is: %i at sample %i \n", phC->currentPeakPos.value, phC->currentPeakPos.time);
		
		printf("\nThe Negative peak value for C1 is: %i at sample %i \n", phA->currentPeakNeg.value, phA->currentPeakNeg.time);
		printf("The Negative peak value for C2 is: %i at sample %i \n", phB->currentPeakNeg.value, phB->currentPeakNeg.time);
		printf("The Negative peak value for C3 is: %i at sample %i \n", phC->currentPeakNeg.value, phC->currentPeakNeg.time);
		
		printf("\nThe first sample for V1 is: %i \n", phA->voltageSamples[0]);
		printf("The first sample for V2 is: %i \n", phB->voltageSamples[0]);
		printf("The first sample for V3 is: %i \n\n", phC->voltageSamples[0]);
		
		printf("Phasor 1 is: \n V %.2f, %.2fº \n C %.2f, %.2fº \n\n", phA->voltage.magnitude, phA->voltage.angle, phA->current.magnitude, phA->current.angle);
		printf("Phasor 2 is: \n V %.2f, %.2fº \n C %.2f, %.2fº \n\n", phB->voltage.magnitude, phB->voltage.angle, phB->current.magnitude, phB->current.angle);
		printf("Phasor 3 is: \n V %.2f, %.2fº \n C %.2f, %.2fº \n\n", phC->voltage.magnitude, phC->voltage.angle, phC->current.magnitude, phC->current.angle);
		
		printf("Vrms 1 is: %.2f;  Crms 1 is: %.2f \n", phA->RMSVoltage, phA->RMSCurrent);
		printf("Vrms 2 is: %.2f;  Crms 2 is: %.2f \n", phB->RMSVoltage, phB->RMSCurrent);
		printf("Vrms 3 is: %.2f;  Crms 3 is: %.2f \n\n", phC->RMSVoltage, phC->RMSCurrent);
		
		printf("Vrms 12 is: %.2f, %.2f; \n", phA->lineVoltage.magnitude, phA->lineVoltage.angle);
		printf("Vrms 23 is: %.2f, %.2f; \n", phB->lineVoltage.magnitude, phB->lineVoltage.angle);
		printf("Vrms 31 is: %.2f, %.2f; \n\n", phC->lineVoltage.magnitude, phC->lineVoltage.angle);
			
		printf("Apparent Power 1 is: %.2f;  Active Power 1 is: %.2f;  Reactive Power 1 is: %.2f \n", phA->apparentPower, phA->activePower, phA->reactivePower);
		printf("Apparent Power 2 is: %.2f;  Active Power 2 is: %.2f;  Reactive Power 2 is: %.2f \n", phB->apparentPower, phB->activePower, phB->reactivePower);
		printf("Apparent Power 3 is: %.2f;  Active Power 3 is: %.2f;  Reactive Power 3 is: %.2f \n\n", phC->apparentPower, phC->activePower, phC->reactivePower);
		
		printf("Power Factor 1 is: %.2f \n", phA->powerFactor);
		printf("Power Factor 2 is: %.2f \n", phB->powerFactor);
		printf("Power Factor 3 is: %.2f \n\n", phC->powerFactor);
		
	}
	
	return 0;
}

int findAccumulators(Phase* phA, Phase* phB, Phase* phC, long int timeDiff){
	
	//Seta o modo debug quando houver uma funcao disponivel
	int debug = 0;
	
	threeP triphasic;
	
	threeP* ptrTriphasic = &triphasic;
	
	float ApparentPower3P;
	float ActivePower3P;
	float ReactivePower3P;
	
	readTableAccumulators(ptrTriphasic);
	
	if (debug == 1){

		fprintf(stdout, "Table Accumulators read successfully \n");
		fprintf(stdout, "eneApp = %f \n", triphasic.eneApp);
		fprintf(stdout, "eneAct = %f \n", triphasic.eneAct);
		fprintf(stdout, "eneReact = %f \n", triphasic.eneReact);
		
	}
	
	ApparentPower3P = (phA->apparentPower + phB->apparentPower + phC->apparentPower);
	ActivePower3P = (phA->activePower + phB->activePower + phC->activePower);
	ReactivePower3P = (phA->reactivePower + phB->reactivePower + phC->reactivePower);
	
	triphasic.eneApp = (triphasic.eneApp + (ApparentPower3P/(60 * (60/timeDiff))));
	triphasic.eneAct = (triphasic.eneAct + (ActivePower3P/(60 * (60/timeDiff))));
	triphasic.eneReact = (triphasic.eneReact + (ReactivePower3P/(60 * (60/timeDiff))));
	
	writeTableAccumulators(ptrTriphasic);
	
	return 0;
}
