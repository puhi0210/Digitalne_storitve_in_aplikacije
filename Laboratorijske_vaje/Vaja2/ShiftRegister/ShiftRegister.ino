/* Shift register */
#define ds 12
#define shcp 10
#define stcp 11

void shiftRegister(int data){
  digitalWrite(ds, LOW);
  digitalWrite(shcp, LOW);
  digitalWrite(stcp, LOW);
  for(int i=0;i<8;i++){
    digitalWrite(ds, ((data>>i) & 1));
    digitalWrite(shcp, HIGH);
    digitalWrite(shcp, LOW);
  }
  digitalWrite(stcp, HIGH);
  delay(10);
  digitalWrite(stcp, LOW);
}

void setup(){
  Serial.begin(9600);

  pinMode(ds, OUTPUT);
  pinMode(shcp, OUTPUT);
  pinMode(stcp, OUTPUT);
}

void loop(){
 
  int data = 1;

  for(int i=0;i<8;i++){
    shiftRegister(data);
    data = data *2;
    delay(500);
  }


  for(int i=0;i<8;i++){
    shiftRegister(data);
    data = data /2;
    delay(500);
  }
}

