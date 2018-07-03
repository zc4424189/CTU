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
	char  m_RemoteHost[100];					//Զ������IP��ַ
	int   m_RemotePort;						    //Զ�������˿ں�
	int	  m_socketfd;						     //ͨѶsocket
	int   m_SocketEnable;
	int   m_ExitThreadFlag;
	class CTCPServer*  m_pTCPServer;

private:
    // ͨѶ�̺߳���
	pthread_t 	m_thread;      						//ͨѶ�̱߳�ʶ��ID
	static void* SocketDataThread(void* lparam);    //TCP��������ͨѶ�߳�
	struct  Buff StructSendBuff;
	struct  Buff StructRcvBuff;
public:
	int RecvLen;
	char RecvBuf[1500];

	// ��socket������ͨѶ�߳�
	int Open(void* lparam);
    
	// �ر�socket���ر��̣߳��ͷ�Socket��Դ
	int Close();

	// ��ͻ��˷�������
	int SendData(const char * buf , int len );

	//�����������ݺ��������������������OutDatBuf�У�����OutDatBuf�����ݳ��ȡ�
	int DataPro( char* OutDatBuf );

	int RcveCharsFromRcveBuff(unsigned char *p);

	int SendCharsToSendBuff(unsigned char *p,int length);
};

#endif