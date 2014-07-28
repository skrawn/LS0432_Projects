/** @file Device_TMS570LS04.c
*   @brief This file defines the FLASH details.
*   @date 20.May.2014
*   @version 04.00.00
*
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Device_TMS570LS04.h"

/* Start Device Definition */
/*SAFETYMCUSW 79 S MR:19.4 <APPROVED> "Reason - F021_CPU0_BASE_ADDRESS is a symbolic constant"*/
/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
#define DEVICE_BANKCONTROLREGISTER  F021_CPU0_BASE_ADDRESS  /* Control Register Address */

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

const Device_FlashType Device_FlashDevice =
{
   "TMS570LS04x",                     	/* Device name */
   0x00000000U,                         /* Device Engineering ID */
   Device_ErrorHandlingEcc,             /* Indicates which type of bit Error handling is on the device */   
   Device_CortexR4,					    /* Indicates the Master core type on the device */	   
   TRUE,                              	/* Indicates if the device supports Flash interrupts for processing Flash */   
   31U,                                 /* Nominal time for one write command operation in uS - This value still needs 
                                           to be characterized */
   300U,                                /* Maximum time for one write command operation in uS - This value still needs 
                                           to be characterized */       
   {                                    /* Array of Banks on the device */
	   {    /* Start of Bank Definition */
			 /*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here."*/
			 /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			 DEVICE_BANKCONTROLREGISTER,	   	/* Pointer to the Flash control register for this bank */
			 Fapi_FlashBank7,               	/* Core number for this bank */                
			{                           /* Array of the Sectors within a bank */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector0 is enum."*/
					Fapi_FlashSector0,   /* Sector number */
					0xF0200000U,         /* Starting address of the sector */
					0x00000FFFU,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100000U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector1 is enum."*/
					Fapi_FlashSector1,   /* Sector number */
					0xF0201000U,         /* Starting address of the sector */
					0x00000FFFU,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100200U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector2 is enum."*/
					Fapi_FlashSector2,   /* Sector number */
					0xF0202000U,         /* Starting address of the sector */
					0x00000FFFU,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100400U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector3 is enum."*/
					Fapi_FlashSector3,   /* Sector number */
					0xF0203000U,         /* Starting address of the sector */
					0x00000FFFU,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100600U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				}  /* End of Sector Definition */
			}
	   }  /* End of Bank Definition */
   }   /* End of Bank Array */
};  /* End of Device Definition */

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/* End of File */
