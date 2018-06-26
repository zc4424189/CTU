/*
 * CIpcs.h
 *
 *  Created on: 2018年6月24日
 *      Author: 15645
 */

#ifndef CIPCS_H_
#define CIPCS_H_
#define UP_TYPE         1
#define DOWN_TYPE       2
#define MSG_TYPE        5
#define PARA_TYPE       6
#define MANAGEMSG_TYPE  7
#define DEBUGMSG_TYPE   8
#include "includs.h"
typedef struct
{
	unsigned char Char_Type;
	unsigned char Char_Num;
	unsigned char Char_sq;
	unsigned char Char_COT;
	unsigned char Char_PA;
	//这里放信息元素
}ASDU;
typedef struct
{
	unsigned char Char_Start; //其实字符
	int Int_Length;//报文长度
	int Int_NS;//控制域的收计数器
	int Int_NR;//控制域的发计数器
}APDU;
typedef struct _tagDATA_HEADER
{
	int Int_MessgType; //消息类别
	int Int_ChannelType;  //通道类别
	int Int_SourceIndex;  // 數據的大小
	int Int_MessageNo; // 消息队列号
	unsigned char  Char_MessageBuff[256];   // 數據起始地址
	APDU apdu; //APDU信息
}StructMessageBuff;
class CIpcs {

public:
	CIpcs();
	virtual ~CIpcs();
	void myfun();
	int CreatShareMemory(int type,int memorylength,int creatflag);
private:
	#define UP_TYPE         1
	#define DOWN_TYPE       2
	#define MSG_TYPE        5
	#define PARA_TYPE       6
	#define MANAGEMSG_TYPE  7
	#define DEBUGMSG_TYPE   8
	#define UP_PATH         "up_shm"
	#define DOWN_PATH       "down_shm"
	#define MSG_PATH        "msg_shm"
	#define PARA_PATH       "para_shm"
	#define MANAGEMSG_PATH  "managemsg_shm"
	#define DEBUGMSG_PATH   "debugmsg_shm"

	bool Bool_Created;
	class CLogs log;



};

#endif /* CIPCS_H_ */
