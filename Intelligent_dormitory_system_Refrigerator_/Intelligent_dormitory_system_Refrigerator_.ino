#include <SoftwareSerial.h>

/*************Define Variable****************/
#define LED_OUT 2
#define LM35_PIN 5

/*************Glonal Variable****************/
//使用软件串口，能将数字口模拟成串口
SoftwareSerial BT(8, 9);  //新建对象，接收脚为1，发送脚为0

/*************Initialize****************/
void InitialBluetooth() {
	Serial.println("BT is ready!");
	BT.begin(9600);  //设置波特率
	pinMode(LED_OUT, OUTPUT);
	digitalWrite(LED_OUT, LOW);
}
int InitialLM35(){
	
}

/*************Function****************/
int GetTemperature() {
	int val;
	int dat;
	val = analogRead(LM35_PIN);
	dat = (125 * val) >> 8;
	return dat;
}




void setup() {
	Serial.begin(9600);   //与电脑的串口连接
	InitialBluetooth();
}

void loop() {
	int tem = GetTemperature();
	Serial.print(tem);
	Serial.println("C");
	delay(10);
}

//10.175.196.1