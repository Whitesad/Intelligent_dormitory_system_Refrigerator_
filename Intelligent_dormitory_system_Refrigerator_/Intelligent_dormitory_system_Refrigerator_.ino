#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <MsTimer2.h>
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
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int Current_Tem = 0;
int Target_Tem = 30;
bool isCurrentShow = true;
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

void Initial1602A() {
	lcd.begin(16, 2);
	lcd.print("Current Tem");
}

/*************Function****************/
int GetTemperature() {
	int val;
	int dat;
	val = analogRead(LM35_PIN);
	dat = (125 * val) >> 8;
	return dat;
}

void SetPwm(int pwm) {
	return;
	analogWrite(PinA1, pwm);
	analogWrite(PinB1, pwm);
}

float P = 51;
void Kernel() {
	Current_Tem = GetTemperature();
	int PWM = P * (Current_Tem - Target_Tem);
	SetPwm(PWM);
	delay(10);
}
void UpdateTem() {
	if (isCurrentShow) {
		lcd.setCursor(0, 1);
		lcd.print(Current_Tem);
		lcd.print("C");
	}
}

void setup() {
	Serial.begin(9600);   //与电脑的串口连接
	InitialLM35();
	InitialBluetooth();
	Initial1602A();

	MsTimer2::set(5, Kernel);
	MsTimer2::start();
	//InitialL298N();
}

void loop() {
	if (BT.available()) {
		isCurrentShow = false;
		lcd.setCursor(0, 0);
		lcd.print("           ");
		lcd.setCursor(0, 0);
		lcd.print("Target Tem");
		lcd.setCursor(0, 1);
		lcd.print(Target_Tem);
		lcd.print("C");
	}
	UpdateTem();
	delay(1);
}

//10.175.196.1