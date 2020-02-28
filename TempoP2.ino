/* 
Example Timer1 Interrupt
Flash LED every second
*/

#define ledPin 13
int pinV1 = 11;
int pinA1 = 10;
int pinR1 = 50;
int pinV2 = 51;
int pinA2 = 52;
int pinR2 = 53;
int timer1_counter;
volatile int Totalinterrupts;
int tots;
void setup()
{
  pinMode(pinV1, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinR1, OUTPUT);
  pinMode(pinV2, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(pinR2, OUTPUT);
   Serial.begin(115200);

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  timer1_counter = 15624;   // preload timer 65536-16MHz/256/1Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  Totalinterrupts++;
    Serial.print("Total Ticks:");
  Serial.println(Totalinterrupts);
  
}

void loop()
{
   //primer semafaro
if (Totalinterrupts <= 5) {
   digitalWrite(pinV1, HIGH);
   digitalWrite(pinR1, LOW);    

  }
  if (5 < Totalinterrupts && Totalinterrupts <= 6) { 
    digitalWrite(pinA1, HIGH); 
    digitalWrite(pinV1, LOW); 

  }
  if ( 6 < Totalinterrupts && Totalinterrupts <= 12) { 
    digitalWrite(pinR1, HIGH); 
    digitalWrite(pinA1, LOW);   

  }
  //segundo semafaro
  if (Totalinterrupts <= 6) {
    digitalWrite(pinR2, HIGH); 
    digitalWrite(pinA2, LOW);     

  }
  if (6 < Totalinterrupts && Totalinterrupts <= 11) {
    digitalWrite(pinV2, HIGH); 
    digitalWrite(pinR2, LOW);   

  }
  if ( 11 < Totalinterrupts && Totalinterrupts <= 12) {
    digitalWrite(pinA2, HIGH); 
    digitalWrite(pinV2, LOW);     

  }
  if (Totalinterrupts > 11) {
    Totalinterrupts = 0;
  }
}
