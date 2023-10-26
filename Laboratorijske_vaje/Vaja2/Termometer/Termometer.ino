/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

int temp;
double mv;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);

  mv = (sensorValue * 5000.00) /1023.00;

  temp = (mv -400) /19.5;


  // print out the value you read:
  Serial.println(getTemp(sensorValue));
  Serial.println(temp);
  Serial.println("\n");
  delay(100);  // delay in between reads for stability


}

double getTemp(int adc){
  double t = (((adc * 5000.00) /1023.00) -400) /19.5;
  return t;
}
