#include <avr/io.h>



void kirjaimen_lahetys(char c){
    while(!(UCSR0A & (1<<UDRE0))) //ei tee mitään niin kauan kun transmit bufferissa on dataa
    ;
    UDR0 = c; //laitta bufferiin lisää dataa
}



int main(void){
    UCSR0B |= (1 << TXEN0); // Avaa kommunikaation usb tietokoneen ja sirun vlillä
    UBRR0 = 103; // asettaa taajuuden noin 9600 jolla laitteet puhuvat keskenään


    TCCR1B |= (1 << CS12) | (1 << CS10); // Asettaa rekisterin 101 --> TCNT1 menee nyt tasan sekunti nousta 15625 asti
    
    //Integroitu ledi ja pin 53 output ja päälle
    DDRB |= (1 << PORTB7);
    DDRB |= (1 << PORTB0);
    PORTB |= (1 << PORTB7);
    PORTB |= (1 << PORTB0);

    while(1){
        if(TCNT1 >= 31250){
            TCNT1 = 0;
            if(!(PORTB & (1 << PORTB7)) && !(PORTB & (1 << PORTB0))){ // tarkistaa ledien tilanteen ja tekee juttuja
                PORTB |= (1 << PORTB7) | (1 << PORTB0);
                kirjaimen_lahetys('M');
                kirjaimen_lahetys('o');
                kirjaimen_lahetys('l');
                kirjaimen_lahetys('e');
                kirjaimen_lahetys('m');
                kirjaimen_lahetys('m');
                kirjaimen_lahetys('a');
                kirjaimen_lahetys('t');
                kirjaimen_lahetys('\n');
            }
            else if (PORTB & (1 << PORTB7) && PORTB & (1 << PORTB0))
            {
                PORTB |= (1 << PORTB7);
                PORTB &= ~(1 << PORTB0);
                kirjaimen_lahetys('T');
                kirjaimen_lahetys('o');
                kirjaimen_lahetys('i');
                kirjaimen_lahetys('n');
                kirjaimen_lahetys('e');
                kirjaimen_lahetys('n');
                kirjaimen_lahetys('\n');
            }
            else
                {
                    PORTB &= (1 << PORTB7); 
                    PORTB &= (1 << PORTB0);
                    kirjaimen_lahetys('P'); 
                    kirjaimen_lahetys('i');
                    kirjaimen_lahetys('m');
                    kirjaimen_lahetys('e');
                    kirjaimen_lahetys('y');
                    kirjaimen_lahetys('s');
                    kirjaimen_lahetys('\n');
                }

        }
    }
}
