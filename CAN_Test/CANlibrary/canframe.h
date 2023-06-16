#include "main.h"
#ifndef CAN_MUTIFRAME_H
#define CAN_MUTIFRAME_H
#define TIMEOUT_MS 5000
#define CAN_MAX_DATA_LENGTH 				(0x08)
#define FILL_VALUE 							(0x55)
#define MAX_BUFFER_SIZE 					128

#define ALL_NODE 							0b0000
#define COMMAND_FRAME 						0b0001
#define ACK_COMMAND_FRAME 					0b0010
#define REMOTE_NOTICE_FRAME 				0b0011
#define TEST_FRAME 							0b0100
#define ACK_TEST_FRAME 						0b0101

#define ALL_NODE 							0b0000
#define ENGINE_CONTROL						0b0001
#define LIGHT_GPS							0b0010
#define MASTER								0b0011
#define STEERING							0b0100
#define POWER								0b0110
#define OBSTALCE1							0b1000
#define OBSTALCE2							0b1001
#define OBSTALCE3							0b1010
#define OBSTALCE4							0b1011
#define OBSTALCE5							0b1100
#define OBSTALCE6							0b1101
#define OBSTALCE7							0b1110
#define OBSTALCE8							0b1111

#define END_FRAME 						0b000
#define FIRST_FRAME 					0b001
#define SECOND_FRAME 					0b010
#define THIRD_FRAME 					0b011
#define FOURTH_FRAME 					0b100
#define FIFTH_FRAME 					0b101
#define SIX_FRAME 						0b110
#define SEVEN_FRAME 					0b111

typedef struct CAN_HandlerStruct{
	CAN_HandleTypeDef* hcan;
	uint16_t SenderID;
	uint16_t fillterbank;
}CAN_HandlerStruct;
typedef struct {
	uint16_t MessageType;
	uint16_t TargetNode;
	uint16_t Frametype;
	uint8_t ReceivedBuffer[MAX_BUFFER_SIZE];
	uint8_t Index;
	uint8_t SenderID;
	uint8_t ExpectedLength;
	uint8_t frameIndex;
	uint8_t isLastFrame;
}CANConfigIDRxtypedef;
typedef struct {
	uint16_t MessageType;
	uint16_t TargetNode;
	uint16_t Frametype;
	uint16_t SenderID;
}CANConfigIDTxtypedef;
uint8_t CAN_Receive_Dataframe(CAN_HandlerStruct* Canhandle,CANConfigIDRxtypedef* pIDtype,uint8_t *ReceiveData, uint32_t *ReceiveLength);
uint8_t CAN_Send_Dataframe(CAN_HandlerStruct* Canhandle,CANConfigIDTxtypedef* pIDtype, uint8_t *Data, uint32_t Datalength);
uint32_t CAN_Config_filtering(CAN_HandlerStruct *Can, uint16_t NodeID);
uint8_t CAN_Send_Request(CAN_HandlerStruct* canhandler,uint8_t Data);
uint16_t CAN_RECEIVE_ACK(CAN_HandlerStruct* canhandler);
uint8_t CAN_Init(CAN_HandlerStruct* canhandler, CAN_HandleTypeDef* hcan, uint16_t ID);
uint32_t CAN_Config_filtering(CAN_HandlerStruct *Can, uint16_t NodeID);

#endif
