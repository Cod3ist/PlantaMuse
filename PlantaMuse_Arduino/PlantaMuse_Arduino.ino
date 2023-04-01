const int BUTTON_PIN = 2; // Arduino pin connected to button's pin
bool power = false;  // the current state of device

const int LED_PIN_1    = 13; // Arduino pin connected to LED's pin to show ON/OFF
const int LED_PIN_2    = 12; // Arduino pin connected to LED's pin to show plant Happy
const int LED_PIN_3    = 8; // Arduino pin connected to LED's pin to show plant Sad


void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(LED_PIN_2, OUTPUT); // set arduino pin to output mode
  pinMode(LED_PIN_3, OUTPUT); // set arduino pin to output mode
  pinMode(BUTTON_PIN, INPUT); // set arduino pin to input 
  pinMode(LED_PIN_1, OUTPUT);  // set arduino pin to output mode
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), pin_Interrupt, FALLING); 
}

void loop() {
  if (power == true){    
    // Device ON
    device_on();
  } else {        
    // Device OFF
    device_off();
  }  
}


void device_on(){
  int sensorValue = 0 ; //value obtainesd from sensor
  
  digitalWrite(LED_PIN_1, HIGH);
  
  Serial.print("ON,");
  
   if ((digitalRead(10)==1)||(digitalRead(11)==1)){ 
    // electrodes not patched to surface 
     sensorValue = 0;
   } else {                                           
    // electrodes patched to surface 
     sensorValue = analogRead(A0);
   }
   read_moisture();
   Serial.println(sensorValue);
   delay(5000);
}

void device_off(){
  Serial.println("OFF");
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  delay(2000);
}

void read_moisture(){
    int moistureValue = analogRead(A0); // read moisture value
    if (moistureValue < 350){     // Happy condition
      digitalWrite(LED_PIN_3, LOW);
      digitalWrite(LED_PIN_2, HIGH);
    } else {                       // Sad condition
      digitalWrite(LED_PIN_3, HIGH);
      digitalWrite(LED_PIN_2, LOW);
    }
}

void pin_Interrupt(){
  //power ON or OFF the device
  power = !power;
}
