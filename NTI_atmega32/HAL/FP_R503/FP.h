/*
 * FP.h
 *
 * Created: 3/13/2023 3:25:38 PM
 *  Author: ncm
 */

#ifndef FP_H_
#define FP_H_

typedef enum
{
    RECIEVE_PACK = 1,
    CAN_NOT_DETECT_FINGER,
    FAIL_COLLECT_FINGER

} GetImage_Return_t;

/*******************************************************
 * FP APIs
 ********************************************************/

void clearBuffer();
u8 FP_voidStart();
u8 FP_u8ReadFinger();
u8 FP_u8ConvertToCharArr1();
u8 FP_u8ConvertToCharArr2();
u8 showData(u16 pageid);
u8 FP_u8CreateTemplate();
u8 FP_u8StoreTemplate(u16 pageid);
u8 FP_u8Search(u16 startpage, u16 pagenum, u16 *fingerprint_id);
#endif /* FP_H_ */