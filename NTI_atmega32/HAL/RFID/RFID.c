/*
 * RFID.c
 *
 * Created: 3/17/2023 8:49:25 PM
 *  Author: katbo
 */

#include "RFID.h"
#include "RFID_REG.h"
void mcrf522_write_reg(u8 reg, u8 value)
{
	dio_vidWriteChannel(DIO_PORTB, DIO_PIN3, STD_LOW);
	SPI_DATA_RW((reg << 1) & 0x7E);
	SPI_DATA_RW(value);
	dio_vidWriteChannel(DIO_PORTB, DIO_PIN3, STD_HIGH);
}

u8 mcrf522_read_reg(u8 reg)
{
	u8 value;
	dio_vidWriteChannel(DIO_PORTB, DIO_PIN3, STD_LOW);
	SPI_DATA_RW(((reg << 1) & 0x7E) | 0x80); // Send register address with read flag
	value = SPI_DATA_RW(0x00);				 // Receive register value
	dio_vidWriteChannel(DIO_PORTB, DIO_PIN3, STD_HIGH);
	return value;
}

void mcrf522_clear_bit_mask(u8 reg, u8 mask)
{
	u8 temp;
	temp = mcrf522_read_reg(reg);
	mcrf522_write_reg(reg, temp & (~mask));
}

void mcrf522_set_bit_mask(u8 reg, u8 mask)
{
	u8 tmp;
	tmp = mcrf522_read_reg(reg);
	mcrf522_write_reg(reg, tmp | mask);
}

void mcrf522_reset()
{
	mcrf522_write_reg(MCRF522_REG_COMMAND, 0x0F); // Reset
}

void mcrf522_antenna_on(void)
{
	u8 value;

	value = mcrf522_read_reg(0x14);
	if (!(value & 0x03))
	{
		mcrf522_write_reg(0x14, value | 0x03);
	}
}

void mcrf522_init(void)
{
	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	mcrf522_write_reg(0x2A, 0x80); // TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	mcrf522_write_reg(0x2B, 0x9A); // TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25?s.
	mcrf522_write_reg(0x2C, 0x03); // Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	mcrf522_write_reg(0x2D, 0xE8);
	mcrf522_write_reg(0x15, 0x40); // forces a 100 % ASK modulation independent of the ModGsPReg register setting
	mcrf522_write_reg(0x11, 0x3D);
	mcrf522_antenna_on(); // Enable antenna
}

u8 Communicate(u8 command, u8 *sendData, u8 sendLen, u8 *backData, u8 *backLen)
{
	/*******************/
	u8 waitIRq = 0, irq_en = 0, n;
	if (command == MCRF522_CMD_TRANSCEIVE)
	{
		irq_en = 0x77;	// enable tx,rx,idle,lowalert,err,timer interrupt
		waitIRq = 0x30; // wait for tx complete flag and idle flag
	}
	mcrf522_write_reg(MCRF522_REG_COMMAND, MCRF522_CMD_IDLE);
	// 11110111    first 1 is for write
	// enable global,tx,rx,idle,lowalert,err,timer interrupt
	mcrf522_write_reg(MCRF522_REG_COMM_IE_N, irq_en | 0x80);
	// clear all interrupts flags
	mcrf522_clear_bit_mask(MCRF522_REG_COMM_IRQ, 0x80);
	// flashes the fifo buffer
	mcrf522_set_bit_mask(MCRF522_REG_FIFO_LEVEL, 0x80);
	// NO action; Cancel the current cmd???
	mcrf522_write_reg(MCRF522_REG_COMMAND, MCRF522_CMD_IDLE);
	// put data in fifo
	for (u8 i = 0; i < sendLen; i++)
	{
		mcrf522_write_reg(MCRF522_REG_FIFO_WR, sendData[i]);
	}
	// send MCRF522_CMD_TRANSCEIVE command then put 1 in start sending bit in bitframing reg
	mcrf522_write_reg(MCRF522_REG_COMMAND, command);
	if (command == MCRF522_CMD_TRANSCEIVE)
	{
		mcrf522_set_bit_mask(MCRF522_REG_BIT_FRAMING, 0x80);
	}
	for (int i = 2000; i > 0; i--)
	{
		n = mcrf522_read_reg(MCRF522_REG_COMM_IRQ);
		if (n & waitIRq)
		{
			break;
		}
		if (n & MCRF522_IRQ_ERR)
		{
			return 0;
		}
	}

	// here we read if there is collision error in error register or timeout
	u8 status = mcrf522_read_reg(MCRF522_REG_ERROR);
	if (status & MCRF522_ERR_COLLISION || n == 0)
	{
		return 0;
	}

	if (backData && backLen)
	{
		*backLen = mcrf522_read_reg(MCRF522_REG_FIFO_LEVEL);
		for (u8 i = 0; i < *backLen; i++)
		{
			backData[i] = mcrf522_read_reg(MCRF522_REG_FIFO_WR);
		}
	}
	return 1;
}

u8 DetectCard()
{
	u8 buffer[2];
	u8 len = sizeof(buffer);
	mcrf522_clear_bit_mask(MCRF522_REG_COLL, 0x80);
	u8 command[1] = {MCRF522_REQ_MODE_ALL};
	// The MIFARE protocol requires that the frame size be set to 7 bits for the request command.
	mcrf522_write_reg(MCRF522_REG_BIT_FRAMING, 0x07);
	if (!Communicate(MCRF522_CMD_TRANSCEIVE, command, 1, buffer, &len))
	{
		return 0;
	}
	if (len != 2)
	{
		return 0;
	}
	return 1;
}

u8 getFirmwareVersion()
{
	return mcrf522_read_reg(0x37);
}

u8 GetCardId(u8 *uid)
{
	u8 buffer[16];
	u8 backLen = 16;
	// all received bits will be cleared after a collision
	mcrf522_clear_bit_mask(MCRF522_REG_COLL, 0x80);
	// Put MCRF522 in idle mode
	mcrf522_write_reg(MCRF522_REG_COMMAND, MCRF522_CMD_IDLE);
	mcrf522_write_reg(MCRF522_REG_BIT_FRAMING, 0);
	buffer[0] = MCRF522_SELECT_TAG;
	buffer[1] = MCRF522_REQ_COMMAND;
	if (!Communicate(MCRF522_CMD_TRANSCEIVE, buffer, (u8)2, buffer, &backLen))
	{
		return 0;
	}
	for (u8 i = 0; i < 4; i++)
	{
		uid[i] = buffer[i];
	}
	uid[4] = '\0';
	return 1;
}
