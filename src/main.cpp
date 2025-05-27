/*
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
    valve=(ADC*500.0/1023.0);
    UCSR0B|=(1<<UDRIE0);

}

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
    UBRR0=103;
}
ISR(USART_UDRE_vect){
   
   UDR0=(unsigned char)valve;
   UCSR0B &= ~(1 << UDRIE0);
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
return 0;
}

*/
/*

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
    UBRR0=103;
}
void display(float valor){

  int val = (int)(valor ); // Convierte, ej: 0.73 -> 73
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
/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

volatile uint8_t parte_alta = 0;
volatile uint8_t parte_baja = 0;
volatile uint8_t contador = 0;
volatile uint16_t valor_recibido = 0;

void config_USART(void) {
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
    UBRR0 = 103;
}

ISR(USART_RX_vect) {
    if (contador == 0) {
        parte_alta = UDR0;
        contador = 1;
    } else {
        parte_baja = UDR0;
        valor_recibido = (parte_alta << 8) | parte_baja;
        if (valor_recibido > 500) valor_recibido = 500;
        contador = 0;
    }
}

void display(uint16_t valor) {
    uint8_t c = valor / 100;        // Parte entera (V)
    uint8_t d = (valor / 10) % 10;  // Décima
    uint8_t u = valor % 10;         // Centésima

    // Display 1 (c)
    PORTB |= 0x07;
    PORTD = (PORTD & 0x0F) | (c << 4);
    PORTB &= ~(1 << 2);
    _delay_ms(1);

    // Display 2 (d)
    PORTB |= 0x07;
    PORTD = (PORTD & 0x0F) | (d << 4);
    PORTB &= ~(1 << 1);
    _delay_ms(1);

    // Display 3 (u)
    PORTB |= 0x07;
    PORTD = (PORTD & 0x0F) | (u << 4);
    PORTB &= ~(1 << 0);
    _delay_ms(1);
}

int main(void) {
    DDRD |= 0xF0;   // 4 bits para BCD
    DDRB |= 0x0F;   // 3 bits para control de displays + punto decimal
    PORTB &= ~0x08; // Apaga punto decimal si está en PB3
    config_USART();
    sei();

    while (1) {
        display(valor_recibido); // Muestra valor continuamente
    }
    return 0;
}
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL


void config_ADC(void){

    ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
}

float valve=0;
char enviar=1;
ISR(ADC_vect){
    valve=(ADC*500.0/1023.0);
    UCSR0B|=(1<<UDRIE0);

}

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
    UBRR0=103;
}
