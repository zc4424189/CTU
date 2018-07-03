// TCPServer_CE.h: interface for the CTCPServer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "includs.h"

class CTCPServer
{
private:
	pthread_t 	m_thread;      						//ͨѶ�̱߳�ʶ��ID
	//Socket�����߳�
	 static int SocketListenThread( void*lparam );
public:
	int			m_sockfd;							//TCP�������socket
	int			m_ExitThreadFlag;
	int			m_LocalPort;						//���÷���˿ں�
	CTCPServer();
	virtual ~CTCPServer();
	int Open();				    					//��TCP����
	int Close();									//�ر�TCP����
	// ɾ��һ���ͻ��˶������� �ͷ���Դ
	int RemoveClientSocketObject( void* lparam );
	class CTCPCustom* pClientSocket;
};

#endif