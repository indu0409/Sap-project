int irPin1=7;
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int irPin2=8;
int count=0;
int led=13;
int buzzer=4;
boolean state1 = true;
boolean state2 = true;
boolean insideState = false;
boolean outsideIr=false;
boolean isPeopleExiting=false;
int i=1;
void setup() {
Serial.begin(9600);
pinMode(irPin1, INPUT);
pinMode(irPin2, INPUT);
pinMode(led, OUTPUT);
pinMode(buzzer, OUTPUT);

}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");

  delay(1500);
  if (!digitalRead(irPin1) && i==1 && state1){
     outsideIr=true;
     delay(100);
     i++;
     state1 = false;
  }

   if (!digitalRead(irPin2) && i==2 &&   state2){
     Serial.println("Entering into room");
     outsideIr=true;
     delay(100);
     i = 1 ;
     count++;
     Serial.print("No of persons inside the room: ");
     Serial.println(count);
     state2 = false;
  }

   if (!digitalRead(irPin2) && i==1 && state2 ){
     outsideIr=true;
     delay(100);
     i = 2 ;
     state2 = false;
  }
if(count>5)
{
  digitalWrite(led,HIGH);
  digitalWrite(buzzer,HIGH);
}
else
{
  digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
}
  if (!digitalRead(irPin1) && i==2 && state1 ){
     Serial.println("Exiting from room");
     outsideIr=true;
     delay(100);
     count--;
       Serial.print("Nos of persons inside the room: ");
       Serial.println(count);
     i = 1;
     state1 = false;
  }  
    if (digitalRead(irPin1)){
     state1 = true;
    }

     if (digitalRead(irPin2)){
     state2 = true;
    }
  
}
