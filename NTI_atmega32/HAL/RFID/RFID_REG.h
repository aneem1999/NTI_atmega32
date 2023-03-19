/*
 * RFID_REG.h
 *
 *  Created on: Mar 12, 2023
 *      Author: dell
 */

#ifndef HAL_RFID_RFID_REG_H_
#define HAL_RFID_RFID_REG_H_

// Mifare_One card command word
# define PICC_REQIDL			0x26				// find the antenna area does not enter hibernation
# define MCRF522_REQ_MODE_ALL	0x52				// find all the cards antenna area
# define MCRF522_SELECT_TAG		0x93				// election card
# define MCRF522_REQ_COMMAND	0x20				// request uid



//command set
#define MCRF522_CMD_IDLE 				0x00
#define MCRF522_CMD_TRANSCEIVE			0x0C

#define MCRF522_REG_COMM_IE_N		0x02
#define MCRF522_REG_COMM_IRQ		0x04
#define MCRF522_REG_FIFO_LEVEL		0x0A
#define	MCRF522_REG_COMMAND			0x01
#define MCRF522_REG_FIFO_WR			0x09
#define MCRF522_REG_BIT_FRAMING		0x0D
#define MCRF522_REG_ERROR			0x06
#define MCRF522_REG_CONTROL			0x0C
#define MCRF522_REG_COLL			0x0E

#define MCRF522_IRQ_ERR				0x01
#define MCRF522_ERR_COLLISION		0x08

#endif /* HAL_RFID_RFID_REG_H_ */
