//****************************   SPECIAL CASES *******************************************************************************

//------------------------  dotted lines special ------------------------------------
void dotted()
{
    qtrRead();
    if(dval[0]==0 && dval[1]==0 && dval[2]==0 && dval[3]==0 && dval[6]==0 && dval[7]==0 && dval[4]==0 && dval[5]==0)
    {
      go(100,200);
      brake();

    }
}



//=====Getting onto the line using PID========  ( GO ON THE CORRECT PATH)

void ontoLine(int val)
{
  forward();
  for (int i = 0; i < val; i++) PID(200);
  brake();
}

void ontoLineR(int val)
{
  back();
  for (int i = 0; i < val; i++) PIDB(200);
  brake();
}


//============special reverse-------------------------

void revtoLine(int val)
{
  for (int i = 0; i < val; i++) 
  {
    back(200,200);
    delay(2.5);
  }
  brake();
}

//===============special case bridge1=================
void bridge()
{
  while(1)
  {   
    qtrRead();
     if(dval[0]==0 && dval[7]==0 && dval[4]==0 && dval[5]==0)
     {
      go(630,150);
      brake();
      break;
     }
     else 
     {
      PID(200);
      forward();
     }
  }
}

void cage()
{
  leftturns=leftturns+1;  
  while(1)
  {
    qtrRead();    
    if(dval[7]==1 && dval[6]==1 && dval[5]==1 && dval[4]==1)
    { 
      brake();
      delay(250);
      go(120,180);
      lastError=0;
      break;
    }
    else{
      PID(200);
      forward();
    }
  }}
    




//===================special case with damn T junction =======================
void faketurn()
{
  while(1)
  {   
    qtrRead();
    if((dval[0]==1) && (dval[7]==1))
    {
      go(150,150);
      break;
    }
    else 
    {
      PID(200); 
      forward();  
    }
  }
}

//------------------------bridge passing--------------------------------------

void dead(int count)
{
  int deadcount=0;
  while(1)
  {
    
    qtrRead();
    if(dval[0]==1 && dval[7]==1)
    {
      brake();
      break;
    } 
    else
    {
       
        deadcount=deadcount+1;
        
        if(deadcount>=count)
        {
         PID(100);
         forward();
        } 
        else{
            PID(200);
        forward(); 
        }
      }

    }
  }

//-----------------------------detecting the objects----------------
QuickStats stats;
void detect1()
{
  float cm1;
  float values1[100];
  long duration1;
  for(int i=0;i<100;i++)
  {
  
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  values1[i] = microsecondsToCentimeters(duration1);  
  Serial.println(values1[i]);
  }
  cm1=stats.mode(values1,80,1);
  Serial.print("average =  ");
  Serial.println(cm1);
  delay(500);
  
  float cm2;
  float values2[100];
  long duration2;
  for(int i=0;i<100;i++)
  {
  
  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);

  values2[i] = microsecondsToCentimeters(duration2);
 Serial.println(values2[i]);
  }
  cm2=stats.mode(values2,80,1);
  Serial.print("average =  ");
  Serial.println(cm2);
  delay(500);

  float cm3;
  float values3[100];
  long duration3;
  for(int i=0;i<100;i++)
  {
  pinMode(trigPin3, OUTPUT);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  pinMode(echoPin3, INPUT);
  duration3 = pulseIn(echoPin3, HIGH);

  values3[i] = microsecondsToCentimeters(duration3);
  Serial.println(values3[i]);
 }
  cm3=stats.mode(values3,80,1);
  Serial.print("average =  ");
  Serial.println(cm3);
  delay(500);
if(cm1==cm3+1 || cm1==cm3-1 || cm1==cm3)
{
  object1=1;// cylinder
}
else if((cm1!=cm3) && (cm3!=cm2) && (cm3>=(cm2+3)))
{
  object1=4; //sphere
}
else if((cm1==cm2) && (cm3>cm2))
{
  object1=3;//cube
}

else if(cm1<cm3)
{
  object1=2; // pyramid
}
else
{
  object1=3;//cube
}

}
//-----------------------------------------------------------------------------------


void detect2()
{
  float cm1;
  float values1[100];
  long duration1;
  for(int i=0;i<100;i++)
  {
  
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  values1[i] = microsecondsToCentimeters(duration1);  
  Serial.println(values1[i]);
  }
  cm1=stats.mode(values1,100,1);
  Serial.print("average =  ");
  Serial.println(cm1);
  delay(500);
  
  float cm2;
  float values2[100];
  long duration2;
  for(int i=0;i<100;i++)
  {
  
  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);

  values2[i] = microsecondsToCentimeters(duration2);
 Serial.println(values2[i]);
  }
  cm2=stats.mode(values2,100,1);
  Serial.print("average =  ");
  Serial.println(cm2);
  delay(500);

  float cm3;
  float values3[100];
  long duration3;
  for(int i=0;i<100;i++)
  {
  pinMode(trigPin3, OUTPUT);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  pinMode(echoPin3, INPUT);
  duration3 = pulseIn(echoPin3, HIGH);

  values3[i] = microsecondsToCentimeters(duration3);
  Serial.println(values3[i]);
 }
  cm3=stats.mode(values3,100,1);
  Serial.print("average =  ");
  Serial.println(cm3);
  delay(500);
