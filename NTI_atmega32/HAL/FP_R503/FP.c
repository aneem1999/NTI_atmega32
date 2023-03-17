/*
 * FP.c
 *
 * Created: 3/13/2023 3:25:16 PM
 *  Author: ncm
 */

/**********************************************************************************************************
 *    INCLUDES
 ***********************************************************************************************************/
#include "std_types.h"
#include "../MCAL/USART/uart_interface.h"
#include "FP.h"
#include "../HAL/LCD/LCD.h"

#define F_CPU 16000000U
#include <util/delay.h>

/**********************************************************************************************************
 *    R503   Commends Sets
 ***********************************************************************************************************/
u8 handshake[13] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x17, 0x00, 0x00, 0x1c};
u8 getimg[12] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
u8 img2tz1[13] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08};
u8 img2tz2[13] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x02, 0x00, 0x09};
u8 regmodel[12] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09};
u8 store[15] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00};
u8 search[17] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x00, 0xff, 0x01, 0x0d};
u8 load[15] =
    {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00};

u8 REGISTRY_ID = 0;

u8 Buffer[25];

/**********************************************************************************************************
 *  Functions  implementation
 *********************************************************************************************************/

//////////////////////////////////////////////////////////
void clearBuffer()
{
    for (int i = 0; i < 25; i++)
        Buffer[i] = -1;
    // for(int i=0;i<10;i++)myserial.read();
}

/***************************************************************
 *  For UART protocol, it control the “on/off” of USB port
 *   turn off usb port
 */
u8 FP_voidStart()
{
    LCD_ClearDisplay();
    int i = 0;
    for (i = 0; i < 13; i++)
    {
        UART_TransmitBusyWait(handshake[i]);
    }

    i = 0;
    while (i < 12)
    {
        if (UART_Receive_No_Block(&Buffer[i]) == UART_RECIEVE_ERROR)
        {
            // handel it
        }
        i++;
    }

    if (Buffer[9] == 0)
    {
        clearBuffer();

        LCD_GoToXY(0, 0);
        LCD_WriteString("FP Started ");
        LCD_WriteData(Buffer[9] + 48);
        return 1;
    }
    else
    {
        LCD_GoToXY(0, 0);
        LCD_WriteString("FP cant Start ");
        LCD_WriteData(Buffer[9] + 48);
        clearBuffer();
        return 0;
    }
}

/***************************************************************
 *  Detecting finger and store the detected finger image in
 *  ImageBuffer while returning successfull confirmation code
 *  If there is no finger, returned confirmation code
 *  would be “can’t detect finger”.
 */
u8 FP_u8ReadFinger()
{
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        UART_TransmitBusyWait(getimg[i]);
    }

    i = 0;
    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }

    if (Buffer[9] == 0)
    {

        clearBuffer();
        LCD_GoToXY(1, 0);
        LCD_WriteString("read ");

        return 1;
    }
    else if (Buffer[9] == 1 || Buffer[9] == 3)
    {
        LCD_WriteString("read ");

        clearBuffer();
        return 2;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

/*********************************************************************
 *  Generate character file from the original finger image in
 *  ImageBuffer and store the file in CharBuffer1 or CharBuffer2.
 */
u8 FP_u8ConvertToCharArr1()
{
    int i = 0;
    for (i = 0; i < 13; i++)
    {
        UART_TransmitBusyWait(img2tz1[i]);
    }

    i = 0;
    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }

    if (Buffer[9] == 0)
    {
        clearBuffer();
        LCD_WriteString(",convert");
        return 1;
    }
    else
    {
        LCD_WriteString(",NotConvrt");
        clearBuffer();
        return 0;
    }
}

u8 FP_u8ConvertToCharArr2()
{
    int i = 0;
    for (i = 0; i < 13; i++)
    {
        UART_TransmitBusyWait(img2tz2[i]);
    }

    i = 0;
    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }

    if (Buffer[9] == 0)
    {
        clearBuffer();
        LCD_WriteString(",convert2");
        return 1;
    }
    else
    {
        clearBuffer();
        LCD_WriteString(",Not convert2");
        return 0;
    }
}

