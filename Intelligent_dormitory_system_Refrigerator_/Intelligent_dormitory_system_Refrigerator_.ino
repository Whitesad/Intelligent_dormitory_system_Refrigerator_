#include <SoftwareSerial.h>
#define LED_OUT 2

//ʹ��������ڣ��ܽ����ֿ�ģ��ɴ���
SoftwareSerial BT(8, 9);  //�½����󣬽��ս�Ϊ1�����ͽ�Ϊ0

char val;  //�洢���յı���

void setup() {
	Serial.begin(9600);   //����ԵĴ�������
	Serial.println("BT is ready!");
	BT.begin(115200);  //���ò�����
	pinMode(LED_OUT, OUTPUT);
	digitalWrite(LED_OUT, LOW);
}

void loop() {
	//������յ�����ģ������ݣ��������Ļ
	if (BT.available())
	{
		char a, ch;
		char num[8];
		a = BT.read();
		Serial.print(a);
		if (a == '{')
		{
			char p = 0;

			ch = BT.read();
			BT.read();

			while (BT.available())
			{
				num[p++] = BT.read();
			}
			num[--p] = '\0';
			float nu = atol(num);
		}
		switch (a)
		{
		case 'Z':digitalWrite(LED_OUT, HIGH); break;
		default:digitalWrite(LED_OUT, LOW); break;
		}
	}
}

//10.175.196.1