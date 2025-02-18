const int enPin = 8;
const int stepXPin = 2;  // X.STEP
const int dirXPin = 5;   // X.DIR
const int stepYPin = 3;  // Y.STEP
const int dirYPin = 6;   // Y.DIR

const int pulseWidthMicros = 100;  // microsegundos
const int millisBtwnSteps = 1000;

const int openDuration = 300;
const int pinLedA = 31; // Lampada do quarto
const int pinLedB = 33; // Cafeteira
const int pinLedC = 35; // Radio
const int pinLedD = 39; // Luz do sensor
const int pinTrig = 24;
const int pinEcho = 26;

const int Distance_Treshold = 10;
String Serial_Data = "";
String Serial1_Data = ""; // Dados do Bluetooth

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);
    Serial.println("Serial USB Inicializada.");
    
    Serial1.begin(9600);
    Serial1.setTimeout(10);
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

void loop() {
    Read_Serial();
    Read_Serial1();
    distancia();
}

void Read_Serial() {
    while (Serial.available() > 0) {
        char inChar = Serial.read();
        if (inChar != '\n') {
            Serial_Data += inChar;
        } else {
            Split_String();
        }
    }
}

void Read_Serial1() {
    while (Serial1.available() > 0) {
        char inChar = Serial1.read();
        if (inChar != '\n') {
            Serial1_Data += inChar;
        } else {
            Split_String_1();
        }
    }
}

void Split_String() {
    Switch_Action(Serial_Data);
    Serial_Data = "";
}

void Split_String_1() {
    Switch_Action(Serial1_Data);
    Serial1_Data = "";
}

void moveMotor(int stepPin, int dirPin, int duration) {
    digitalWrite(dirPin, HIGH);
    unsigned long startTime = millis();
    while (millis() - startTime < duration) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(pulseWidthMicros);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(millisBtwnSteps);
    }
}

void reverseMoveMotor(int stepPin, int dirPin, int duration) {
    digitalWrite(dirPin, LOW);
    unsigned long startTime = millis();
    while (millis() - startTime < duration) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(pulseWidthMicros);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(millisBtwnSteps);
    }
}

void Switch_Action(String command) {
    char Value = command[0];
    Serial.println(Value);
    
    switch (Value) {
        case '1':
            moveMotor(stepXPin, dirXPin, openDuration);
            break;
        case '2':
            reverseMoveMotor(stepXPin, dirXPin, openDuration);
            break;
        case '4':
            moveMotor(stepYPin, dirYPin, openDuration);
            break;
        case '5':
            reverseMoveMotor(stepYPin, dirYPin, openDuration);
            break;
        case '7':
            moveMotor(stepXPin, dirXPin, openDuration);
            moveMotor(stepYPin, dirYPin, openDuration);
            break;
        case '8':
            reverseMoveMotor(stepXPin, dirXPin, openDuration);
            reverseMoveMotor(stepYPin, dirYPin, openDuration);
            break;
        case 'a':
            digitalWrite(pinLedA, !digitalRead(pinLedA));
            break;
        case 'b':
            digitalWrite(pinLedB, !digitalRead(pinLedB));
            break;
        case 'c':
            digitalWrite(pinLedC, !digitalRead(pinLedC));
            break;
        case 'd':
            moveMotor(stepXPin, dirXPin, openDuration);
            moveMotor(stepYPin, dirYPin, openDuration);
            digitalWrite(pinLedA, LOW);
            digitalWrite(pinLedC, HIGH);
            delay(100);
            digitalWrite(pinLedB, HIGH);
            delay(5000);
            digitalWrite(pinLedC, LOW);
            break;
        case 'n':
            reverseMoveMotor(stepXPin, dirXPin, openDuration);
            reverseMoveMotor(stepYPin, dirYPin, openDuration);
            digitalWrite(pinLedA, LOW);
            digitalWrite(pinLedB, LOW);
            digitalWrite(pinLedC, LOW);
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
    
    if (distance <= 5) {
        digitalWrite(pinLedD, HIGH);
        reverseMoveMotor(stepXPin, dirXPin, openDuration);
        delay(3000);
        moveMotor(stepXPin, dirXPin, openDuration);
        digitalWrite(pinLedD, LOW);
    }
    delay(1000);
}
