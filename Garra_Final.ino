#include <Servo.h>  //Inclui a Biblioteca do servomotor

// Define pinos dos servos
#define pinoServoGarra 6
#define pinoServoAngulo 9
#define pinoServoAltura 10
#define pinoServoBase 11

// Define as portas dos potenciômetros
#define potGarra A0
#define potAngulo A1
#define potAltura A2
#define potBase A3

// Define os componentes
#define ledVerde 13
#define ledAmarelo 12
#define botaoModoOperacao 2
#define botaoLocal1 3
#define botaoLocal2 4
#define botaoLocal3 5
#define botaoLocal4 7


// Nomeia os servos
Servo servoGarra, servoAngulo, servoAltura, servoBase;

// Cria as variáveis dos ângulos de cada motor
int motorGarra, motorAngulo, motorAltura, motorBase;

// Cria as variáveis do código
// Cria as váriáveis do tipo "byte" para alternar entre os modos de operação.
byte modoOperacao = 1, flagMovimento = 1; //Flag para coletar objeto = 1. Flag para posicionar o objeto = 2.


//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------


void trocaModoOperacao();  // Boa prática, declara/prototipa a função, para que o arduíno entenda que ela existe e será chamada em algum momento do código.
void trocaFlagMovimento();
void posicionarPadrao();
void posicionarControlandoVelocidade();


void setup() {
  //Inicia o monitor serial
  Serial.begin(9600); 

  //Cofigura os componentes que serão utilizados
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(potGarra, INPUT);
  pinMode(potAngulo, INPUT);
  pinMode(potAltura, INPUT);
  pinMode(potBase, INPUT);
  pinMode(botaoLocal1, INPUT);
  pinMode(botaoLocal2, INPUT);
  pinMode(botaoLocal3, INPUT);
  pinMode(botaoLocal4, INPUT);
  pinMode(botaoModoOperacao, INPUT);

  // Atribui pinos dos servos
  servoGarra.attach(pinoServoGarra);
  servoAngulo.attach(pinoServoAngulo);
  servoAltura.attach(pinoServoAltura);
  servoBase.attach(pinoServoBase);

  // Declara função de interrupção, que serve para alterar o modo de operação
  attachInterrupt(digitalPinToInterrupt(botaoModoOperacao), trocaModoOperacao, RISING); 
}


//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------


