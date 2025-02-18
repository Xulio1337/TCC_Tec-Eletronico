const int enPin = 8; 
const int stepXPin = 2;  // X.STEP 
const int dirXPin = 5;   // X.DIR 
const int stepYPin = 3;  // Y.STEP 
const int dirYPin = 6;   // Y.DIR 

int pulseWidthMicros = 100;  // micro segundos 
int millisBtwnSteps = 1000; 

const int openDuration = 300; 
const int pinLedA = 31; //lampada do quarto 
const int pinLedB = 33; //cafeteira 
const int pinLedC = 35; //radio 
const int pinLedD = 39; //Luz do sensor 
const int pinTrig = 24; 
const int pinEcho = 26; //branco 

const int Media_Interactions = 10; 
const int Distance_Treshold = 10; 
bool has_AutoGate = false; 
String Serial_Data = ""; 
String Serial1_Data = ""; //Esse segundo Serial_Data serve para exibir
// a imagem no celular atraves do modulo Bluetooth

void setup() 
{ 
Serial.begin(9600); 
Serial.setTimeout(10); 
Serial.flush(); 
Serial.println("Serial USB Inicializada."); 

Serial1.begin(9600); 
Serial1.setTimeout(10); 
Serial1.flush(); 
Serial.println("Serial 1 Inicializada."); 
Serial1.println("Serial 1 Inicializada."); 
pinMode(enPin, OUTPUT); 
digitalWrite(enPin, LOW); 
pinMode(stepXPin, OUTPUT); 
pinMode(dirXPin, OUTPUT); 
pinMode(stepYPin, OUTPUT); 
pinMode(dirYPin, OUTPUT); 
pinMode(pinLedA, OUTPUT); 
pinMode(pinLedB, OUTPUT); 
pinMode(pinLedC, OUTPUT); 
pinMode(pinLedD, OUTPUT); 
pinMode(pinTrig, OUTPUT); 
pinMode(pinEcho, INPUT); 
Serial.println(F("CNC Shield iniciada")); 
} 
void loop() 
{ 

Read_Serial(); 
Read_Serial1(); 
distancia(); 
}
 void Read_Serial() 
 { 
 if (Serial.available() > 0) 
 { 
 int inChar = Serial.read(); 
 if (inChar != '\n') 
 { 
 Serial_Data += (char)inChar; 
 } 
 else 
 { 
 Split_String(); 
 } 
 } 
 } 
 void Read_Serial1() 
 { 
 if (Serial1.available() > 0) 
 { 
 int inChar = Serial1.read(); 
 if (inChar != '\n') 
 { 
 Serial1_Data += (char)inChar; 
 } 
 else 
 { 
 Split_String_1(); 
 } 
 
 } 
 } 
 void Split_String() 
 { 
 int CommaIndex = 0; 
 for (int i = 0; i < Serial_Data.length(); i++) 
 { 
 if (Serial_Data[i] == ',') 
 { 
 CommaIndex = i; 
 } 
 } 
 int  State  =  (Serial_Data.substring(Serial_Data.length()  -  2, 
 Serial_Data.length())).toInt(); 
 int Port = (Serial_Data.substring(1, CommaIndex)).toInt(); 
 Switch_Action(Serial_Data); 
 Serial_Data = ""; 
 } 
 void Split_String_1() 
 { 
 Switch_Action(Serial1_Data); 
 //Serial.print("============> Serial BT DATA "); 
 //Serial.println(Serial1_Data); 
 Serial1_Data = ""; 
 } 
 void moveMotor(int stepPin, int dirPin, int duration) 
 { 
 unsigned long startTime = millis(); 

while (millis() - startTime < duration) 
{ 

digitalWrite(dirPin, HIGH); 
digitalWrite(stepPin, HIGH); 
delayMicroseconds(pulseWidthMicros); 
digitalWrite(stepPin, LOW); 
delayMicroseconds(millisBtwnSteps); 
}
 }
void reverseMoveMotor(int stepPin, int dirPin, int duration) 
{ 

unsigned long startTime = millis(); 
while (millis() - startTime < duration) 
{ 
 
digitalWrite(dirPin, LOW); // Reverso 
digitalWrite(stepPin, HIGH); 
delayMicroseconds(pulseWidthMicros); 
digitalWrite(stepPin, LOW); 
delayMicroseconds(millisBtwnSteps); 
}
 }
