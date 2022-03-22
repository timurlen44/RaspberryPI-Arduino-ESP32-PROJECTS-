#include<stdio.h>
#include<wiringPi.h>
const int Pin = 12;
int main(void)
{
    wiringPiSetupGpio();
    pinMode(Pin,PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
    int pulse = 0;
    while(1)
    {
    printf("Please Enter Pulse Between 40 and 260: ");
    scanf("%d",&pulse);
    getchar();
    pwmWrite(Pin,pulse);
    }
    return 0;
}
