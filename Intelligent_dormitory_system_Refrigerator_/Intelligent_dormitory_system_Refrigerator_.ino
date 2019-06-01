#include <SoftwareSerial.h>
#define LED_OUT 2

//使用软件串口，能讲数字口模拟成串口
SoftwareSerial BT(8, 9);  //新建对象，接收脚为1，发送脚为0

char val;  //存储接收的变量

void setup() {
	Serial.begin(9600);   //与电脑的串口连接
	Serial.println("BT is ready!");
	BT.begin(115200);  //设置波特率
	pinMode(LED_OUT, OUTPUT);
	digitalWrite(LED_OUT, LOW);
}

void loop() {
	//如果接收到蓝牙模块的数据，输出到屏幕
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