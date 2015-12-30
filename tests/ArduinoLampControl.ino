
// Config Arduino Pins

int lamp1 = 2;
int lamp2 = 3;
int lamp3 = 4;
int lamp4 = 5;

#define PIN_START 2

void setup() { 

    pinMode(lamp1, OUTPUT);     
    pinMode(lamp2, OUTPUT);     
    pinMode(lamp3, OUTPUT);     
    pinMode(lamp4, OUTPUT);     

    // initialize the serial communication:
    Serial.begin(9600);

    printHelp();

}

void loop() {

    while (Serial.available() > 0) {

        // look for the next valid integer in the incoming serial stream:
        int input = Serial.parseInt(); 

        // look for the newline. That's the end of your
        // sentence:
        if (Serial.read() == '\n') {

            int lamp = input >> 1;  // lamp bits
            int state = input & B001; // mask for lamp bit state
            
            configLamp(lamp+PIN_START,state);

            if(input==8)allOn();
            if(input==9)allOff();
            if(input==10)printHelp();
            if(input==11)runTest();

            if(input<8&&input>=0)printOutput(input,lamp,state);

        }
    }
}

void printOutput(int input,int lamp,int state){

    Serial.print("input binary: ");
    Serial.println(input, BIN);

    Serial.print("lamp #: ");
    Serial.print(lamp+1, DEC);

    Serial.print(" state: ");
    Serial.println(state, BIN);
}

void printHelp(){
    Serial.println("Reflectores control 1.0");
    Serial.println("");
    Serial.println("Control Table");
    Serial.println("----------------------");
    Serial.println(" 000    |   Lamp1 off");
    Serial.println(" 001    |   Lamp1 on");
    Serial.println(" 010    |   Lamp2 off");
    Serial.println(" 011    |   Lamp2 on");
    Serial.println(" 100    |   Lamp3 off");
    Serial.println(" 101    |   Lamp3 on");
    Serial.println(" 110    |   Lamp4 off");
    Serial.println(" 111    |   Lamp4 on");
    Serial.println(" 1000   |   all on");
    Serial.println(" 1001   |   all off");
    Serial.println(" 1010   |   print help");
    Serial.println(" 1011   |   run test");
    Serial.println("----------------------");
    Serial.println("");
    Serial.println("waiting for command..");
    Serial.println("");
}

void runTest(){

    Serial.println("running test..");
    
    Serial.print("lamp1 ON "); startLamp(lamp1); delay(1000);
    Serial.print("lamp2 ON "); startLamp(lamp2); delay(1000);
    Serial.print("lamp3 ON "); startLamp(lamp3); delay(1000);
    Serial.print("lamp4 ON "); startLamp(lamp4); delay(1000);

    delay(3000);

    Serial.print("lamp1 OFF "); stopLamp(lamp1); delay(1000);
    Serial.print("lamp2 OFF "); stopLamp(lamp2); delay(1000);
    Serial.print("lamp3 OFF "); stopLamp(lamp3); delay(1000);
    Serial.print("lamp4 OFF "); stopLamp(lamp4); delay(1000);
}

void configLamp(int lamp,int state){
    digitalWrite(lamp,state);
}

void allOn(){
    Serial.println("start all lamps..");
    startLamp(lamp1); startLamp(lamp2);
    startLamp(lamp3); startLamp(lamp4);
}

void allOff(){
    Serial.println("stop all lamps..");
    stopLamp(lamp1); stopLamp(lamp2);
    stopLamp(lamp3); stopLamp(lamp4);
}

void startLamp(int lamp){
    digitalWrite(lamp,HIGH);
}

void stopLamp(int lamp){
    digitalWrite(lamp,LOW);
}