void loop(){

  
  //  Permite interrupção ao longo do loop
  interrupts();
  static unsigned long delayControle, delayCoordenadas;


  //  Modo de Operação Manual (com potenciômetro).
  if(modoOperacao==1){
    
    // Acende o led amarelo, indicando o modo de operação com Potenciômetro (
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    
    // Leitura dos potenciômetros
    if((millis() - delayControle) < 10){
      motorGarra = map(analogRead(potGarra),0,1023,12,145);
      motorAngulo = map(analogRead(potAngulo),0,1023,5,175);
      motorAltura = map(analogRead(potAltura),0,1023,15,165);
      motorBase = map(analogRead(potBase),0,1023,30,170);
    }
    else{
      // Posicionamento dos potenciômetros 
      servoGarra.write(motorGarra);
      servoAngulo.write(motorAngulo);
      servoAltura.write(motorAltura);
      servoBase.write(motorBase);   
    }
    if((millis() - delayControle) >= 20){
      delayControle = millis();
    }

    /*!!!!!ATENÇÃO!!!!!
     * CAUSA LENTIDÃO
    //Mostra as coordenadas dos servos no monitor serial*/
    if((millis() - delayCoordenadas) < 100){
      Serial.print("\n1 - Servo Garra | Potenciometro = ");
      Serial.println(motorGarra);
      Serial.print("2 - Servo Angulo | Potenciometro = ");
      Serial.println(motorAngulo);
      Serial.print("3 - Servo Altura | Potenciometro = ");
      Serial.println(motorAltura);
      Serial.print("4 - Servo Base | Potenciometro = ");
      Serial.println(motorBase);
    }
    if((millis() - delayCoordenadas) >= 3100){
      delayCoordenadas = millis();
    }
  }



  //  Modo de Operação Automático (com botão).
  if(modoOperacao==2){
    
    // Ascende o led vermelho, indicado o modo de operação com Joystick
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);

    if((millis() - delayControle) < 50){
      if(digitalRead(botaoLocal1)==HIGH && flagMovimento == 1){ // COLETAR NO PRIMEIRO LOCAL
        posicionarPadrao();
        posicionarControlandoVelocidade(servoBase, 105, 165, 50);
        posicionarControlandoVelocidade(servoAngulo, 75, 76, 50);
        posicionarControlandoVelocidade(servoAltura, 125, 67, 50);
        posicionarControlandoVelocidade(servoGarra, 15, 145, 28);
        posicionarControlandoVelocidade(servoAltura, 67, 115, 50);
        trocaFlagMovimento();
        /*
        * CÓDIGO DE ZERAMENTO - DEBUG
        * servoGarra.write(0);
        * servoAngulo.write(0);
        * servoAltura.write(0);
        * servoBase.write(0);
        */
      }
      if(digitalRead(botaoLocal2)==HIGH && flagMovimento == 1){ // COLETAR NO SEGUNDO LOCAL
        posicionarPadrao();
        posicionarControlandoVelocidade(servoBase, 105, 101, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 84, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 68, 28);
        posicionarControlandoVelocidade(servoGarra, 15, 145, 28);
        posicionarControlandoVelocidade(servoAltura, 68, 125, 28);
        trocaFlagMovimento();
      }
      if(digitalRead(botaoLocal3)==HIGH && flagMovimento == 1){ // COLETAR NO TERCEIRO LOCAL
        posicionarPadrao();
        posicionarControlandoVelocidade(servoBase, 105, 95, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 147, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 105, 28);
        posicionarControlandoVelocidade(servoGarra, 15, 145, 28);
        posicionarControlandoVelocidade(servoAngulo, 147, 75, 28);
        trocaFlagMovimento();
      }
      if(digitalRead(botaoLocal4)==HIGH && flagMovimento == 1){ // COLETAR NO QUARTO LOCAL
        posicionarPadrao();
        posicionarControlandoVelocidade(servoBase, 105, 66, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 126, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 87, 28);
        posicionarControlandoVelocidade(servoGarra, 15, 145, 28);
        posicionarControlandoVelocidade(servoAngulo, 126, 75, 28);
        trocaFlagMovimento();
      }


      //Posiciona o objeto:
      if(digitalRead(botaoLocal1)==HIGH && flagMovimento == 2){ // POSICIONAR NO PRIMEIRO LOCAL
        servoBase.write(105);
        delay(1000);
        servoAltura.write(125);
        delay(1000);
        servoAngulo.write(75);
        delay(1000);
        posicionarControlandoVelocidade(servoBase, 105, 165, 50);
        posicionarControlandoVelocidade(servoAngulo, 75, 76, 50);
        posicionarControlandoVelocidade(servoAltura, 125, 67, 50);
        posicionarControlandoVelocidade(servoGarra, 145, 15, 28);
        posicionarControlandoVelocidade(servoAltura, 67, 115, 50);
        trocaFlagMovimento();
      }
      if(digitalRead(botaoLocal2)==HIGH && flagMovimento == 2){ // POSICIONAR NO SEGUNDO LOCAL
        servoBase.write(105);
        delay(1000);
        servoAltura.write(125);
        delay(1000);
        servoAngulo.write(75);
        delay(1000);
        posicionarControlandoVelocidade(servoBase, 105, 101, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 84, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 68, 28);
        posicionarControlandoVelocidade(servoGarra, 145, 15, 28);
        posicionarControlandoVelocidade(servoAltura, 68, 125, 28);
        trocaFlagMovimento();
      }
      if(digitalRead(botaoLocal3)==HIGH && flagMovimento == 2){ // POSICIONAR NO TERCEIRO LOCAL
        servoBase.write(105);
        delay(1000);
        servoAltura.write(125);
        delay(1000);
        servoAngulo.write(75);
        delay(1000);
        posicionarControlandoVelocidade(servoBase, 105, 95, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 147, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 105, 28);
        posicionarControlandoVelocidade(servoGarra, 145, 15, 28);
        posicionarControlandoVelocidade(servoAngulo, 147, 75, 28);
        trocaFlagMovimento();
      }
      if(digitalRead(botaoLocal4)==HIGH && flagMovimento == 2){ // POSICIONAR NO QUARTO LOCAL
        servoBase.write(105);
        delay(1000);
        servoAltura.write(125);
        delay(1000);
        servoAngulo.write(75);
        delay(1000);
        posicionarControlandoVelocidade(servoBase, 105, 66, 28);
        posicionarControlandoVelocidade(servoAngulo, 75, 126, 28);
        posicionarControlandoVelocidade(servoAltura, 125, 87, 28);
        posicionarControlandoVelocidade(servoGarra, 145, 15, 28);
        posicionarControlandoVelocidade(servoAngulo, 126, 75, 28);
        trocaFlagMovimento();
      }

      
    }
  
    else{
      // Posiciona os servos de acordo com o mapeamento dos potenciômetros
      /*servoGarra.write(motorGarra);
      servoAngulo.write(motorAngulo);
      servoAltura.write(motorAltura);
      servoBase.write(motorBase);*/
    }
  
    if((millis() - delayControle) >= 100){
      delayControle = millis();
    }

    /*!!!!!ATENÇÃO!!!!!
     * CAUSA LENTIDÃO
    //Mostra as coordenadas dos servos no monitor serial*/
    if((millis() - delayCoordenadas) < 100){
      Serial.print("\n1 - Servo Garra | Potenciometro = ");
      Serial.println(motorGarra);
      Serial.print("2 - Servo Angulo | Potenciometro = ");
      Serial.println(motorAngulo);
      Serial.print("3 - Servo Altura | Potenciometro = ");
      Serial.println(motorAltura);
      Serial.print("4 - Servo Base | Potenciometro = ");
      Serial.println(motorBase);
    }
    if((millis() - delayCoordenadas) >= 3100){
      delayCoordenadas = millis();
    }
  }
}


