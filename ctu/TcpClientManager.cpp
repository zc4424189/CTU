/**
 * @internal
 * @file CTCPClientManager.cpp
 *
 * @endif
 */


#include "TCPClient.h"
#include "TCPClientManager.h"

class CTCPClient g_TCPClnt[TCPCLIENT_MAX_NUM];
struct  Buff StructSendBuff[TCPCLIENT_MAX_NUM];
struct  Buff StructRcvBuff[TCPCLIENT_MAX_NUM];
/*****************************************************************************
 * CTCPClientManager class implementation
 *****************************************************************************/

/**
 * Constructs a CTCPClientManager object and initialises its data.
 */
CTCPClientManager::CTCPClientManager( )
{
	m_nTCPClientNum = 0;
}

CTCPClientManager::~CTCPClientManager( )
{

}

int CTCPClientManager::AddTCPClientObject( char *pHostIP, int nHostPort )
{
	//CTCPClient*  pTCPClnt;

	if( m_nTCPClientNum >= TCPCLIENT_MAX_NUM )
		return 0;

	strcpy( m_TCPClientInfo[m_nTCPClientNum].HostIP, pHostIP );
	m_TCPClientInfo[m_nTCPClientNum].HostPort = nHostPort;
	m_TCPClientInfo[m_nTCPClientNum].nIdx = m_nTCPClientNum;
	m_TCPClientInfo[m_nTCPClientNum].ConnState = csWAIT;
	//pTCPClnt = new class CTCPClient;
	//m_TCPClientInfo[m_nTCPClientNum].pTCPClient = (void*)pTCPClnt;
	m_TCPClientInfo[m_nTCPClientNum].pTCPClient = (void*)&g_TCPClnt[m_nTCPClientNum];
	m_TCPClientInfo[m_nTCPClientNum].m_ExitFlag = 0;

	m_nTCPClientNum++;	
	return 1;
}


int CTCPClientManager::DeleteAllTCPClient( )
{
	//int 			i1;
	//CTCPClient*  	pTCPClnt;

	if( m_nTCPClientNum == 0 )
		return 0;
	/*
	for( i1=0; i1<m_nTCPClientNum; i1++ )
	{
		pTCPClnt = (CTCPClient*)m_TCPClientInfo[i1].pTCPClient;
		if( pTCPClnt )
			delete pTCPClnt;
		m_TCPClientInfo[i1].pTCPClient = NULL;
	}
	*/

	m_nTCPClientNum = 0;
	return 1;
}

int CTCPClientManager::Start( )
{
	int					res, i1;
	pthread_attr_t 		attr;

	res = pthread_attr_init(&attr);
	if( res!=0 )
	{
		printf("Create attribute failed\n" );
	}
	// �����̰߳�����
	res = pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );
	// �����̷߳�������
	res += pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
	if( res!=0 )
	{
		printf( "Setting attribute failed\n" );
		return -1;
	}

	// create TCPClient Thread
	for( i1=0; i1<m_nTCPClientNum; i1++ )
	{
		res = pthread_create( &m_thread[i1], &attr, (void *(*) (void *))&TCPClientThreadFunc, (void*)&m_TCPClientInfo[i1] );
		if( res!=0 )
		{
			pthread_attr_destroy( &attr );
			return -1;
		}
	}

	pthread_attr_destroy( &attr );
	return 0;
}

int CTCPClientManager::Stop( )
{
	int		i1;

	for( i1=0; i1<m_nTCPClientNum; i1++ )
	{
		m_TCPClientInfo[i1].m_ExitFlag = 1;
	}

	return 0;
}


int CTCPClientManager::Open( int Idx )
{
	if( Idx>= m_nTCPClientNum )
		return -1;
	if( m_TCPClientInfo[Idx].ConnState!=csWAIT )
		return -1;

	m_TCPClientInfo[Idx].ConnState = csINIT;

	return 0;
}

int	CTCPClientManager::GetTCPClientState( int Idx )
{
	if(Idx >= m_nTCPClientNum )
		return -1;
	return (int)m_TCPClientInfo[Idx].ConnState;
}


