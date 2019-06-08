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

#define TARGET_TEM_CD 2000
/*************Glonal Variable****************/
//使用软件串口，能将数字口模拟成串口
SoftwareSerial BT(RX_BLZ, TX_BLZ);  //新建对象，接收脚为1，发送脚为0
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int Current_Tem = 0;
int Target_Tem = 10;
bool isCurrentShow = true;
int TargetShowCD = 0;
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
}

void Initial1602A() {
	lcd.begin(16, 2);
	lcd.print("Current Tem");
}

void InitialCurrentTem() {
	lcd.setCursor(0, 0);
	lcd.print("           ");
	lcd.setCursor(0, 0);
	lcd.print("Current Tem");
}
void InitialTargetTem() {
	TargetShowCD = 0;
	lcd.setCursor(0, 0);
	lcd.print("           ");
	lcd.setCursor(0, 0);
	lcd.print("Target Tem");
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
	analogWrite(PinA1, 0);
	analogWrite(PinB2, pwm);
	return;
}

float P = 51;
void Kernel() {
	Current_Tem = GetTemperature();
	int PWM = P * (Current_Tem - Target_Tem);
	if (PWM >= 255) {
		PWM = 255;
	}
	else if (PWM <= 0) {
		PWM = 0;
	}
	SetPwm(PWM);
	delay(10);
}
void ShowCurretTem() {
	lcd.setCursor(0, 1);
	lcd.print(Current_Tem);
	lcd.print("C");
}
void ShowTargetTem() {
	lcd.setCursor(0, 1);
	lcd.print(Target_Tem);
	lcd.print("C");
}
void BluzDebug() {
	if (Serial.available())
		BT.write(Serial.read());
	//把hc-05的串口输出的字符 输出到电脑串口中
	if (BT.available())
		Serial.write(BT.read());
}
void setup() {
	Serial.begin(9600);   //与电脑的串口连接
	InitialLM35();
	InitialBluetooth();
	Initial1602A();
	InitialL298N();

	MsTimer2::set(5, Kernel);
	MsTimer2::start();
}
char ch;

void loop() {
	if (BT.available())
	{
		ch = BT.read();
		//Serial.print(a);
		while (BT.available())
			BT.read();
		switch (ch)
		{
		case 'U':
			InitialTargetTem();
			if (Target_Tem <= 15)
				Target_Tem++;
			isCurrentShow = false;
			Serial.println("U");
			break;
		case 'D':
			InitialTargetTem();
			if (Target_Tem >= 5)
				Target_Tem--;
			isCurrentShow = false;
			Serial.println("D");
			break;
		}
	}
	if (isCurrentShow)
		ShowCurretTem();
	else {
		ShowTargetTem();
		TargetShowCD += 2;
		if (TargetShowCD >= TARGET_TEM_CD) {
			TargetShowCD = 0;
			isCurrentShow = true;
			InitialCurrentTem();
		}
	}
	delay(1);
}

//10.175.196.1