/*
 * dht.h
 *
 * Created: 3/13/2023 7:53:01 PM
 *  Author: ncm
 */

#ifndef DHT_H_
#define DHT_H_


typedef enum
{
    ERROR_READ,
    SUCCESS_READ
} DHT_Read_t;

void DHT_voidRequest(void);

void DHT_voidResponse(void);

u8 DHT_u8Recive(void);

DHT_Read_t DHT_enuReadData(u16 *RH_Value, u16 *Temp_Value);
#endif /* DHT_H_ */