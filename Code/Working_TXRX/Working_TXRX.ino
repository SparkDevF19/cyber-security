#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int switchPin = 8;
int rxLED = 7; //yellow 
int txLED = 6; //green 
int buttonPin = 5;
//unsigned long data_to_send;
unsigned long data = 0;
unsigned long data_length = 0 ;
unsigned int* data_bin;

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  //Receiver is connected to Arduino Pin Digital #2
  mySwitch.enableReceive(0);

  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(rxLED, OUTPUT);
  pinMode(txLED, OUTPUT);
  
  //Optional set protocol (default is 1, will work for most outlets)
  //mySwitch.setProtocol(2);
  
  //Optional set pulse length.
   mySwitch.setPulseLength(321);
  
  //Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(1);
  
}

void loop() {
  int switchVal = digitalRead(switchPin);
  if(switchVal == HIGH) {
    digitalWrite(rxLED, LOW);
    digitalWrite(txLED, HIGH);
    int buttonVal = digitalRead(buttonPin);
    
    if(buttonVal == HIGH) {
      //Transmitting
      Serial.println("Sending!");
      //sending as decimal
      mySwitch.send(data, data_length);
      Serial.println(data);
      Serial.println(data_length);
      //sending as binary
      //mySwitch.sendChar("1111111111000010010011110000100000100010011010000010110000000101");
  
      //mySwitch.send("010000101001111100101111111111111111111");
      //Serial.println("01000010100111110010110010101011101100101111011010110110101");
      //mySwitch.send(data, data_length);
    }  
  } else {
    //Receiving
    digitalWrite(rxLED, HIGH);
    digitalWrite(txLED, LOW);
    //Serial.println("Receiving");
    
    if (mySwitch.available()) {
      //transmit with decimal
      data = mySwitch.getReceivedValue();
      data_length = mySwitch.getReceivedBitlength();
      //transmit with binary format
      //data_bin = mySwitch.getReceivedRawdata();
    
      Serial.println(data);
      Serial.println(data_length);
      //Serial.println(*data_bin);
      //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
      mySwitch.resetAvailable();//resets data or getReceivedValue to 0
    } else {
    //Serial.println("not available");
    }
  }
}
