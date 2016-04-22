#define  F_CPU 1000000UL
#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include <util/delay.h>
#include <math.h>

#define KEYPAD_PORT PORTB
#define KEYPAD_DDR 	DDRB
#define KEYPAD_PIN 	PINB
#define dl _delay_ms
#define PI acos(-1.0)
#define RAD_TO_DEG 180/PI
#define end while(1);

#include "mpu6050/mpu6050.h"
#include "lcd/lcd.h"
#include "lcd/lcd.c"

//void mpu6050_getRawData(int16_t*, int16_t*, int16_t*, int16_t*, int16_t*, int16_t*);
void mpu6050_getConvData(double*, double*, double*);//, double*, double*, double*);
int GetKeyPressed(void);
void display(unsigned char row, unsigned char col);
int get_key(void);
void fun(double x);
char line[21];
int m, n;
unsigned char sgn;
int main(void)
{
    sei();
	LCDInit();
    mpu6050_init();
    _delay_ms(100);
    LCDClear();
    sprintf(line, "**Tilt Detector**");
    display(1, 1);
    sprintf(line, "Enter Length in cm: ");
    display(2, 1);
    double axg = 0;
    double ayg = 0;
    double azg = 0;
    int ma, na, md, nd, l = 0, in = 0;
    unsigned char sa, sd;
    double a, d;
    sprintf(line, "0");
    display(3, 1);
    while(1)
    {
        in = get_key();
        if(in == 255)
            continue;
        dl(150);
        if(in == -2)
        {
            dl(200);
            break;
        }
        if(in == -1)
        {
            dl(200);
            l = l / 10;
        }
        else
        {
            l = l * 10 + in;
        }
        sprintf(line, "%d", l);
        display(3, 1);
    }
	LCDClear();
    sprintf(line, "Tilt angle: ");
    display(1, 1);
    sprintf(line, "Difference: ");
    display(3, 1);
    while(1)
    {
        mpu6050_getConvData(&axg, &ayg, &azg);
        a = 2.0 + (RAD_TO_DEG * atan(ayg / sqrt(axg * axg + azg * azg)));
        //a = atan2(-ayg,-azg)*57.2957795+180.0;
        d = (double)(l * 1.0) * sin(a * PI / 180.0);
        fun(a);
        sa = sgn == 0 ? '+' : '-';
        ma = m;
        na = n;
        fun(d);
        sd = sgn == 0 ? '+' : '-';
        md = m;
        nd = n;
        sprintf(line, "%c%d.%d degree", sa, ma, na);
		LCDGotoXY(1, 2);
		LCDString(line);
        sprintf(line, "%c%d.%d cm", sd, md, nd);
        LCDGotoXY(1, 4);
        LCDString(line);
        _delay_ms(500);
    }
    //a = (atan2 (ayg, azg) + PI) * RAD_TO_DEG;
    return 0;
}
int GetKeyPressed(void)
{
    int r, c;
    KEYPAD_PORT|= 0X0F;
    for(c = 0; c < 3; ++c)
    {
        KEYPAD_DDR &= (~( 0X7F ));
        KEYPAD_DDR |= (0X40 >> c);
        for(r = 0; r < 4; ++r)
        {
            if(r == 0)
            {
                if(!(KEYPAD_PIN & (0X08 >> r)))
                {
                    return (r * 3 + c);
                }
            }
            else
            {
                if(!(KEYPAD_PIN & (0X08 >> r)))
                {
                    return (r * 3 + c);
                }
            }
        }
    }
    return 0XFF;
}
int get_key(void)
{
    int key = GetKeyPressed();
    if(key < 9)
        return key + 1;
    if(key == 10)
        return 0;
    if(key == 9)
        return -1;
    if(key == 11)
        return -2;
    return 0XFF;
}
void display(unsigned char row, unsigned char col)
{
    LCDGotoXY(col, row);
    LCDString(line);
}
void fun(double x)
{
    sgn = 0;
    if(x < 0.0)
    {
        x = -x;
        sgn = 1;
    }
    m = x;
    n = (x - m) * 100;
}
