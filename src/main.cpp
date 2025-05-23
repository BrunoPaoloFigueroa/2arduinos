#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

unsigned char z = 0;
unsigned char doto=0;
void config_ADC(void){

    ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
}
float valve=0;
ISR(ADC_vect){
    valve=(ADC*50/1023.0)+40;
    UCSR0B|=(1<<UDRIE0);

}

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
    UBRR0=103;
}
ISR(USART_UDRE_vect){
   
   UDR0=valve;
   ADCSRA|=(1<<ADSC);
    _delay_ms(100);
}

int main(void){

  config_USART();
    config_ADC();   
    ADCSRA|=(1<<ADSC);
    sei();
    while(1){

    }

}




/*
void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
    UBRR0=103;
}
void display(float valor){

  int val = (int)(valor * 100); // Convierte, ej: 0.73 -> 73
  if (val > 999) val = 999;

  int c = val / 100;        // Centenas
  int d = (val / 10) % 10;  // Decenas
  int u = val % 10;         // Unidades

  // Mostrar centenas
  PORTB |= 0x07;           // Apaga todos los displays
  PORTD = (PORTD & 0x0F) | (c << 4); // Envia BCD al 74LS48
  PORTB &= ~(1 << 2);        // Enciende display 1
  _delay_ms(1);

  // Mostrar decenas
  PORTB |= 0x07;
  PORTD = (PORTD & 0x0F) | (d << 4);
  PORTB &= ~(1 << 1);        // Enciende display 2
  _delay_ms(1);

  // Mostrar unidades
  PORTB |= 0x07;
  PORTD = (PORTD & 0x0F) | (u << 4);
  PORTB &= ~(1 << 0);        // Enciende display 3
  _delay_ms(1);
}
unsigned char doto=0;
ISR(USART_RX_vect){
    
   doto=UDR0;

    
}

int main(void){

  DDRD|=0xF0;
    DDRB|=0x0F;
    PORTB&=~(0x08);
    config_USART();
    sei();

    while(1){


     
        display(doto);
    
  
    }


  return 0;
}
*/