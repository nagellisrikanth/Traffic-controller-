int Led = 13 ;// define LED Interface
int buttonpin = 4; // define the flame sensor interface
int analoog = A3; // define the flame sensor interface
int count=0; // define the counter variable 
const int nvariable=60; // Fixing the counter variable to 60 
bool val ;// define numeric variables val
float sensor; //read analoog value
void sigR(); //Read state 
void sigG(); // Green state 
void pending(); //Pending state 
void sigY(); // Yellow state 

void setup() 
{
// put your setup code here, to run once:
pinMode (Led, OUTPUT) ; // define LED as output interface
pinMode (buttonpin, INPUT) ; // output interface defines the flame sensor
pinMode (analoog, INPUT) ;// output interface defines the flame sensor
Serial.begin(9600);// To begin the serial communication 
}

void loop() 
{
// calling the Red state 
sigR ();
}

//Red state 
void sigR()
{
for(count=1;;count++) // stay in the red state till 60 seconds
{

Serial.print("Red State-->"); // printing Red state on the serial monitor
Serial.println(count);
delay(300);
digitalWrite(Led,HIGH);
if(count>=nvariable)
{
  sigG(); // we switch to green state 
}
}
}

//Green state
void sigG()
{
for(count=1;;count++)  // stay in the Green state till the pedestrian requests a signal 
{
digitalWrite(Led,HIGH);
delay(100);
digitalWrite(Led,LOW);
delay(100);
Serial.print("Green State-->"); // printing Green state on the serial monitor
Serial.println(count);
delay(300);
sensor = analogRead(analoog);    
val = digitalRead (buttonpin);  // reading the pedestrian request;
if((val==1)&&(count<nvariable))  // If there is a  pedestrain request and counter value is less then 60 switch to pending state 
{
Pending();
}
if ((val==1)&&(count >=nvariable))  // If there is a  pedestrain request and counter value is greater then 60 switch to yellow state 
{
  digitalWrite(Led,HIGH);       
 sigY();
}  
}
}

//pending  state
void Pending()
{
for(count=1;;count++)  // stay in state till the counter value is less than 60 
{
if(count >nvariable) // here check for the counter value if its greater then 60 we switch to yellow state 
{
  sigY();
}
Serial.print("Pending State-->");  // printing pending state on the serial monitor 
Serial.println(count);
delay (300);
}
}


//yellow state
void sigY()
{
for(count =1;;count++) 
{
if(count >5)   // here check for the counter value if its greater then 5 we switch to Red state
{
sigR();
}
Serial.print("Yellow state-->");// printing yellow state on the serial monitor 
Serial.println(count);
delay(300);
}
}


