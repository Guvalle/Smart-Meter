#include "util.h"

int clearPointers(Phase* phA, Phase* phB, Phase* phC)
{
	
	phA->voltagePeak.value = 0;
	phB->voltagePeak.value = 0;
	phC->voltagePeak.value = 0;
	phA->currentPeak.value = 0;
	phB->currentPeak.value = 0;
	phC->currentPeak.value = 0;
	
	phA->voltagePeakPos.value = 0;
	phB->voltagePeakPos.value = 0;
	phC->voltagePeakPos.value = 0;
	phA->currentPeakPos.value = 0;
	phB->currentPeakPos.value = 0;
	phC->currentPeakPos.value = 0;
	
	phA->voltagePeakNeg.value = 0;
	phB->voltagePeakNeg.value = 0;
	phC->voltagePeakNeg.value = 0;
	phA->currentPeakNeg.value = 0;
	phB->currentPeakNeg.value = 0;
	phC->currentPeakNeg.value = 0;
	
	phA->voltagePeak.time = 0;
	phB->voltagePeak.time = 0;
	phC->voltagePeak.time = 0;
	phA->currentPeak.time = 0;
	phB->currentPeak.time = 0;
	phC->currentPeak.time = 0;
	
	phA->voltageOffset = 0;
	phB->voltageOffset = 0;
	phC->voltageOffset = 0;
	
	phA->currentOffset = 0;
	phB->currentOffset = 0;
	phC->currentOffset = 0;
	
	phA->voltageAbs = 0;
	phB->voltageAbs = 0;
	phC->voltageAbs = 0;
	
	phA->currentAbs = 0;
	phB->currentAbs = 0;
	phC->currentAbs = 0;
	
	phA->RMSVoltage = 0;
	phB->RMSVoltage = 0;
	phC->RMSVoltage = 0;
	
	phA->RMSCurrent = 0;
	phB->RMSCurrent = 0;
	phC->RMSCurrent = 0;
	
	phA->apparentPower = 0;
	phA->activePower = 0;
	phA->reactivePower = 0;
	
	phB->apparentPower = 0;
	phB->activePower = 0;
	phB->reactivePower = 0;
	
	phC->apparentPower = 0;
	phC->activePower = 0;
	phC->reactivePower = 0;
	
	phA->powerFactor = 0;
	phB->powerFactor = 0;
	phC->powerFactor = 0;
	
	return 0;
}
