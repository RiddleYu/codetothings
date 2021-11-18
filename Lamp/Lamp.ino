#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET

#include <Blinker.h>
#include<Servo.h>


char auth[] = "83ad02eb82ad";      //Blinker申请到的密钥
char ssid[] = "Apple";             //设备将要连入的wifi（2.4GHz）的名称
char pswd[] = "2528184787";       //wifi密码

bool oState = false;
Servo servoA;

void doAction(const String & state) 
{
  BLINKER_LOG("doAction : ", state);
  if(state == BLINKER_CMD_ON) 
    {
    BLINKER_LOG("开关 开了");
    servoA.write(130);      // 舵机角度写入
    delay(200);//延时0.2s
    } else if(state == BLINKER_CMD_OFF)
      {
        BLINKER_LOG("开关 关了");
        servoA.write(0);       // 舵机角度写入                   
        delay(200);
      }
}
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);
    if (state == BLINKER_CMD_ON)
    {
        digitalWrite(LED_BUILTIN, LOW);
        doAction(state);
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) 
    {
        digitalWrite(LED_BUILTIN, HIGH);
        doAction(state);
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
        oState = false;
    }
}
void miotQuery(int32_t queryCode)
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("MIOT Query All");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("MIOT Query Power State");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
    }
}
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}
void setup()
{
    Serial.begin(9600);
    BLINKER_DEBUG.stream(Serial);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    servoA.attach(D0);
    
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
    doAction("off");
}
void loop()
{
    Blinker.run();
}
