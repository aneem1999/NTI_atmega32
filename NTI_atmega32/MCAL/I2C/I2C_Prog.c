/**
 * @file I2C_Prog.c
 * @brief 
 * @version 0.2
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "../LIB/register.h"
#include "./I2C_Interface.h"
#include "./I2C_Reg.h"


typedef enum i2c_prescaller_value
{
    I2C_PRESCALLER_DIV1     = 1,
    I2C_PRESCALLER_DIV4     = 4,
    I2C_PRESCALLER_DIV16    = 16,
    I2C_PRESCALLER_DIV64    = 64
}I2C_Prescaller_t;
I2C_Prescaller_t I2C_Prescaller = I2C_PRESCALLER_DIV4;
#define         FCPU                16000000UL
/**
 * @note  SCL value set (250 khz) for fast mode
 *        SCL value set (77 khz) for strd mode
 */
#define         SCL_FREQ            100000UL
#define         I2C_STATUS_MASK     0XF8

/**************************************************************************************************/
/**************************************************************************************************/
/***************************************** Version 0.2 ********************************************/
/**************************************************************************************************/
/**************************************************************************************************/

/**
 * @brief Enable I2C For Master:
 * @brief The Init Function will do the following Initialization to Master I2C.
 *        1- Set Prescaller value for TWSR Reg.
 *        2- Set Bit rate on TWBR Reg based on SCL_FREQ "Pre define value" , will add the option to make it select from user
 *        3- Enable Ack for Master 
 *        4- Enable I2C
 * @note  SCL value set (250 khz) for fast mode
 *        SCL value set (77 khz) for strd mode
 */
void I2C_vInit(void)
{
    #if 1
    // SETBIT(TWCR , TWEN);                            /* Enable I2C                                 */
    switch (I2C_Prescaller)
    {
        case I2C_PRESCALLER_DIV1:
            TWSR |= 0;
        break;
        case I2C_PRESCALLER_DIV4:
            TWSR |= 1;
        break;
        case I2C_PRESCALLER_DIV16:
            TWSR |= 2;
        break;
        case I2C_PRESCALLER_DIV64:
            TWSR |= 3;
        break;
        default:
            break;
    }
    TWBR = ((FCPU / SCL_FREQ) - 16) / (2 * 1);      /* Set Bit rate Based on pre define SCL value */
    #endif
    // TWBR = 0x5F;                    //SCL hz value set (77 khz) for strd mode
    // TWSR = 0x00;                    //prescalar value set(4)
}


/**
 * @brief   Send Start Condition on the bus
 *          1- Clear The flag               : TWINT Bit
 *          2- Enable Ack                   : TWEA Bit
 *          3- Enable Start Condition Bit   : TWSTA Bit
 *          4- Enable I2C                   : TWEN Bit
 * @return I2C_ErrorState_t
 */
I2C_ErrorState_t I2C_enuStartTransmission(void)
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTA) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    if((TWSR & I2C_STATUS_MASK) !=  I2C_START_ACK)
    {
        return I2C_SC_ERROR;                /* Start not transmitted */
    }
    else
    {
        return I2C_OK;                     /* Start Send Ok */
    }

}


/**
 * @brief Master will Send salve address with write Option
 *          1- Clear The flag               : TWINT Bit
 *          2- Enable I2C                   : TWEN Bit
 * @param SalveAddress 
 * @return I2C_ErrorState_t
 */
I2C_ErrorState_t I2C_enuSendSalveAdd(u8 SalveAddress)
{
    TWDR = SalveAddress;                /* load slave address not shift */
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    // if((TWSR & I2C_STATUS_MASK) !=  I2C_MT_SLA_W_ACK)
    // {
    //     return I2C_MT_SLA_W_ERROR;                  /* Salve Address Not Ack "Slave with this address not found " */
    // }
    // else
    // {
    //     return I2C_OK;                              /* Salve Address has Ack */
    // }
    return 0;
}


/**
 * @brief Log to Spacific Ram Address
 * 
 * @param SalveAddress 
 * @return I2C_ErrorState_t 
 */
I2C_ErrorState_t I2C_enuSendSlaveRamAdd(u8 SalveAddress)
{
    TWDR = SalveAddress;                /* load slave Ram address not shift */
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    if((TWSR & I2C_STATUS_MASK) !=  I2C_MT_DATA_ACK)
    {
        return I2C_MT_DATA_ERROR;                       /* ???? */
    }
    else
    {
        return I2C_OK;                                  /* Salve Address has Ack */
    }
}

/**
 * @brief 
 * @note Check for condition
 * @param Data 
 * @return I2C_ErrorState_t 
 */
I2C_ErrorState_t I2C_enuSendSlaveData(u8 Data)
{
    TWDR = Data;                                    /* load slave Ram address not shift */
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    // if((TWSR & I2C_STATUS_MASK) !=  I2C_MT_DATA_ACK)
    // {
    //     return I2C_MT_DATA_ERROR;                       /* ???? */
    // }
    // else
    // {
    //     return I2C_OK;                                  /* Salve Address has Ack */
    // }
    return 0;

}

/**
 * @brief   Send Repeated Start Condition on the bus
 *          1- Clear The flag               : TWINT Bit
 *          2- Enable Ack                   : TWEA Bit
 *          3- Enable Start Condition Bit   : TWSTA Bit
 *          4- Enable I2C                   : TWEN Bit
 * @return I2C_ErrorState_t
 */
I2C_ErrorState_t I2C_enuRestartTransmission(void)
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTA) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    if((TWSR & I2C_STATUS_MASK) !=  I2C_R_START_ACK)
    {
        return I2C_RSC_ERROR;                /* Start not transmitted */
    }
    else
    {
        return I2C_OK;                     /* Start Send Ok */
    }

}


/**
 * @brief 
 * 
 * @return u8 
 */
u8 I2C_enuReadOneByte(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    return TWDR;
}


/**
 * @brief 
 * 
 * @return uint16 
 */
int I2C_enuReadMoreByte(void)
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while(CHECK_BIT(TWCR , TWINT) == 0);               /* Polling untill the transmitting done         */
    return TWDR;    // TWDR 1Byte so why need to int & how return more byte
}
















/**
 * @brief 
 * 
 */
void I2C_vStopTransmission(void)
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWSTO) | (1<<TWEN);
}

	// i2c_write(0x80,com);


void I2C_Write(u8 FrameType , u8 Data)
{
    I2C_enuStartTransmission();
    I2C_enuSendSalveAdd(OLED_ADDRESS | WRITE);
    I2C_enuSendSlaveRamAdd(FrameType);                // To know if it data or cmd will send next
    I2C_enuSendSlaveData(Data);
    I2C_vStopTransmission();
}





































u8 I2C_Read(u8 Address)
{
    u8 Data;                                     
    I2C_enuStartTransmission();                 
    I2C_enuSendSalveAdd(OLED_ADDRESS | WRITE);                  // 0x78
    I2C_enuSendSlaveRamAdd(Address);                
    I2C_enuRestartTransmission();                               
    I2C_enuSendSalveAdd(OLED_ADDRESS | READ);                   // 0x79  
    Data = I2C_enuReadOneByte();                    
    I2C_vStopTransmission();  
    return Data;                      
}