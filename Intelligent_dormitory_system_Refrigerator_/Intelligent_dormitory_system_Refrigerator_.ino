#include <SoftwareSerial.h>
#define LED_OUT 2

//ʹ��������ڣ��ܽ����ֿ�ģ��ɴ���
SoftwareSerial BT(8, 9);  //�½����󣬽��ս�Ϊ1�����ͽ�Ϊ0

char val;  //�洢���յı���

void setup() {
	Serial.begin(9600);   //����ԵĴ�������
	Serial.println("BT is ready!");
	BT.begin(9600);  //���ò�����
	pinMode(LED_OUT, OUTPUT);
	digitalWrite(LED_OUT, LOW);
}

void loop() {
	//������յ�����ģ������ݣ��������Ļ
	if (BT.available())
	{
		digitalWrite(LED_OUT, HIGH);
	}

}

//10.175.196.1