//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------


//  Declara função de troca de modo de operação
void trocaModoOperacao(){
  modoOperacao++;
  if(modoOperacao==3){
    modoOperacao=1;
  }
}

void trocaFlagMovimento(){
  flagMovimento++;
  if(flagMovimento==3){
    flagMovimento=1;
  }
}

void posicionarPadrao(){
  servoGarra.write(12);
  delay(1000);
  servoBase.write(105);
  delay(1000);
  servoAltura.write(125);
  delay(1000);
  servoAngulo.write(75);
  delay(1000);
  
 /* posicionarControlandoVelocidade(servoGarra, motorGarra, 15, 50);
  * posicionarControlandoVelocidade(servoBase, motorBase, 105, 50);
  * posicionarControlandoVelocidade(servoAngulo, motorAngulo, 75, 50);
  * posicionarControlandoVelocidade(servoAltura, motorAltura, 125, 50);
 */
}

void posicionarControlandoVelocidade(Servo servo, int posicaoAtual, int posicaoMaxGiro, int velocidade){
  static unsigned long delayGiro;
  while(posicaoAtual!=posicaoMaxGiro){
    if((millis() - delayGiro) < 5){
      servo.write(posicaoAtual);
    }
  
    if((millis() - delayGiro) >= velocidade){
      if(posicaoAtual<posicaoMaxGiro){
        posicaoAtual++;
      }
      else{
        posicaoAtual--;
      }
      delayGiro = millis();
    }
  }
}