/***************************************************************************
 * to load template at the specified location (PageID) of Flash library to template buffer
CharBuffer1/CharBuffer2
*/
u8 showData(u16 pageid)
{
    u8 i = 0;
    u8 sum = 0;
    u8 pageid1, pageid2;
    u8 sum1, sum2;

    pageid1 = (pageid >> 8) & 0x00ff;
    pageid2 = (pageid & 0x00ff);
    load[11] = pageid1;
    load[12] = pageid2;
    for (i = 6; i < 13; i++)
    {
        sum += load[i];
    }
    sum1 = (sum >> 8) & 0x00ff;
    sum2 = (sum & 0x00ff);
    load[13] = sum1;
    load[14] = sum2;

    for (i = 0; i < 15; i++)
    {
        UART_TransmitBusyWait(load[i]);
    }

    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }

    if (Buffer[9] == 0)
    {
        LCD_GoToXY(3, 0);
        LCD_WriteString("templtOK");
        clearBuffer();
        return 1;
    }
    else
    {
        LCD_GoToXY(3, 0);
        LCD_WriteString("templt fail");
        clearBuffer();
        return 0;
    }
}
/*******************************************************************
 * combine information of character files from CharBuffer1 and CharBuffer2 and
generate a template which is stroed back in both CharBuffer1 and CharBuffer2.
*/
u8 FP_u8CreateTemplate()
{
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        UART_TransmitBusyWait(regmodel[i]);
    }

    i = 0;
    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }

    if (Buffer[9] == 0)
    {
        clearBuffer();
        LCD_WriteString(" ,str");
        return 1;
    }
    else
    {
        clearBuffer();
        LCD_WriteString(" ,Nstr");
        return 0;
    }
}

/****************************************************
 * store the template of specified buffer (Buffer1/Buffer2)
 * at the designated location of Flash library.
 */
u8 FP_u8StoreTemplate(u16 pageid)
{
    int i = 0;
    int sum = 0;
    u8 pageid1, pageid2;
    u8 sum1, sum2;

    pageid1 = (pageid >> 8) & 0x00ff;
    pageid2 = (pageid & 0x00ff);
    store[11] = pageid1;
    store[12] = pageid2;
    for (i = 6; i < 13; i++)
    {
        sum += store[i];
    }
    sum1 = (sum >> 8) & 0x00ff;
    sum2 = (sum & 0x00ff);
    store[13] = sum1;
    store[14] = sum2;

    for (i = 0; i < 15; i++)
    {
        UART_TransmitBusyWait(store[i]);
    }

    i = 0;
    while (i < 12)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }
    if (Buffer[9] == 0)
    {
        clearBuffer();
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

u8 FP_u8Search(u16 startpage, u16 pagenum, u16 *fingerprint_id)
{
    u8 i = 0;

    search[11] = (startpage >> 8) & 0x00ff;
    search[12] = startpage & 0xff;
    search[13] = (pagenum >> 8) & 0x00ff;
    search[14] = pagenum & 0xff;

    for (i = 0; i < 17; i++)
    {
        UART_TransmitBusyWait(search[i]);
    }

    i = 0;
    while (i < 16)
    {
        UART_Receive_No_Block(&Buffer[i]);
        i++;
    }
    *fingerprint_id = ((u16)Buffer[10] << 8) | Buffer[11];

    u16 fingerprint_score = ((u16)Buffer[12] << 8) | Buffer[13];

    if (Buffer[9] == 0)
    {
        clearBuffer();
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

/*
  When enrolling, user needs to enter the finger two times. The system will process the two time
  finger images, generate a template of the finger based on processing results and store the template
 */

u8 FP_Enroll(void)
{
    /* Start port */
    if (FP_voidStart())
    {

        /* detect finger first shot in store it in img buffer 1 */
        if (FP_u8ReadFinger())
        {

            /* convert img to array of char in char buffer 1*/
            if (FP_u8ConvertToCharArr1())
            {

                // tell user put his finger again
            }
            else
            {
            }
        }
        else
        {
        }
        /* detect finger second shot and store it in img buffer 2 */
        if (FP_u8ReadFinger())
        {
            LCD_GoToXY(2, 0);

            /* convert img to array of char in char buffer 2*/
            if (FP_u8ConvertToCharArr2())
            {

                /* generte model for finger print */
                if (FP_u8CreateTemplate())
                {

                    /* store model for finger print  in flash */
                    if (FP_u8StoreTemplate(0))
                    {
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }
}

/*
    When matching, user enters the finger through optical sensor and system will generate a template
of the finger and compare it with templates of the finger library. For 1:1 matching, system will
compare the live finger with specific template designated in the Module; for 1:N matching, or
searching, system will search the whole finger library for the matching finger. In both
circumstances, system will return the matching result, success or failure
*/

u8 FP_u8UserVerify(u16 *FP_id)
{
    /* Start port */
    if (FP_voidStart())
    {
        /* detect finger first shot in store it in img buffer 1 */
        if (FP_u8ReadFinger())
        {
            /* convert img to array of char in char buffer 1*/
            if (FP_u8ConvertToCharArr1())
            {
                if (FP_u8Search((u16)0, (u16)0, FP_id))
                {
                }
            }
            else
            {
            }
        }
        else
        {
        }
    }
}