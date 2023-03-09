/***************************************************************
     @author             :    Ahmed Naeem
     @date 				 :    4 Mar 11:15:02 AM
     @version 			 :    1.0V
     @brief 		     :    interface file  file [_interface.h]
***************************************************************/
					    	


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


/*************************************************************
 *   Global SPI Call back function
 *************************************************************/
void (*GP_SPI_CallBack)();



/*************************************************************
 *   SPI APIs
 *************************************************************/
void SPI_voidMasterInit();

void SPI_voidSlaveInit();

void SPI_voidTransmit(u8 data);


u8 SPI_u8Recieve();


void SPI_voidIEN(void (*CallBack)());



#endif /* SPI_INTERFACE_H_ */