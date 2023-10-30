/*
Sistemas Embebidos TP1 Parte 2A-Display de 7 segmentos com 4 digitos (Relógio)
Trabalho realizado por:
  Cláudio Coelho a22106474
  Lucas Martins a22103318
Trabalho realizado com base em:
  https://www.youtube.com/watch?v=3m4jhmafg8E
  https://www.youtube.com/watch?v=6XY9PooMrms&t=1101s
  https://www.youtube.com/watch?v=fYAlE1u5rno&t=44s
  https://www.electronicssimplified.in/feed/2062/
  https://github.com/DeanIsMe/SevSeg/tree/master
  https://projecthub.arduino.cc/SAnwandter1/programming-4-digit-7-segment-led-display-5c4617
  https://www.arduino.cc/reference/en/libraries/sevseg/
*/

#include "SevSeg.h" //Biblioteca para o controlo de displays de 7 segmentos com 4 digitos.

#define segA 2
#define segB 3
#define segC 4
#define segD 5
#define segE 6
#define segF 7
#define segG 8
#define segDP 9
#define D1 10
#define D2 11
#define D3 12
#define D4 13

SevSeg sevseg;

void setup() {
  //Configuração da biblioteca
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = false; //Indica à biblioteca que não há resistências nos segmentos.
  byte hardwareConfig = COMMON_ANODE; //Mostra à biblioteca que o display a ser utilizado é um display ânodo comum
  bool updateWithDelays = false; //Por defeito é false, recomendado segundo a documentação da biblioteca.
  bool leadingZeros = true; //Mostra zeros nas casas da esquerda caso o valor ocupe menos de quatro digitos no display.
  bool disableDecPoint = false; //Mantém permite a ativação do ponto décimal por meio da biblioteca.
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,updateWithDelays, leadingZeros, disableDecPoint);

  //Coloca os pinos de 2 a 13 a realizar output.
  for (byte i = 2; i < 14; i++){pinMode(i, OUTPUT);}
}

int countD1 = 0; //Define o primeiro digito da hora.
int countD2 = 0; //Define o segundo digito da hora.
int countD3 = 0; //Define o primeiro digito dos minutos.
int countD4 = 0; //Define o segundo digito dos minutos.

void loop() {

  if(countD4 >= 10){countD4=0;countD3+=1;} //Incrementa o primeiro digito dos minutos e iguala o segundo a 0 sempre que o segundo seja maior ou igual a 10.
  if(countD3 >= 6){countD3=0;countD2+=1;} //Incrementa o segundo digito das horas e igual o primeiro dos minutos a 0 sempre que o primeiro digito dos minutos seja maior ou igual a 6.
  if(countD1 < 2){ //Verifica se o primeiro digito das horas é superior a 2.
    if(countD2 >= 10){countD2=0;countD1+=1;} //Se o primeiro digito das horas fôr maior que 2 e o segundo maior ou igual a 10 o primeiro digito das horas é incrementado e o segundo é igualado a 0. 
  }else{  //Ocorre caso o primeiro digito das horas seja inferior a 2.
    if(countD2 >= 4){countD1=0;countD2=0;countD3=0;countD4=0;} //Se o primeiro digito das hora fôr menor que 2 e o segundo maior ou igual a quatro os quatro digitos do display são igualados a 0.
  }
  for(int i=0;i<26950;i++){ //Garante que cada hora aparece no display durante aproximadamente 1 minuto, o número de ciclos ideal para tal (26950) foi definido através de vários testes.
  sevseg.setNumber(countD1*1000 + countD2*100 + countD3*10 + countD4,2); //Define o número que o display deve mostrar e o número de casas decimais presentes no mesmo.
  sevseg.refreshDisplay(); //Fundamental para o funcionamento correto da biblioteca, garantindo que o display mostre o que deve.
  delay(2);
}
  countD4 += 1; //Incrementado cada vez que o loop é realizado.
}
