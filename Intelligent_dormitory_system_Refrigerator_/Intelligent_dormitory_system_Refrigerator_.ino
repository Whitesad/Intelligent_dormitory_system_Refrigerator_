#include <SoftwareSerial.h>

/*************Define Variable****************/
#define LED_OUT 2
#define LM35_PIN 5

#define PinA1 13
#define PinA2 12
#define PinB1 11
#define PinB2 10

#define RX_BLZ 8
#define TX_BLZ 9

/*************Glonal Variable****************/
//使用软件串口，能将数字口模拟成串口
SoftwareSerial BT(RX_BLZ, TX_BLZ);  //新建对象，接收脚为1，发送脚为0

/*************Initialize****************/
void InitialBluetooth() {
	Serial.println("BT is ready!");
	BT.begin(9600);  //设置波特率
}
void InitialLM35() {

}
void InitialL298N() {
	pinMode(PinA1, OUTPUT);
	pinMode(PinA2, OUTPUT);
	pinMode(PinB1, OUTPUT);
	pinMode(PinB2, OUTPUT);


	digitalWrite(PinA1, HIGH);
	digitalWrite(PinA2, LOW);
	digitalWrite(PinB1, HIGH);
	digitalWrite(PinB2, LOW);

	analogWrite(PinA1, 100);
	analogWrite(PinA2, 100);
	analogWrite(PinB1, 100);
	analogWrite(PinB2, 100);


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
	InitialL298N();
}

void loop() {
	int tem = GetTemperature();
	if (BT.available()) {
		Serial.println("ok");
	}
	delay(10);
}

//10.175.196.1