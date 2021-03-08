#define REL1 2 //pin releu 1 
#define REL2 3 // pin releu 2
#define REL3 4 //pin releu 3
#define REL4 5 //pin releu 4
#define CD 7 //comanda deschide_poarta telecomanda 1


unsigned long time1;
unsigned long  timp_intarziere=35*10;
unsigned int starePoarta=0;
unsigned int stareVechePoarta=0;
unsigned int valVecheTelecomanda=0;


void deschide_poarta(){
Serial.println("Deschid\n");
  digitalWrite(REL3, HIGH);
  digitalWrite(REL4, HIGH);
  delay(500);
  digitalWrite(REL1, LOW);
  digitalWrite(REL2, LOW); 
    
}

void inchide_poarta(){
  Serial.println("Inchid\n");
  digitalWrite(REL1, HIGH);
  digitalWrite(REL2, HIGH);
  delay(500);
  digitalWrite(REL3, LOW);
  digitalWrite(REL4, LOW); 
   
}
void opreste_poarta(){
  digitalWrite(REL1, HIGH);
  digitalWrite(REL2, HIGH);

  digitalWrite(REL3, HIGH);
  digitalWrite(REL4, HIGH);
  delay(1000);
  Serial.println("Opresc\n");
}

void setup(){
  Serial.begin (9600);
  pinMode(REL1, OUTPUT);
    pinMode(REL2, OUTPUT);
    pinMode(REL3, OUTPUT);
    pinMode(REL4, OUTPUT);
    pinMode(CD, INPUT);
     time1=0;
  void opreste_poarta();
  starePoarta=0;
  stareVechePoarta=0;
  
}
void loop(){
  
  unsigned long milli;
  milli=millis()/100;
  int   valCD = digitalRead(CD);
  int stareVeche=starePoarta;
  int evenimentButon=valCD!=valVecheTelecomanda;
  valVecheTelecomanda=valCD;

  if(evenimentButon==HIGH){ 
    if(starePoarta==0){
      stareVechePoarta=1;
      starePoarta=2;
      inchide_poarta();
      time1=milli+timp_intarziere;
    }
    else if(starePoarta==1){
      starePoarta=2;
      stareVechePoarta=0;
      deschide_poarta();
      time1=milli+timp_intarziere;
    }
    else if(starePoarta==2){
      opreste_poarta();
      starePoarta=1;
      stareVechePoarta=0;
    }
    
  }
  if(time1==milli){
    opreste_poarta();
    starePoarta=stareVechePoarta; 
     
  }
}
