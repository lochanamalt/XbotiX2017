//=====================Coming to Junctions=======================


//Coming to the juction and turn left

int leftturns=0;
int rightturns=0;

void left90()
{
  leftturns=leftturns+1;  
  while(1)
  {
    qtrRead();    
    if(dval[7]==1 && dval[6]==1 && dval[5]==1 && dval[4]==1)
    { 
      brake();
      delay(250);
      turnLeft90();
      lastError=0;
      break;
    }
    
    else{
            
          if(((leftturns==4) || (leftturns==1)) && (btnstate2==LOW) )
          {
            forward();
            PID(150);
          }
          else if((leftturns==5)&& (btnstate2==LOW))
          {
            forward();
            PID(120);
          }
          else
          {
            forward();
            PID(200);
          }
        } 
  
}}

//Coming to the juction and turn right

void right90()
{
  rightturns=rightturns+1;
  while(1)
  {
    qtrRead();
    if(dval[0]==1 && dval[1]==1 && dval[2]==1 && dval[3]==1)
    {    
      brake();
     delay(250);
      turnRight90();
      lastError=0;
      break;
    }
    else 
    {
       if((rightturns==6) && (btnstate2==LOW))
      {
        forward();
        PID(120);
      }
      else
      {
         PID(200);
         forward();
         
      }
      }     
   }
  }

//Coming to the T the juction------------------------

void deadend()
{
  while(1)
  {
    
    qtrRead();
    if(dval[0]==1 && dval[7]==1)
    {
      brake();
      break;
    } 
    else{
        PID(200);
        forward();       
      }

    }
  }

//=====================================================================================

//turning 90 degrees to the left

void turnLeft90()
{
  leftCount=0;
  rightCount=0;
  analogWrite(motorL_PWM,150);
  analogWrite(motorR_PWM,150);
  while(leftCount<100 || rightCount<900)   // test countings
  {
    if(leftCount<100) Lforward();
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<900) Rforward();
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
//****************   turning 90 degrees to the right   ********************

void turnRight90()
{
  leftCount=0;
rightCount=0;
  analogWrite(motorL_PWM,150);
  analogWrite(motorR_PWM,150);
  while(leftCount<900 || rightCount<100)   // test countings
  {
    if(leftCount<900) Lforward();
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<100) Rforward();
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
//***************   turning 180 degrees  *********************

void turn180()
{
  leftCount=0;
  rightCount=0;
  analogWrite(motorL_PWM,150);
  analogWrite(motorR_PWM,150);
  while(leftCount<720 || rightCount<720)
  {
    if(leftCount<720)
    {
      Lforward();
    }
    else{
      digitalWrite(motorL_dirP,HIGH);
      digitalWrite(motorL_dirN,HIGH);
    }
    if(rightCount<720)
    {
      Rbackward();
    }
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

