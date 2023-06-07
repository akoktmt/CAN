#include "main.h"
#ifndef CAN_MUTIFRAME_H
#define CAN_MUTIFRAME_H
#define TIMEOUT_MS 5000
#define CAN_MAX_DATA_LENGTH 	(0x08)
#define FILL_VALUE 						(0x55)
#define MAX_BUFFER_SIZE 15
/*-------------------------------------------*/
/** @defgroup CAN_MessType_mode 
  * @{
  */
#define ALL_NODE 							(0x00)
#define COMMAND_FRAME 				(0x01)
#define ACK_COMMAND_FRAME 		(0x02)
#define REMOTE_NOTICE_FRAME 	(0x03)
#define TEST_FRAME 						(0x04)
#define ACK_TEST_FRAME 				(0x05)
/**
  * @}
  */
/*-------------------------------------------*/	
	/** @defgroup CAN_Target_mode 
  * @{
  */
#define ALL_NODE 							(0x00)
#define ENGINE_CONTROL 				(0x01)
#define LIGHT_GPS 						(0x02)
#define MASTER 								(0x03)
#define STEERING 							(0x04)
#define OBSTALCE 							(0x05)
#define POWER 								(0x06)
/**
  * @}
  */
/*-------------------------------------------*/
	/** @defgroup CAN_Frame_mode 
  * @{
  */
#define END_FRAME 						(0x00)
#define FIRST_FRAME 					(0x01)
#define SECOND_FRAME 					(0x02)
#define THIRD_FRAME 					(0x03)
#define FOURTH_FRAME 					(0x04)
#define FIFTH_FRAME 					(0x05)
#define SIX_FRAME 						(0x06)
#define SEVEN_FRAME 					(0X07)
/**
  * @}
  */
/*-------------------------------------------*/	
 /** @defgroup CAN_Sender_mode 
  * @{
  */
#define ALL_NODE 							(0x00)
#define ENGINE_CONTROL 				(0x01)
#define LIGHT_GPS 						(0x02)
#define MASTER 								(0x03)
#define STEERING 							(0x04)
#define OBSTALCE 							(0x05)
#define POWER 								(0x06)
/**
  * @}
  */
/*-------------------------------------------*/
/** @defgroup CAN_TX_Struct 
  * @{
  */
typedef struct {
	CAN_HandleTypeDef* hcan;
	uint16_t MessageType; /*!< @ref CAN_Target_mode */
	uint16_t TargetNode; /*!< @ref CAN_Target_mode */
	uint16_t Frametype; /*!< @ref CAN_Frame_mode */
	uint16_t SenderID; /*!< @ref CAN_Sender_mode */
}CANConfigIDTxtypedef;
/**
  * @}
  */
/*-------------------------------------------*/
/** @defgroup CAN_RX_Struct 
  * @{
  */
typedef struct {
	CAN_HandleTypeDef* hcan;
	uint16_t MessageType;	/*!< @ref CAN_Target_mode */
	uint16_t TargetNode; 	/*!< @ref CAN_Target_mode */
	uint16_t Frametype;		/*!< @ref CAN_Target_mode */
	uint16_t SenderID;		/*!< @ref CAN_Target_mode */
	uint16_t DataLength;
}CANConfigIDRxtypedef;

//typedef struct {
//	CAN_HandleTypeDef* hcan;
//	uint16_t NodeID;
//}

/**
  * @}
  */
#endif