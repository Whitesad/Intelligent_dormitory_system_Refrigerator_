#include <SoftwareSerial.h>
//ʹ��������ڣ��ܽ����ֿ�ģ��ɴ���
SoftwareSerial BT(1, 0);  //�½����󣬽��ս�Ϊ1�����ͽ�Ϊ0
char val;  //�洢���յı���

void setup() {
	Serial.begin(9600);   //����ԵĴ�������
	Serial.println("BT is ready!");
	BT.begin(9600);  //���ò�����
}

void loop() {
	//������ڽ��յ����ݣ����������������
	if (Serial.available()) {
		val = Serial.read();
		BT.print(val);
	}

	//������յ�����ģ������ݣ��������Ļ
	if (BT.available()) {
		val = BT.read();
		Serial.print(val);
		//
	}
}