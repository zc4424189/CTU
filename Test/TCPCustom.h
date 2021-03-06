// TCPCustom.h: interface for the CTCPCustom class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _TCPCUSTOM_H
#define _TCPCUSTOM_H

#include "includs.h"

class CTCPCustom
{
public:
	CTCPCustom();
	virtual ~CTCPCustom();
public:
	char  m_RemoteHost[100];					//远程主机IP地址
	int   m_RemotePort;						    //远程主机端口号
	int	  m_socketfd;						     //通讯socket
	int   m_SocketEnable;
	int   m_ExitThreadFlag;
	class CTCPServer*  m_pTCPServer;

private:
    // 通讯线程函数
	pthread_t 	m_thread;      						//通讯线程标识符ID
	static void* SocketDataThread(void* lparam);    //TCP连接数据通讯线程
	struct  Buff StructSendBuff;
	struct  Buff StructRcvBuff;
public:
	int RecvLen;
	char RecvBuf[1500];

	// 打开socket，创建通讯线程
	int Open(void* lparam);
    
	// 关闭socket，关闭线程，释放Socket资源
	int Close();

	// 向客户端发送数据
	int SendData(const char * buf , int len );

	//处理接收数据函数，并将处理结果放在OutDatBuf中，返回OutDatBuf的数据长度。
	int DataPro( char* OutDatBuf );

	int RcveCharsFromRcveBuff(unsigned char *p);

	int SendCharsToSendBuff(unsigned char *p,int length);
};

#endif
