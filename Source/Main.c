#include <pic.h>  // Inclui o arquivo para o compilador HI-TECH C

#define _XTAL_FREQ 4000000  // Define a frequ�ncia do cristal para 4 MHz

unsigned char count_push_button = 1; // Contador para a frequ�ncia do LED

// Fun��o de interrup��o
void interrupt ISR(void) {
    if (INTF)  // Se a interrup��o externa (INT) ocorrer
    {
        count_push_button++;  // Incrementa o contador a cada press�o do bot�o
        if (count_push_button > 5) {
            count_push_button = 1;  // Reseta para 1 Hz se passar de 5 Hz
        }
        INTF = 0;  // Limpa a flag de interrup��o
    }
}

// Fun��o para configurar os pinos
void setup() {
    TRISDbits.TRISD0 = 0; // Configura RD0 como sa�da (LED)
    TRISBbits.TRISB0 = 1; // Configura RB0 como entrada (bot�o)
    PORTDbits.RD0 = 0; // Inicializa o LED desligado
    
    // Configura��o da interrup��o externa
    INTE = 1;   // Habilita a interrup��o externa (INT)
    INTF = 0;   // Limpa a flag de interrup��o externa
    GIE = 1;    // Habilita interrup��es globais
    OPTION_REGbits.INTEDG = 1;  // Interrup��o na borda de subida
}

// Fun��o para gerar o atraso vari�vel (em ms)
void delay_ms_variable(unsigned int delay) {
    while(delay--) {
        __delay_ms(1);  // Atraso de 1 ms
    }
}

void main() {
    setup();  // Configura��o inicial

    unsigned int delay_time = 1000;  // Tempo de atraso inicial para 1 Hz

    while (1) {
        PORTDbits.RD0 = 1;  // Liga o LED
        delay_ms_variable(delay_time / 2);  // Atraso baseado na frequ�ncia
        PORTDbits.RD0 = 0;  // Desliga o LED
        delay_ms_variable(delay_time / 2);  // Atraso baseado na frequ�ncia
        
        // Ajuste do tempo de atraso de acordo com o contador
        switch(count_push_button) {
            case 1: delay_time = 1000; break;  // 1 Hz
            case 2: delay_time = 500; break;   // 2 Hz
            case 3: delay_time = 333; break;   // 3 Hz
            case 4: delay_time = 250; break;   // 4 Hz
            case 5: delay_time = 200; break;   // 5 Hz
        }
    }
}
