
 
#include <Servo.h>  //include servo.h library
Servo myservo;
 
int pos = 0;    

 
int flameCentro = A4;     // left sensor
int flameEsquerda = A3;  // right sensor
int flameDireita = A5; 
int ParamDeFogo = 400;  

#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pump 10
 
void setup()
{
  pinMode(flameCentro, INPUT);
  pinMode(flameEsquerda, INPUT);
  pinMode(flameDireita, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
 Serial.begin(9600);
  myservo.attach(8);
  myservo.write(90); 
}
 
void apagarFogo()
{
    delay (500);

   digitalWrite(pump, HIGH);
   delay(500);
    
    for (pos = 90; pos > 0; pos -= 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 0; pos < 180; pos += 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pump,LOW);
  myservo.write(90);

}

void MoverDireita() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(1000);
}
void MoverEsquerda() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}
void MoverFrente() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
 
}
void Parar() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
 
}
 
void loop()
{
  myservo.write(90);  
  int valorFlameDireita = analogRead(flameDireita);
  int valorFlameEsquerda = analogRead(flameEsquerda);
  int valorFlameCentro = analogRead(flameCentro);
  Serial.println(valorFlameDireita);
  Serial.println(valorFlameEsquerda);
  Serial.println(valorFlameCentro);


  if((valorFlameDireita <= ParamDeFogo) && ((valorFlameCentro >= ParamDeFogo))){
      MoverDireita();
  }else if((valorFlameEsquerda <= ParamDeFogo) && ((valorFlameCentro >= ParamDeFogo))){
    MoverEsquerda();
  }else if(valorFlameCentro <= ParamDeFogo){
    if(valorFlameCentro < 100){
     Parar();
     apagarFogo();
    }else{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
     }
  }else{
     Parar();
  }
     delay(300);
}