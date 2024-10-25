#include "Includes.h"


unsigned char count_push_button = 1; 

void interrupt ISR(void)
{
	if(INTF)  //If External Edge INT Interrupt
	{
		count_push_button++;  // Incrementa o contador a cada pressão do botão
        if (count_push_button > 5) {
            count_push_button = 1;  // Reseta para 1 Hz se passar de 5 Hz
        }
        INTF = 0;  // Limpa a flag de interrupção
	}
}