if(cm1==cm3+1 || cm1==cm3-1 || cm1==cm3)
{
  object2=1;// cylinder
}
else if((cm1!=cm3) && (cm3!=cm2) && (cm3>=(cm2+3)))
{
  object2=4; //sphere
}
else if((cm1==cm2) && (cm3>cm2))
{
  object2=3;//cube
}

else if(cm1<cm3)
{
  object2=2; // pyramid
}
else
{
  object2=3;//cube
}

}





//==================================================================================



  
  

//------------------grabbing the object----------------------------------

void grab()
{
if(object1==2)  
{ ontoLineR(110);
   delay(100);
   ontoLine(70);
   delay(500);
   servo1.write(112);
  delay(2000);
  servo2.write(0);
  delay(1000);
  servo1.write(0);}
else if(object1==3)  
{ontoLineR(110);
   delay(100);
   ontoLine(30);
   delay(500);
   servo1.write(112);
  delay(2000);
  servo2.write(16);
  delay(1000);
  servo1.write(0);}
else if(object1==1)  
{ontoLineR(110);
   delay(100);
   ontoLine(30);
   delay(500);
   servo1.write(112);
  delay(2000);
  servo2.write(20);
  delay(1000);
  servo1.write(0);}
else if(object1==4)  
{ontoLineR(100);
   delay(100);
   ontoLine(60);
   delay(500);
  servo1.write(112);
  delay(2000);
  servo2.write(18);
  delay(1000);
  servo1.write(0);
  }

}
//----------------------scanning----------------------------------
void scan()
{
  for(int i=0;i<3;i++)
  {
    detect2();
   
    if((object1==object2) && (i==0))
      {
    delay(500);
    grab();
    delay(750);
    turn180();
    dotted();
    cage();
    break;
    }
    else if((object1!=object2) && (i==0))
    {
      delay(500);
      turn180();
      dotted();
      left90();
      dotted();
      left90();
      dotted();
      deadend();
      ontoLine(25);
    }
    else if((object1==object2) && (i==1))
    {
     delay(500);
    grab();
    delay(750);
    turn180();
    dotted();
    right90();
    dotted();
    left90();
    break;
    }
    else if((object1!=object2) && (i==1))
    {
      delay(500);
      turn180();
      dotted();
      left90();
      dotted();
      left90();
      dotted();
      deadend();
      ontoLine(25);
    }
    
    else if((object1==object2) && (i==2))
   {
  delay(500);
   grab();
   delay(750);
   turn180();
   dotted();
   right90();

    dotted();
    left90();
    break;
    }


    else if((object1!=object2) && (i==2))
    {
      delay(500);
      turn180();
       dotted();
      left90();
      dotted();
      left90();
      dotted();
      deadend();
      ontoLine(25);
    }
    else
    {
    delay(500);
    grab();
    delay(750);
    turn180();
    dotted();
    right90();
    dotted();
    left90();
    break;
    }
  }
}







//==================move with turns===================

void go(unsigned int turns, int Speed)
{
  leftCount=0;
  rightCount=0;
  analogWrite(motorL_PWM,Speed);
  analogWrite(motorR_PWM,Speed);
  while(leftCount<turns || rightCount<turns){
    
    if(leftCount<turns) Lforward();
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<turns) Rforward();
    else{
      digitalWrite(motorR_dirP,HIGH);
      digitalWrite(motorR_dirN,HIGH);
    }
  }
  brake();
  delay(50);
  
  leftCount=0;
  rightCount=0;
}


void reverse(unsigned int turns, int Speed)
{
  brake();
  delay(50);
  leftCount=0;
  rightCount=0;
  analogWrite(motorL_PWM,Speed);
  analogWrite(motorR_PWM,Speed);
  while(leftCount<turns || rightCount<turns){
    
    if(leftCount<turns)Lbackward();
    
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<turns) Rbackward();
    else{
      digitalWrite(motorR_dirP,HIGH);
      digitalWrite(motorR_dirN,HIGH);
    }
  }
  
  brake();
  delay(50);
  
  leftCount=0;
  rightCount=0;
}


//--------------------------reverse pid---------------------------------------



void revpid(unsigned int turns)
{
  brake();
  delay(50);
  leftCount=0;
  rightCount=0;
  while(leftCount<turns || rightCount<turns){
    PID(200);
    
    if(leftCount<turns)Lbackward();
    
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<turns) Rbackward();
    else{
      digitalWrite(motorR_dirP,HIGH);
      digitalWrite(motorR_dirN,HIGH);
    }
  }
  
  brake();
  delay(50);
  
  leftCount=0;
  rightCount=0;
}

//---------------------- go pid ---------------------


void gopid(unsigned int turns)
{
  brake();
  delay(50);
  leftCount=0;
  rightCount=0;
  while(leftCount<turns || rightCount<turns){
    PID(200);
    
    if(leftCount<turns)Lforward();
    
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<turns) Rforward();
    else{
      digitalWrite(motorR_dirP,HIGH);
      digitalWrite(motorR_dirN,HIGH);
    }
  }
  
  brake();
  delay(50);
  
  leftCount=0;
  rightCount=0;
}

//=================================================================================================================



long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
