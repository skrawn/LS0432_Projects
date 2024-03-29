/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright Texas Instruments - 2012.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_format.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_Format.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       07Sept2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.01       14Sept2012    Vishwanath Reddy     0000000000000    Review changes
 * 00.01.02       30Nov2012     Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 00.01.05		  04Mar2013	  	Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.06		  11Mar2013	  	Vishwanath Reddy     SDOCM00099152    Change because of the F021 library. 
 * 01.12.00		  13Dec2013     Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                    MISRA C fixes.
 *                                                   SDOCM00105415    API can now be called with out TI_Fee_Init
 *                                                                    being called.
 *********************************************************************************************************************/

 
 /*********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ti_fee.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  TI_Fee_Format
 *********************************************************************************************************************/
/*! \brief      This function is used to Erase all the VS.
 *  \param[in]  u32FormatKey
 *  \param[out] none
 *  \return     boolean 
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
#if(TI_FEE_DRIVER == 1U)
/* SourceId : HL_Fee_SourceId_17 */
/* DesignId : HL_FEE_DesignId_31 */
/* Requirements : HL_FEE_SR67 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
boolean TI_Fee_Format(uint32 u32FormatKey)
{
	uint16 u16LoopIndex=0U;
	uint32 u32FlashStatus = 0U;
	uint16 u16Index=0U;
	Fapi_FlashSectorType oSectorStart,oSectorEnd;
	boolean bFlashStatus=FALSE;
	uint8 u8EEPIndex=0U;	
	boolean bFormat = FALSE;
	
	/* Erase configured sectors of EEPROM */
	/*SAFETYMCUSW 28 D <APPROVED> "Reason -  TI_FEE_NUMBER_OF_EEPS is limited to 1/2 */
	while((u8EEPIndex<TI_FEE_NUMBER_OF_EEPS) && (u32FormatKey == 0xA5A5A5A5U))
	{		
		if(UNINIT != TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState)
		{
			for(u16LoopIndex=0U;u16LoopIndex<TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;u16LoopIndex++)	
			{			
				/* Determine the Start & End Address for the Virtual Sector */
				if(u8EEPIndex==0U)
				{				
					oSectorStart=Fee_VirtualSectorConfiguration[u16LoopIndex].FeeStartSector;
					oSectorEnd=Fee_VirtualSectorConfiguration[u16LoopIndex].FeeEndSector;
					/*SAFETYMCUSW 55 D MR:13.6 <APPROVED> "Reason -  u16LoopIndex is not modified here."*/
					(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16LoopIndex])++;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Invalid;
				}
				else
				{				
					oSectorStart=Fee_VirtualSectorConfiguration[u16LoopIndex +
					             TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1].FeeStartSector;
					oSectorEnd=Fee_VirtualSectorConfiguration[u16LoopIndex +
					           TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1].FeeEndSector;
					(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16LoopIndex+
					                                       TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1])++;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex+
					                   TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1]=VsState_Invalid;
				}							

				TI_FeeInternal_GetVirtualSectorIndex(oSectorStart,oSectorEnd,
				                                    (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8Bank,
				                                    (boolean)TRUE,(uint8)u8EEPIndex);

				/* Erase the Virtual Sector */
				for(u16Index=0U;u16Index<=(oSectorEnd-oSectorStart);u16Index++)
				{
					oSectorEnd-=u16Index; 				
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress=
					Device_FlashDevice.Device_BankInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8Bank].Device_SectorInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd].Device_SectorStartAddress;
					/*SAFETYMCUSW 496 S MR:8.1 <APPROVED> "Reason -  Fapi_issueAsyncCommandWithAddress is part of F021 and is included via F021.h."*/
					if((Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
										(uint32_t *)TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress
					                     ))==Fapi_Status_Success)
					 {
					 }
					 else
					 {
						/* For MISRA-C complaince */
					 }
					 u32FlashStatus=TI_FeeInternal_PollFlashStatus();
					 if(u32FlashStatus!=0U)
					 {
						/* Report Error if the erase failed */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_EraseVS;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;						
						TI_Fee_u8ErrEraseVS = 0x1U << (Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber-1U);
					}
					else
					{
						bFlashStatus=TI_FeeInternal_BlankCheck(
						             TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress,
									 TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+(Device_FlashDevice.Device_BankInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8Bank].Device_SectorInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd].Device_SectorLength),
									(uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8Bank, 												
									u8EEPIndex);
						if(bFlashStatus!=TRUE)
						{
							/* Report Error if the erase failed */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_EraseVS;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;							
							TI_Fee_u8ErrEraseVS = 0x1U << (Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber-1U);	
						}	
						else
						{
							/* For MISRA-C complaince */
						}		
					}
				}
			}
		}
		else
		{
			/* Report Error */
			bFormat = TRUE;	
		}
		u8EEPIndex++;
	}
	/* Erase EEPROM bank */
	if(u32FormatKey == 0x5A5A5A5AU)
	{
		/* Set up the State machine.*/ 
		if((Fapi_initializeFlashBanks((uint32)TI_FEE_OPERATING_FREQUENCY))==Fapi_Status_Success)
		{	
			TI_Fee_FapiInitCalled = TRUE;				
			Fapi_setActiveFlashBank(Device_FlashDevice.Device_BankInfo[0].Device_Core); 
			Fapi_enableEepromBankSectors(0xFFFFFFFFU, 0xFFFFFFFFU);			
			
			if((Fapi_issueAsyncCommandWithAddress(Fapi_EraseBank,
												 /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
												 (uint32_t *)Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress
												  ))!=Fapi_Status_Success)
			{
				/* Report Error if the erase failed */
				bFormat = TRUE;
			}
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is not required."*/
			TI_FeeInternal_PollFlashStatus();
		}
		else
		{
			/* Report Error if the erase failed */
			bFormat = TRUE;
		}
	}
	
	if((u32FormatKey != 0xA5A5A5A5U) && (u32FormatKey != 0x5A5A5A5AU))
	{
		/* Report Error if the key did not match */
		bFormat = TRUE;		
	}		
	return(bFormat);
}
#endif

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: ti_fee_format.c
 *********************************************************************************************************************/
