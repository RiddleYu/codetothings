const int TrigPin = 2; 
const int EchoPin = 3; 
float cm;
int YellowPin = 7;
int GreenPin=8;
int RedPin=9;
void setup()
{ Serial.begin(9600); 
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(GreenPin,OUTPUT);
  pinMode(RedPin,OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop()
{ digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm
  cm = (int(cm * 100)) / 100; //保留两位小数
  if (cm < 10)
    {digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);
    }
  else if (cm > 10 && cm < 50)
    { digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
    }
  else if (cm > 50)
     {  digitalWrite(13, HIGH);
        delay(10);
        digitalWrite(13, LOW);
     }
   if(cm>50)//亮绿灯，蜂鸣器不工作
      {
       digitalWrite(GreenPin,HIGH);
       delay(1000);
       digitalWrite(GreenPin,LOW);
       delay(1000);                                                                                                                                        
       }
   else if(cm>10)//亮黄灯，蜂鸣器间歇工作
   {
    digitalWrite(YellowPin,HIGH);
     delay(7*cm);
  digitalWrite(YellowPin,LOW);
   }
   else
   {
     digitalWrite(RedPin,HIGH);
     delay(12*cm);
  digitalWrite(RedPin,LOW);
    }
 delay(10);
  Serial.print(cm);
  Serial.print("cm");//串口输出
  Serial.println();
}
