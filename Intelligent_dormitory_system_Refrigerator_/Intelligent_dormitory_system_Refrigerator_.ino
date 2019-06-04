#include <SoftwareSerial.h>

/*************Define Variable****************/
#define LED_OUT 2
#define LM35_PIN 5

/*************Glonal Variable****************/
//ʹ��������ڣ��ܽ����ֿ�ģ��ɴ���
SoftwareSerial BT(8, 9);  //�½����󣬽��ս�Ϊ1�����ͽ�Ϊ0

/*************Initialize****************/
void InitialBluetooth() {
	Serial.println("BT is ready!");
	BT.begin(9600);  //���ò�����
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
	Serial.begin(9600);   //����ԵĴ�������
	InitialBluetooth();
}

void loop() {
	int tem = GetTemperature();
	Serial.print(tem);
	Serial.println("C");
	delay(10);
}

//10.175.196.1