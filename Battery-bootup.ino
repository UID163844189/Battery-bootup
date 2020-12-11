const int button = 11;
const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(button, INPUT);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);

	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
}

void bootup()
{
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	Serial.println("press for bootup");

#pragma region 长按开机的过程
	for (int i = 0; i < 32767; i += 1)
	{
		if (digitalRead(button) == LOW)
			return;
	}
	digitalWrite(led1, HIGH);
	for (int i = 0; i < 32767; i += 1)
	{
		if (digitalRead(button) == LOW)
			return;
	}
	digitalWrite(led2, HIGH);
	for (int i = 0; i < 32767; i += 1)
	{
		if (digitalRead(button) == LOW)
			return;
	}
	digitalWrite(led3, HIGH);
	for (int i = 0; i < 32767; i += 1)
	{
		if (digitalRead(button) == LOW)
			return;
	}
	digitalWrite(led4, HIGH);
	for (int i = 0; i < 32767; i += 1)
	{
		if (digitalRead(button) == LOW)
			return;
	}
#pragma endregion

	Serial.println("bootup");
	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);
	digitalWrite(led3, HIGH);
	digitalWrite(led4, LOW);
	for (; digitalRead(button) == HIGH;) //长按开机之后等待释放
		;
}

void loop()
{
	// put your main code here, to run repeatedly:
	if (digitalRead(button) == HIGH)
	{
		Serial.println("press");
		digitalWrite(led1, HIGH);
		digitalWrite(led2, HIGH);
		digitalWrite(led3, HIGH);
		digitalWrite(led4, LOW);
		//for (bool released = false; digitalRead(button) == LOW; );
		for (;;) //检测电量时等待释放
		{
			if (digitalRead(button) == LOW)
			{
				Serial.println("released");
				break;
			}
		}

		for (unsigned int i = 0; i < 32767; i += 1) //释放后如果再按下，就进入长按启动
		{
			delayMicroseconds(100);
			if (digitalRead(button) == HIGH)
			{
				bootup();
				digitalWrite(led1, LOW);
				digitalWrite(led2, LOW);
				digitalWrite(led3, LOW);
				digitalWrite(led4, LOW);
				break;
			}
		}
		digitalWrite(led1, LOW);
		digitalWrite(led2, LOW);
		digitalWrite(led3, LOW);
		digitalWrite(led4, LOW);
	}
	else
	{
		digitalWrite(led1, LOW);
		digitalWrite(led2, LOW);
		digitalWrite(led3, LOW);
		digitalWrite(led4, LOW);
	}

	//Serial.println("start up");
}
