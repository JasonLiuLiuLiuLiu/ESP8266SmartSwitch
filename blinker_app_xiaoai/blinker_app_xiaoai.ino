#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET   //小爱同学

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Blinker.h>

char auth[] = "2cf492755d68";  //设备key
char ssid[] = "2.4";  //路由器wifi ssid
char pswd[] = "12345678";  //路由器wifi 密码

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyOn[] = "On";  // a reply string to send back
char  replyOff[] = "Off";  // a reply string to send back

BlinkerButton ButtonOn("btn-on");     //定义按钮键名
BlinkerButton ButtonOff("btn-off");     //定义按钮键名
bool oState = false;
int counter = 0;
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {     //小爱同学控制开命令 此处修改为点动模式，适合按钮操作，
        //digitalWrite(0, LOW);
        //delay(200);
        digitalWrite(0, LOW);
        BlinkerMIOT.powerState("on");

        BlinkerMIOT.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) {   //小爱同学控制关命令 此处修改为点动模式，适合按钮操作，
        digitalWrite(0,HIGH);
        //delay(200);
        //digitalWrite(0, LOW);
        BlinkerMIOT.powerState("off");

        BlinkerMIOT.print();

        oState = false;
    }
}

void miotQuery(int32_t queryCode)      //小爱同学控制
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

void dataRead(const String & data)      // 如果未绑定的组件被触发，则会执行其中内容
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}

void button1_on(const String & state)     //点灯app内控制按键触发
{
    BLINKER_LOG("get button state: ", state);
    //digitalWrite(0,LOW);
    //delay(200);
    digitalWrite(0, LOW);
    oState = true;
}

void button1_off(const String & state)     //点灯app内控制按键触发
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(0,HIGH);
    //delay(200);
    //digitalWrite(0, LOW);
    oState = false;
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(0, OUTPUT);              //定义io口为输出
    digitalWrite(0,LOW);           //定义io默认为高电平

    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" connected");

    Udp.begin(localUdpPort);
    Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
    ButtonOn.attach(button1_on);      
    ButtonOff.attach(button1_off);      
}

void loop()
{
    int packetSize = Udp.parsePacket();
    
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        Serial.printf("UDP packet contents: %s\n", incomingPacket);
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        if(len==2) // 开 on
        {
          digitalWrite(0,LOW);
          oState = true;
          Udp.write(replyOn);
        }else if(len==3) //关 off
        {
           digitalWrite(0,HIGH);
           oState = false;
           Udp.write(replyOff);
        }
        incomingPacket[len] = 0;
        
        Udp.endPacket();
      }
    }
    
    Blinker.run();
}
