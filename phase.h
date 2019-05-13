#ifndef PHASE
#define PHASE
#include <math.h>

//Declaracao da classe Phase que contem todas as propriedades de uma fase
class Phase{
	public:
	
	int samplesPerPeriod = 50;
	
	//int midVolt = 435;
	//int midCurr = 512;
	int voltageOffset, currentOffset;
	int voltageAbs, currentAbs;
	
	float innerTP = 220/3;
	float innerTC = 10;
	float voltageConversion = innerTP * 0.0048828125 * 2.4; //2.5 é referente ao divisor de tensão no secundário dos trafos 512 está para 3 como 360(pico) está para 2.4 ish
	float currentConversion = innerTC * 0.0048828125;
	
	int voltageSamples[50];
	int currentSamples[50];
	
	class Peak{
		public:

		int value;
		int time;
	} voltagePeakPos, voltagePeakNeg, voltagePeak, currentPeakPos, currentPeakNeg, currentPeak;
	
	class Phasor{
		public:
		
		float magnitude;
		float angle;
	} lineVoltage, voltage, current;
	
	float RMSVoltage, RMSCurrent;
	float activePower, reactivePower, apparentPower;
	float powerFactor;
	float harmonics[15];
	
	void findPeak(){
		
		int sample = 0;
		
		voltagePeakPos.value = 0;
		voltagePeakNeg.value = 0;
		currentPeakPos.value = 0;
		currentPeakNeg.value = 0;
		
		for(sample = 0; sample < samplesPerPeriod; sample++)
		{
			if(*(voltageSamples + sample) > voltagePeakPos.value)
			{
				voltagePeakPos.value = *(voltageSamples + sample);
				voltagePeakPos.time = sample;
			} else if (voltagePeakNeg.value == 0) {voltagePeakNeg.value = voltagePeakPos.value; voltagePeakNeg.time = sample; } 
						
			if(*(voltageSamples + sample) < voltagePeakNeg.value)
			{
				voltagePeakNeg.value = *(voltageSamples + sample);
				voltagePeakNeg.time = sample;
			} else if (voltagePeakPos.value == 0) {voltagePeakPos.value = voltagePeakNeg.value; voltagePeakPos.time = sample; }
			
			if(*(currentSamples + sample) > currentPeakPos.value)
			{
				currentPeakPos.value = *(currentSamples + sample);
				currentPeakPos.time = sample;
			} else if (currentPeakNeg.value == 0) {currentPeakNeg.value = currentPeakPos.value; currentPeakNeg.time = sample; }
			
			if(*(currentSamples + sample) < currentPeakNeg.value)
			{
				currentPeakNeg.value = *(currentSamples + sample);
				currentPeakNeg.time = sample;
			} else if (currentPeakPos.value == 0) {currentPeakPos.value = currentPeakNeg.value; currentPeakPos.time = sample; }
			
		}
		
		voltagePeak.value = (voltagePeakPos.value - voltagePeakNeg.value)/2;
		currentPeak.value = (currentPeakPos.value - currentPeakNeg.value)/2;

		if (abs(voltagePeakPos.value) >= abs(voltagePeakNeg.value)) {voltageAbs = voltagePeakPos.value;}
		else {voltageAbs = voltagePeakNeg.value;}
		
		if (abs(currentPeakPos.value) >= abs(currentPeakNeg.value)) {currentAbs = currentPeakPos.value;}
		else {currentAbs = currentPeakNeg.value;}
		
	}
	
	void findOffset(){
	
		voltageOffset = (voltagePeakPos.value + voltagePeakNeg.value)/2;
		currentOffset = (currentPeakPos.value + currentPeakNeg.value)/2;
		
	}
	
	void findPhasor(){

		voltage.magnitude = (abs(voltagePeak.value) * voltageConversion);
		if (voltage.magnitude < 5) { voltage.magnitude = 0; }
		
		if (abs(voltagePeak.value) > 3){ //Maior que 3 para dar uma margem
			if(voltageSamples[0] > 0 && voltageSamples[0] < voltagePeakPos.value){	
				if(voltagePeakPos.time < voltagePeakNeg.time){ voltage.angle = (asin(((float)voltageSamples[0]) / (float)abs(voltageAbs)) * (180/3.1415)); }
				if(voltagePeakNeg.time < voltagePeakPos.time){ voltage.angle = (180 - (asin(((float)voltageSamples[0]) / (float)abs(voltageAbs)) * (180/3.1415))); }				
			}
			if(voltageSamples[0] < 0 && voltageSamples[0] > voltagePeakNeg.value){	
				if(voltagePeakPos.time < voltagePeakNeg.time){ voltage.angle = (asin(((float)voltageSamples[0]) / (float)abs(voltageAbs)) * (180/3.1415)); }
				if(voltagePeakNeg.time < voltagePeakPos.time){ voltage.angle = (180 - (asin(((float)voltageSamples[0]) / (float)abs(voltageAbs)) * (180/3.1415))); }				
			}
			if(voltageSamples[0] == 0) {
				if(voltagePeakPos.time < voltagePeakNeg.time){ voltage.angle = 0; }
				if(voltagePeakNeg.time < voltagePeakPos.time){ voltage.angle = 180; }				
			}
			if(voltageSamples[0] == voltagePeakPos.value) { voltage.angle = 90; }
			if(voltageSamples[0] == voltagePeakNeg.value) { voltage.angle = 270; }
		}
		else voltage.angle = 0;
		
		current.magnitude = (abs(currentPeak.value) * currentConversion);
		if (current.magnitude < 0.1) { current.magnitude = 0; }
		
		if (abs(currentPeak.value) > 3){ //Maior que 3 para dar uma margem
			if(currentSamples[0] > 0 && currentSamples[0] < currentPeakPos.value){	
				if(currentPeakPos.time < currentPeakNeg.time){ current.angle = (asin(((float)currentSamples[0]) / (float)abs(currentAbs)) * (180/3.1415)); }
				if(currentPeakNeg.time < currentPeakPos.time){ current.angle = (180 - (asin(((float)currentSamples[0]) / (float)abs(currentAbs)) * (180/3.1415))); }				
			}
			if(currentSamples[0] < 0 && currentSamples[0] > currentPeakNeg.value){	
				if(currentPeakPos.time < currentPeakNeg.time){ current.angle = (asin(((float)currentSamples[0]) / (float)abs(currentAbs)) * (180/3.1415)); }
				if(currentPeakNeg.time < currentPeakPos.time){ current.angle = (180 - (asin(((float)currentSamples[0]) / (float)abs(currentAbs)) * (180/3.1415))); }				
			}
			if(currentSamples[0] == 0) {
				if(currentPeakPos.time < currentPeakNeg.time){ current.angle = 0; }
				if(currentPeakNeg.time < currentPeakPos.time){ current.angle = 180; }				
			}
			if(currentSamples[0] == currentPeakPos.value) { current.angle = 90; }
			if(currentSamples[0] == currentPeakNeg.value) { current.angle = 270; }
		}
		else current.angle = 0;
	}
	
	void findRMS(){
		
		RMSVoltage = voltage.magnitude/sqrt(2);
		RMSCurrent = current.magnitude/sqrt(2);
		
	}
	
	void findPowers(){
		
		apparentPower = RMSVoltage * RMSCurrent;
		activePower = apparentPower * powerFactor;
		reactivePower = apparentPower * sin(acos(powerFactor));
		
	}
	
	void findPowerFactor(){
	
		powerFactor = cos(voltage.angle - current.angle);
		
	}
	
};

struct threeP {
	float eneApp = 0;
	float eneAct = 0;
	float eneReact = 0;
};

#endif
