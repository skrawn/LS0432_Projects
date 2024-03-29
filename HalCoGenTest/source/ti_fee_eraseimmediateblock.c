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
 *         File:  ti_fee_eraseimmediateblock.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_EraseImmediateBlock.
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
 * 00.01.03       14Jan2013     Vishwanath Reddy     SDOCM00098510    Changes as requested by Vector.
 * 00.01.05		  04Mar2013	  	Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.08		  05Apr2013	    Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured  
                                                                      blocks,Main function modified to complete writes 
																	  asfast aspossible, Added Non polling modesupport.
 * 00.01.09		  19Apr2013	  	Vishwanath Reddy     SDOCM00099152    Warning removal,Added feature comparision of data
																	  during write.															  
 * 00.01.10       11Jun2013	    Vishwanath Reddy     SDOCM00101845	  Fixed issue withone EEPROM getting locked because
                                                                      of error in second EEPROM.	
 * 01.12.00		  13Dec2013     Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                    MISRA C fixes. 
 *                																	  
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
 *  TI_Fee_EraseImmediateBlock
 *********************************************************************************************************************/
/*! \brief      This function performs the Erase Immediate operation on a block .
 *  \param[in]  uint16 BlockNumber
 *  \param[out] none
 *  \return     E_OK
 *  \return     E_NOT_OK
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_13 */
/* DesignId : HL_FEE_DesignId_21 */
/* Requirements : HL_FEE_SR55, HL_FEE_SR56, HL_FEE_SR57 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
Std_ReturnType TI_Fee_EraseImmediateBlock(uint16 BlockNumber)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
	   outside of FEE."*/
	Std_ReturnType oResult=E_OK;
	uint32 u32BlockAddress = 0x0BAD0BADU;
	uint16 u16BlockNumber=0U;
	uint16 u16BlockIndex=0U;	
	TI_FeeModuleStatusType ModuleState=IDLE;	
	uint16 u16DataSetNumber=0U;
	uint8 u8EEPIndex=0U;
		
	TI_Fee_u8DeviceIndex = 0U;			
	
	/* Determine the Block number & Block index */
	/* From the block number, remove data selection bits */
	u16BlockNumber=TI_FeeInternal_GetBlockNumber(BlockNumber);
	/* Get the index of the block in Fee_BlockConfiguration array */
	u16BlockIndex=TI_FeeInternal_GetBlockIndex(u16BlockNumber);
	/* If block index is not configured/found, report an error */
	if(u16BlockIndex==0xFFFFU)
	{
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_InvalidBlockIndex;
	  /*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be
	    fixed outside of FEE."*/
	  oResult=E_NOT_OK;
	  #if(TI_FEE_NUMBER_OF_EEPS==2U)
	  TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_oStatus=TI_FEE_ERROR;
	  TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_Error=Error_InvalidBlockIndex;
	  #endif		  
	}
	else
	{	
	  /* Read the device index from the block configuration */
	  u8EEPIndex = Fee_BlockConfiguration[u16BlockIndex].FeeEEPNumber;	
	  /* Store the module state */
	  ModuleState=TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;		
	  if(UNINIT == ModuleState)
	  {
		/* Module is Not Initialized */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_FeeUninit;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_FAILED;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
		 fixed outside of FEE."*/
		oResult=E_NOT_OK;
	  }
	  else
	  {
		TI_Fee_u8DeviceIndex = u8EEPIndex;
		/* Get the DataSet index after removing the Block number */
		/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is not required."*/
		u16DataSetNumber = TI_FeeInternal_GetDataSetIndex(BlockNumber);	 	
		/* Check if the block is already available in EEP */
		u32BlockAddress = TI_FeeInternal_GetCurrentBlockAddress(u16BlockIndex,u16DataSetNumber,u8EEPIndex);
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_OK;
		/* Check for any non severe errors */		
		TI_FeeInternal_CheckForError(u8EEPIndex);
	  }
	}
	/* Vector's requirement - If block is configured but not present in Flash, do not return error. */	
	if(u32BlockAddress == 0x00000000U)	
	{
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_OK;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_Nil;
	  oResult=E_OK;
	  #if(STD_OFF == TI_FEE_POLLING_MODE)
	  TI_FEE_NVM_JOB_END_NOTIFICATION();
	  #endif
	}

	/* Store the module state */
	ModuleState=TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;		
	
	if((Fee_BlockConfiguration[u16BlockIndex].FeeImmediateData!=TRUE) && (u16BlockIndex!=0xFFFFU))
	{				
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should 
		  be fixed outside of FEE."*/
		oResult=E_NOT_OK;			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_BlockInvalid;				
	}
	
	if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error==Error_Nil) && (u16BlockIndex!=0xFFFFU) && 
	   (u32BlockAddress != 0x00000000U))
	{
		oResult = TI_FeeInternal_InvalidateErase(BlockNumber);
	}					
	if(oResult==(uint8)E_NOT_OK)
	{
		if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate==0U) &&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock==0U) &&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync==0U)&&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync==0U)&&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read==0U)
		  )
		 {
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate=0U;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_FAILED;
			#if(STD_OFF == TI_FEE_POLLING_MODE)
			TI_FEE_NVM_JOB_ERROR_NOTIFICATION();
			#endif
			/* Restore the module state */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=ModuleState;			
		}
	}
	else if((u16BlockIndex!=0xFFFFU) && (u32BlockAddress != 0x00000000U))
	{
		/* Block Size is zero since no data is present in Erased Block */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSizeinBlockHeader = 0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader=BlockNumber;						
		TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate=1U;
	}		
	#if(TI_FEE_NUMBER_OF_EEPS==2U)
	TI_Fee_oStatusWord_Global.Fee_u16StatusWord = ((TI_Fee_oStatusWord[0].Fee_u16StatusWord) |
												   (TI_Fee_oStatusWord[1].Fee_u16StatusWord));
	#endif  
    return(oResult);	
}

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: ti_fee_eraseimmediateblock.c
 *********************************************************************************************************************/
