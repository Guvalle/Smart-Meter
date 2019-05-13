#include "mcp3008.h"

////////////////////////////////////////////////////////
//Funcao responsavel por inicializar os setups do conversor AD
int startMCP(int SPI_CHAN, int MY_PIN)
{
	//Chamada das setups do RaspberryPi referentes as configuracoes do mcp3008
	wiringPiSetup();
	mcp3004Setup(MY_PIN, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels
	
	
}
