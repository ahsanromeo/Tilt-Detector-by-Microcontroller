
#include "lcd.h"


void LCDSendCmd4BIT(unsigned char ucCmd)
{

    if(ucCmd&0x01) LCD_DATA_PORT |= (1<<LCD_D4);
    else LCD_DATA_PORT &= ~(1<<LCD_D4);

    if(ucCmd&0x02) LCD_DATA_PORT |= (1<<LCD_D5);
    else LCD_DATA_PORT &= ~(1<<LCD_D5);

    if(ucCmd&0x04) LCD_DATA_PORT |= (1<<LCD_D6);
    else LCD_DATA_PORT &= ~(1<<LCD_D6);

    if(ucCmd&0x08) LCD_DATA_PORT |= (1<<LCD_D7);
    else LCD_DATA_PORT &= ~(1<<LCD_D7);

    LCD_CONTROL_PORT |= (1<<LCD_E);
    LCD_CONTROL_PORT &= ~(1<<LCD_E);

    _delay_ms(2);
}

void LCDSendCmd(unsigned char ucCmd)
{
    //LCD_RS=LCD_cmd;
    LCD_CONTROL_PORT &= ~(1<<LCD_RS);

    LCDSendCmd4BIT(ucCmd>>4);
    LCDSendCmd4BIT(ucCmd);
}
void LCDSendData (unsigned char ucData)
{
    //LCD_RS=LCD_data;
    LCD_CONTROL_PORT |= (1<<LCD_RS);

    LCDSendCmd4BIT(ucData>>4);
    LCDSendCmd4BIT(ucData);
}

void LCDGotoXY(unsigned char x,unsigned char y)
{
    if(y == 1)
    {
        LCDSendCmd(DDRAM_PTR + LINE1_ADDR + x-1);
    }
    else if(y == 2)
    {
        LCDSendCmd(DDRAM_PTR + LINE2_ADDR + x-1);
    }
    else if(y == 3)
    {
        LCDSendCmd(DDRAM_PTR + LINE3_ADDR + x-1);
    }
    else if(y == 4)
    {
        LCDSendCmd(DDRAM_PTR + LINE4_ADDR + x-1);
    }
}

void LCDInit()
{

    LCD_CONTROL_DIRECTION |= (1<<LCD_RS);
    LCD_CONTROL_DIRECTION |= (1<<LCD_RW);
    LCD_CONTROL_DIRECTION |= (1<<LCD_E);

    LCD_DATA_DIRECTION |= (1<<LCD_D4);
    LCD_DATA_DIRECTION |= (1<<LCD_D5);
    LCD_DATA_DIRECTION |= (1<<LCD_D6);
    LCD_DATA_DIRECTION |= (1<<LCD_D7);


    //LCD_RS= LCD_cmd;
    LCD_CONTROL_PORT &= ~(1<<LCD_RS);
    //LCD_E = LCD_DISABLE;
    LCD_CONTROL_PORT &= ~(1<<LCD_E);

    _delay_ms(500);

    LCDSendCmd4BIT(0x03);
    _delay_ms(150);
    LCDSendCmd4BIT(0x03);
    _delay_ms(50);
    LCDSendCmd4BIT(0x03);

    LCDSendCmd4BIT(0x02);

    LCDSendCmd(0x28);//function set, 4 line, 8-bit, character size=5x7
    LCDClear();					//clear display
    LCDSendCmd(0x02 );
    LCDOff();					//turn off the LCD
    LCDOn();					//turn on the LCD
    LCDSendCmd(0x06);
    LCDSendCmd(0x10);
    LCDSendCmd(DDRAM_PTR); 			//set DDRAM Address
}

void LCDPutchar(char c)
{
    LCDSendData(c);
}
void LCDString(char *msg)
{
    uint8_t len = 0;

    while(*msg)
    {
        LCDPutchar(*msg);
        msg++;
        len++;
    }
//**** Added by Bakee  ****************************
//*** To pad the remaining characters with space  ***
    while(LCD_MAX_CHAR_IN_LINE - len)
    {
        LCDPutchar(0x20); // Space
        len++;
    }


}
void LCDDigit(unsigned char c)
{
    if(c<10)
    {
        c += 0x30;
    }
    else
    {
        c = 0x30;
    }
    LCDSendData(c);
}


//MY ADDED FUNCTION


//**** Added by Bakee  ****************************

void LCDShowCursor()
{
    LCDSendCmd(0x0E); // Display on, Cursor On and Blink On;
}

void LCDHideCursor()
{
    LCDSendCmd(0x0C); // Display on, Cursor Off and Blink Off; Format 1-D-C-B; D= Display, C= Cursor, B= Blink;
}

//***  End of addition **************************************




// Added by bakee

void LCDRefresh()
{

    //LCD_RS= LCD_cmd;
    LCD_CONTROL_PORT &= ~(1<<LCD_RS);
    //LCD_E = LCD_DISABLE;
    LCD_CONTROL_PORT &= ~(1<<LCD_E);

    _delay_ms(2);

    LCDSendCmd4BIT(0x03);
    _delay_ms(2);

    LCDSendCmd4BIT(0x03);
    _delay_ms(2);

    LCDSendCmd4BIT(0x03);
    _delay_ms(2);

    LCDSendCmd4BIT(0x02);
    _delay_ms(2);

    LCDSendCmd(0x28);//function set, 4 line, 8-bit, character size=5x7
    //LCDClear();					//clear display
    LCDSendCmd(0x02 );
    //LCDOff();					//turn off the LCD
    LCDOn();					//turn on the LCD
    LCDSendCmd(0x06);
    LCDSendCmd(0x10);
    LCDSendCmd(DDRAM_PTR); 			//set DDRAM Address
}