int CTCPClientManager::TCPClientThreadFunc( void* lparam )
{
	PTCPCLIENT_INFO		pTCPClntInfo = (PTCPCLIENT_INFO)lparam;
	CTCPClient*      	pTCPClnt;
	int                 ConnectNum=0, TimeCnt=0;
	unsigned char       Buf[2560];
	int                 len,i;

	//������¼�����
	fd_set 				fdRead;
	int 				ret;
	//�����¼��ȴ�ʱ��
	struct timeval		aTime;

	pTCPClnt = (CTCPClient*)pTCPClntInfo->pTCPClient;
	
	for( ; ; )
	{
		usleep(100000);
		i=0;
		if(StructRcvBuff[pTCPClntInfo->nIdx].in==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
		{
			StructRcvBuff[pTCPClntInfo->nIdx].in=0;
		}
		pthread_mutex_lock(&pTCPClnt->mutexRevcBuff);
		while(pTCPClnt->RecvBuff[i]!='\0')
		{
			StructRcvBuff[pTCPClntInfo->nIdx].buff[StructRcvBuff[pTCPClntInfo->nIdx].in] =pTCPClnt->RecvBuff[i];
			StructRcvBuff[pTCPClntInfo->nIdx].in++;
			if(StructRcvBuff[pTCPClntInfo->nIdx].in==BUFFSIZE)
			{
				StructRcvBuff[pTCPClntInfo->nIdx].in=0;
			}
		}
		pthread_mutex_unlock(&pTCPClnt->mutexRevcBuff);
		if(  pTCPClntInfo->m_ExitFlag )
		{
			pTCPClntInfo->m_ExitFlag = 0;
			if( pTCPClntInfo->ConnState > csINIT )
			{
				pTCPClnt->Close( );
			}
			break;
		}

		if( pTCPClntInfo->ConnState == csWAIT )
		{
			sleep( 1 );
			continue;
		}

		aTime.tv_sec = 0;
		aTime.tv_usec = 0;      // for wait 100ms
		//�ÿ�fdRead�¼�Ϊ��
		FD_ZERO( &fdRead );
		//���ö��¼�
		FD_SET( 0,&fdRead );
		//����select�������ж��Ƿ��ж��¼�����
		ret = select( 0,&fdRead,NULL,NULL,&aTime );

		switch( pTCPClntInfo->ConnState )
		{
		case csWAIT:
			pTCPClntInfo->ConnState = csINIT;
			break;
		case csINIT:							                 //  Open TCP Client Connect
			pTCPClnt->Open( pTCPClntInfo->HostIP, pTCPClntInfo->HostPort  );
			pTCPClntInfo->ConnState = csCLOSED;
			printf( "TCPClnt Connect...\n" );
			ConnectNum = 0;
			break;
		case csCLOSED:								           // wait for TCP connection establish...
			if( pTCPClnt->Connect( ) )
			{
				pTCPClntInfo->ConnState = csOPEN;
				printf( "TCPClnt Opened\n" );
				ConnectNum = 0;
				TimeCnt = 0;
			}
			else
			{
				ConnectNum++;			
			}
			if( ConnectNum > 0 )
			{
				pTCPClnt->Close(  );
				pTCPClntInfo->ConnState = csWAIT;
			}
			break;
		case csOPEN:							  // TCP connection is established
			if( pTCPClnt->m_sockclose )
			{
				pTCPClntInfo->ConnState = csWAIT;
			}
			TimeCnt++;
			//��ʱ�������ݣ�ÿ�μ������Ϊ100ms
			if( TimeCnt >= 1 )       // for 3 seconds
			{

				TimeCnt = 0;
				i=0;
				if((pTCPClntInfo->nIdx)<0)//����������С��1ֱ���˳�
				{
					len = -1;
				}
				pthread_mutex_lock(&StructSendBuff[pTCPClntInfo->nIdx].mutex);//��������
				if(StructSendBuff[pTCPClntInfo->nIdx].out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
				{
					StructSendBuff[pTCPClntInfo->nIdx].out=0;
				}
				while(StructSendBuff[pTCPClntInfo->nIdx].in!=StructSendBuff[pTCPClntInfo->nIdx].out)
				{
					Buf[i]=StructSendBuff[pTCPClntInfo->nIdx].buff[StructSendBuff[pTCPClntInfo->nIdx].out];
					StructSendBuff[pTCPClntInfo->nIdx].out++;
					i++;
					if(StructSendBuff[pTCPClntInfo->nIdx].out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
					{
						StructSendBuff[pTCPClntInfo->nIdx].out=0;
					}
				}
				pthread_mutex_unlock(&StructSendBuff[pTCPClntInfo->nIdx].mutex);
				len = i;


				len = pTCPClnt->SendData( Buf, len );

				if( len<0 )
				{
					printf( "SendData failed!\n");
					pTCPClnt->Close(  );
					pTCPClntInfo->ConnState = csWAIT;
				}
			}
			break;
		}
	}

	printf( "TCPClientThreadFun finished\n");
	pthread_exit( NULL );
	return 0;
}
int CTCPClientManager::SendCharsToSendBuff(unsigned char *p,int index,int length)
{
	int i=0;
	if(length>=2047)
	{
		return -1;
	}
	if(index<0)//����������С��1ֱ���˳�
	{
		return -1;
	}
	pthread_mutex_lock(&StructSendBuff[index].mutex);//��������
	if(StructSendBuff[index].in==BUFFSIZE)//�ж�д��ָ���Ƿ�Խ��
	{
		StructSendBuff[index].in=0;
	}
	for(i=0;i<length;i++)
	{

		if(p[i]=='\0')
		{
			return i;
		}
		StructSendBuff[index].buff[StructSendBuff[index].in]=p[i];
		StructSendBuff[index].in++;
		if(StructSendBuff[index].in==BUFFSIZE)
		{
			StructSendBuff[index].in=0;
		}
	}
	pthread_mutex_unlock(&StructSendBuff[index].mutex);
	return i;
}


int CTCPClientManager::RcveCharsFromRcveBuff(unsigned char *p,int index)
{
	int i=0;
	if(index<0)//����������С��1ֱ���˳�
	{
		return -1;
	}
	pthread_mutex_lock(&StructRcvBuff[index].mutex);//��������
	if(StructRcvBuff[index].out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
	{
		StructRcvBuff[index].out=0;
	}
	while(StructRcvBuff[index].in!=StructRcvBuff[index].out)
	{
		p[i]=StructRcvBuff[index].buff[StructRcvBuff[index].out];
		StructRcvBuff[index].out++;
		if(StructRcvBuff[index].out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
		{
			StructRcvBuff[index].out=0;
		}
	}
	pthread_mutex_unlock(&StructRcvBuff[index].mutex);
	return i;
}