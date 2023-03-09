/***************************************************************
     @author             :    Ahmed Naeem
     @date 				 :    4 Mar 11:15:02 AM
     @version 			 :    1.0V
     @brief 		     :    Configuration  file [cfg.h]
***************************************************************/
					
#ifndef SPI_CFG_H
#define SPI_CFG_H
/*************************************************************
 *    SPI Configurations Define Macros
 *************************************************************/

/* @ref DATA_Order_Define */
#define DATA_Order_LSBtoMSB 1
#define DATA_Order_MSBtoLSB 0

/* @ref PCK_Prescaler_Define */
#define PCK_Prescaler_4     0
#define PCK_Prescaler_16    (1)
#define PCK_Prescaler_64    (2)
#define PCK_Prescaler_128   (3)
#define PCK_Prescaler_2     (4)
#define PCK_Prescaler_8     (5)
#define PCK_Prescaler_32    (6)
#define PCK_Prescalerx2_64  (7)


/* @ref SPI_CPOL_Define */
#define SPI_CPOL_RIS_FAL     0
#define SPI_CPOL_FAL_RIS     1

/* @ref SPI_CPHA_Define */
#define SPI_CPHA_SMPL_STUP   0
#define SPI_CPHA_STUP_SMPL   1




/*************************************************************
 *    SPI Configurations
 *************************************************************/
#define SPI_DATA_Order     DATA_Order_MSBtoLSB
#define SPI_PCK_Prescaler  PCK_Prescaler_128
#define SPI_CPOL           SPI_CPOL_RIS_FAL
#define SPI_CPHA           SPI_CPHA_SMPL_STUP
#endif