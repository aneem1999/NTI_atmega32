/*
 * exEEPROM.h
 *
 * Created: 3/11/2023 10:28:08 AM
 *  Author: ncm
 */ 


#ifndef EXEEPROM_H_
#define EXEEPROM_H_




void exEEPROM_voidWriteByte(u8 copyofWordAddrs,u8 copyofByte);


void exEEPROM_voidReadByte(u8 copyofWordAddrs,u8* copyofByte);










#endif /* EXEEPROM_H_ */