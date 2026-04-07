#include "Door.h"

void beep(char a)
{
    for (int i = 0; i < a; i++)
    {
        digitalWrite(15, HIGH);
        delay(100);
        digitalWrite(15, LOW);
        delay(100);
    }
}
void lbeep(char a)
{
    digitalWrite(15, HIGH);
    delay(a);
    digitalWrite(15, LOW);
}

void Open_door(int a, int t)
{
    if (a == -1)
        return;
    else if (a)
    {
        u8g2.clearBuffer();
        u8g2.drawXBMP(33, 20, 16, 16, str57); // 正在开门
        u8g2.drawXBMP(49, 20, 16, 16, str58);
        u8g2.drawXBMP(65, 20, 16, 16, str0);
        u8g2.drawXBMP(81, 20, 16, 16, str1);
        u8g2.sendBuffer();                   // 开显示
        err = 0;
        digitalWrite(4, HIGH);
        beep(2);
        delay(t);
        digitalWrite(4, LOW);
    }
    else
    {
        err++;
    }
}