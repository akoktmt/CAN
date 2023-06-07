#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "canframe.h"
extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart1;
uint8_t CAN_Send_Dataframe(CANConfigIDTxtypedef* pIDtype, uint8_t *Data, uint32_t Datalength)
{
	CAN_TxHeaderTypeDef Txheader;
/*Config Frame----------------------------------------------------------------*/	
	Txheader.DLC=8;
	Txheader.RTR=CAN_RTR_DATA;
	Txheader.IDE=CAN_ID_STD;
/*Config ID-------------------------------------------------------------------*/	
	uint32_t Txmailbox;
	uint16_t ID_NUM = 0x00;
	uint8_t Message_ID = pIDtype->MessageType;
	uint8_t Target_ID=pIDtype->TargetNode;
	uint8_t Frame_type=FIRST_FRAME;
	ID_NUM |= Message_ID;
	ID_NUM =(ID_NUM <<4)|Target_ID;
/*Implement send data----------------------------------------------------------*/	
		uint8_t* frame = (uint8_t*)malloc(CAN_MAX_DATA_LENGTH);  
    uint32_t frameLength = 0;  
		uint32_t length = Datalength;
    int isFirstFrame = 1;
		int isLastFrame=0;
		uint32_t startTime = HAL_GetTick();
/*Add SenderID vs Data length at first frame-----------------------------------*/    
    for (int i = 0; i < Datalength; i++) 
		 {
        uint8_t byte = Data[i];
         if (isFirstFrame) 
					{
            frame[frameLength] = pIDtype->SenderID;
            frameLength++;
            frame[frameLength] = length;
            frameLength++;
            isFirstFrame = 0;
					}
/*Add byte into frame data----------------------------------------------------*/
        frame[frameLength] = byte;
        frameLength++;  
/*Check if frame data is not fill, add FILL byte until frame full 8bytes------*/				
        if (frameLength == CAN_MAX_DATA_LENGTH || i == Datalength - 1) 
				{  					
             while (frameLength < CAN_MAX_DATA_LENGTH)
							{
                frame[frameLength] = FILL_VALUE;
                frameLength++;
							}
/*Check last frame------------------------------------------------------*/ 
						if(i == Datalength - 1)
							{ 
								isLastFrame=1;
								ID_NUM=(ID_NUM <<3)|END_FRAME;
							}
						if(isLastFrame==0){
								ID_NUM =(ID_NUM <<3)|Frame_type;
							}
						Txheader.StdId=ID_NUM;
/*send data--------------------------------------------------------------------*/
            if(HAL_CAN_AddTxMessage(&hcan,&Txheader,frame,&Txmailbox)!=HAL_OK)
							{
								Error_Handler();
							}
/*Check if a transmission request is pending on the selected TxMailboxes------*/			
						while(HAL_CAN_IsTxMessagePending(&hcan,Txmailbox))        
/*Decrease data frame and set frame turn 0 again------------------------------*/							
            memset(frame, 0, CAN_MAX_DATA_LENGTH);
            frameLength = 0;        
/*add SenderID for every 1st next frame---------------------------------------*/						
            frame[0] = pIDtype->SenderID;
            frameLength++;
						ID_NUM=ID_NUM>>3;
						Frame_type++;
        }
			}
    free(frame);  
}
/*uint8_t CAN_Receive_Dataframe(CAN_RxHeaderTypeDef *RxHeader, uint8_t *Data)
{
		while(! HAL_CAN_GetRxFifoFillLevel(&hcan,CAN_RX_FIFO0))
		
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, RxHeader, Data) != HAL_OK)
    {
        Error_Handler();
        return 0; 
    }
    return 1;
}*/
/*CAN Receive Data---------------------------------------------------------------------------------------------------------------------------------*/
uint32_t addArrayToBuffer(uint8_t* buffer, uint8_t* array, int size, int* bufferIndex) {
    for (int i = 0; i < size; i++) {
        buffer[*bufferIndex] = array[i];
        (*bufferIndex)++;
    }   
}
uint8_t CAN_Receive_Dataframe(CANConfigIDRxtypedef* pIDtype, uint32_t Datalength)
{
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t frame[CAN_MAX_DATA_LENGTH] = {0};
    uint8_t isLastFrame = 0;
		uint8_t SenderId=0;
		uint8_t frameLength=0;
		uint32_t ExpectedLength = 0;
	  uint8_t ReceivedBuffer[MAX_BUFFER_SIZE];
    uint32_t Index = 0;
		uint8_t isReceive= 0;
	while(!isLastFrame){
    while (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0);
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, frame) != HAL_OK)
    {
        Error_Handler();
    }
    uint16_t ID_NUM = RxHeader.StdId;
    uint8_t Frame_type = ID_NUM & 0x07;
    uint8_t Target_ID = (ID_NUM >> 3) & 0x0F;
    uint8_t  Message_ID= (ID_NUM >> 7) & 0x0F;
		if(Frame_type==FIRST_FRAME)
		{
			SenderId=frame[0];
			ExpectedLength=frame[1];
			frameLength=2;
		}
		else if(Frame_type!=FIRST_FRAME&&Frame_type!=END_FRAME)
		{
			SenderId=frame[0];
			frameLength=1;
		}
		else if(Frame_type==END_FRAME)
		{
			SenderId=frame[0];
			frameLength=1;
			isLastFrame=1;
		}
		for (frameLength; frameLength < CAN_MAX_DATA_LENGTH; frameLength++) {
			 if(frame[frameLength]!=FILL_VALUE || SenderId==pIDtype->SenderID){
        ReceivedBuffer[Index] = frame[frameLength];
        Index++;
			 }
    }
	frameLength=0;	
}
	HAL_UART_Transmit(&huart1,(uint8_t*)ReceivedBuffer,20,HAL_MAX_DELAY);
	
}
//uint16_t CAN_Send_Request()
//{
//	uint32_t Txmailbox;
//	CAN_TxHeaderTypeDef Txheader;
//	Txheader.DLC=8;
//	Txheader.RTR=CAN_RTR_DATA;
//	Txheader.IDE=CAN_ID_STD;
//	Txheader.StdId=REQUEST_FRAME;
//	uint8_t frame[8];
//	if(HAL_CAN_AddTxMessage(&hcan,&Txheader,frame,&Txmailbox)!=HAL_OK)
//	{
//		Error_Handler();
//	}
//	while(HAL_CAN_IsTxMessagePending(&hcan,Txmailbox));
//}
uint16_t CAN_RECEIVE_ACK()
{
	CAN_RxHeaderTypeDef Rxheader;
	uint8_t frame[8];
	 while (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0)
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &Rxheader, frame) != HAL_OK)
    {
        Error_Handler();
    } 
}
void CAN_Config_filtering(void)
{
		CAN_FilterTypeDef Can_filter_init;
		Can_filter_init.FilterActivation=	ENABLE;
		Can_filter_init.FilterBank=0;
		Can_filter_init.FilterFIFOAssignment=CAN_RX_FIFO0;
		Can_filter_init.FilterIdHigh= 0x0000;
		Can_filter_init.FilterIdLow= 0x0000;
		Can_filter_init.FilterMaskIdHigh= 0x0000;
		Can_filter_init.FilterMaskIdLow= 0x0000;
		Can_filter_init.FilterMode=CAN_FILTERMODE_IDMASK;
		Can_filter_init.FilterScale=CAN_FILTERSCALE_32BIT;
	if(HAL_CAN_ConfigFilter(&hcan,&Can_filter_init)!=HAL_OK)
	{
		Error_Handler();
	}
}