void Switch_Action(String command) 
{ 
char Value[20]; 
command.toCharArray(Value, 20); 
Serial.println(Value[0]); 
switch (Value[0]) 
 
{ 
case '1': 
Serial.println(F("Opening Motor X")); 
Serial1.println(F("Opening Motor X")); 
moveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motor X Stopped")); 
Serial1.println(F("Motor X Stopped")); 
break; 
case '2': 
Serial.println(F("Closing Motor X")); 
Serial1.println(F("Closing Motor X")); 
reverseMoveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motor X Stopped")); 
Serial1.println(F("Motor X Stopped")); 
break; 
case '4': 
Serial.println(F("Opening Motor Y")); 
Serial1.println(F("Opening Motor Y")); 
moveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motor Y Stopped")); 
Serial1.println(F("Motor Y Stopped")); 
break; 
case '5': 
Serial.println(F("Closing Motor Y")); 
Serial1.println(F("Closing Motor Y")); 
reverseMoveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motor Y Stopped")); 
Serial1.println(F("Motor Y Stopped")); 
 
break; 
case '7': 
Serial.println(F("Simultaneously Opening Motors X and Y")); 
Serial1.println(F("Simultaneously Opening Motors X and Y")); 
moveMotor(stepXPin, dirXPin, openDuration); 
moveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motors X and Y Stopped")); 
Serial1.println(F("Motors X and Y Stopped")); 
break; 
case '8': 
Serial.println(F("Simultaneously Closing Motors X and Y")); 
Serial1.println(F("Simultaneously Closing Motors X and Y")); 
reverseMoveMotor(stepXPin, dirXPin, openDuration); 
reverseMoveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motors X and Y Stopped")); 
Serial1.println(F("Motors X and Y Stopped")); 
break; 
case '3': 
Serial.println(F("Custom Command: Opening Motor X and Closing Motor Y")); 
Serial1.println(F("Custom Command: Opening Motor X and Closing Motor Y")); 
moveMotor(stepXPin, dirXPin, openDuration); 
reverseMoveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motors X and Y Stopped")); 
Serial1.println(F("Motors X and Y Stopped")); 
break; 
case '6': 
Serial.println(F("Custom Command: Opening Motor Y and Closing Motor X")); 
Serial1.println(F("Custom Command: Opening Motor Y and Closing Motor X")); 
 
moveMotor(stepYPin, dirYPin, openDuration); 
reverseMoveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motors X and Y Stopped")); 
Serial1.println(F("Motors X and Y Stopped")); 
break; 
case 'a': 
digitalWrite(pinLedA, !digitalRead(pinLedA)); // Inverte o estado do LED 
break; 
case 'b': 
digitalWrite(pinLedB, !digitalRead(pinLedB)); 
break; 
case 'c': 
digitalWrite(pinLedC, !digitalRead(pinLedC)); 
break; 
case 'd': 
Serial.println(F("Opening Motor X")); 
Serial1.println(F("Opening Motor X")); 
moveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motor X Stopped")); 
Serial1.println(F("Motor X Stopped")); 
Serial.println(F("Opening Motor Y")); 
Serial1.println(F("Opening Motor Y")); 
moveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motor Y Stopped")); 
Serial1.println(F("Motor Y Stopped")); 
delay(100); 
digitalWrite(pinLedA, LOW); 
digitalWrite(pinLedC, HIGH); 
 
delay(100); 
digitalWrite(pinLedB, HIGH); 
delay(5000); 
digitalWrite(pinLedC, LOW); 
break; 
case 'n': 
Serial.println(F("Closing Motor X")); 
Serial1.println(F("Closing Motor X")); 
reverseMoveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motor X Stopped")); 
Serial1.println(F("Motor X Stopped")); 
Serial.println(F("Closing Motor Y")); 
Serial1.println(F("Closing Motor Y")); 
reverseMoveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motor Y Stopped")); 
Serial1.println(F("Motor Y Stopped")); 
digitalWrite(pinLedA, LOW); 
digitalWrite(pinLedB, LOW); 
digitalWrite(pinLedC, LOW); 
break; 
case 't': 
Serial.println(F("Opening Motor X")); 
Serial1.println(F("Opening Motor X")); 
moveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Motor X Stopped")); 
Serial1.println(F("Motor X Stopped")); 
Serial.println(F("Closing Motor Y")); 
Serial1.println(F("Closing Motor Y")); 
 
reverseMoveMotor(stepYPin, dirYPin, openDuration); 
Serial.println(F("Motor Y Stopped")); 
Serial1.println(F("Motor Y Stopped")); 
digitalWrite(pinLedA, HIGH); 
delay(100); 
digitalWrite(pinLedB, LOW); 
delay(100); 
digitalWrite(pinLedC, HIGH); 
break; 

default: 

break; 
} 
} 
void distancia() { 
digitalWrite(pinTrig, LOW); 
delayMicroseconds(2); 
digitalWrite(pinTrig, HIGH); 
delayMicroseconds(10); 
digitalWrite(pinTrig, LOW); 

long duration = pulseIn(pinEcho, HIGH); 
int distance = duration * 0.034 / 2; 
//Aqui existia um Serial.Print para a distancia, retirado por motivos convencionais 

if (distance <= 5) { 
 
digitalWrite(pinLedD, HIGH);  // Liga o LED 
reverseMoveMotor(stepXPin, dirXPin, openDuration); 
Serial.println(F("Opening Motor X")); 
Serial1.println(F("Opening Motor X")); 
// Aguarda 3 segundos 
delay(1000); 
Serial.println(F("aguardando X")); 
Serial1.println(F("aguardando X")); 
delay(3000); 
//Inverte o motor após 3 segundos 
moveMotor(stepXPin, dirXPin, openDuration); 
digitalWrite(pinLedD, LOW); 
Serial.println(F("Closing Motor X")); 
Serial1.println(F("Closing Motor X")); 
// Mantém-se disponível para detecção contínua 
} 
// Delay opcional para evitar leituras muito frequentes 
delay(1000); 
} 