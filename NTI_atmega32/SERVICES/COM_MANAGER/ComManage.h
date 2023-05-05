/*
 * ComManage.h
 *
 * Created: 3/27/2023 10:48:21 AM
 *  Author: ncm
 */

#ifndef COMMANAGE_H_
#define COMMANAGE_H_

#include "../LIB/std_types.h"

/*************** UART Default stop condition ******************/
#define Default_STOP '\r'

void ComM_Init(void);
void ComM_SendMssg(u8 mssg[]);
void ComM_ReceiveMssg(u8 **mssg);
boolean ComM_MssgIsReceived(void);
void ComM_RxComplete_Clbk(void);
void ComM_TxComplete_Clbk(void);

#endif /* COMMANAGE_H_ */