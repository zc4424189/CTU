// TCPCustom.cpp: implementation of the CTCPCustom class.
//
//////////////////////////////////////////////////////////////////////


#include "TCPCustom.h"
#include "TCPServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//���캯��
CTCPCustom::CTCPCustom()
{
   m_SocketEnable = 0;
   m_ExitThreadFlag = 0;
}


//��������
CTCPCustom::~CTCPCustom()
{
   //�ر��߳��˳��¼�
}

/*--------------------------------------------------------------------
���������ܡ�: ���߳����ڼ�����ͻ������ӵ�socketͨѶ���¼������統���յ����ݡ�
			   ���ӶϿ���ͨѶ���̷���������¼�
����ڲ�����: lparam:������ָ�룬����ͨ���˲��������߳��д�����Ҫ�õ�����Դ��
			   ���������ǽ�CTCPCustom��ʵ��ָ�봫����
�����ڲ�����:  (��)
������  ֵ��:   ��
---------------------------------------------------------------------*/
void* CTCPCustom::SocketDataThread(void* lparam)
{
	CTCPCustom *pSocket;
	//�õ�CTCPCustom��ʵ��ָ��
	pSocket = (CTCPCustom*)lparam;

	//������¼�����
	fd_set fdRead;  
	int ret,i;
	struct timeval	aTime;
	aTime.tv_sec = 0;
	aTime.tv_usec = 0;
	while( 1 )
	{
        //�յ��˳��¼��������߳�
		usleep(10000);
		if( pSocket->m_ExitThreadFlag )
		{
			break;
		}
		//�ÿն��¼�����
		FD_ZERO(&fdRead);
		//��pSocket���ö��¼�
		FD_SET(pSocket->m_socketfd, &fdRead );
		//����select�������ж��Ƿ��ж��¼�����
		aTime.tv_sec = 0;
		aTime.tv_usec = 0;
		ret = select(0, &fdRead, NULL, NULL, &aTime);



		
		if( ret<0 )
		{
			//�ر�socket
			close( pSocket->m_socketfd );
			break;
		}
		
		else
		{
			//�ж��Ƿ���¼�
			if(FD_ISSET(pSocket->m_socketfd,&fdRead))
			{
				pSocket->RecvLen = recv(pSocket->m_socketfd, pSocket->RecvBuf, 1024,0);
				if (pSocket->RecvLen < 0 )
				{
					//��ͻ��˶����ӵ�Socket����
					printf( "Socket error\n");
					//�ر�socket
					close(pSocket->m_socketfd);
					break;

				}
				//��ʾ�����Ѿ����ݹر�
				else if( pSocket->RecvLen == 0)
				{
					printf( "Close socket %d\n", pSocket->m_socketfd );
					//�ر�socket
					close(pSocket->m_socketfd);
					break;
				}
				else
				{
					//�Խ��յ����ݽ��д������ݴ��ڼĴ���
					i=0;
					pthread_mutex_lock(&pSocket->StructRcvBuff.mutex);//��������
					if(pSocket->StructRcvBuff.in==BUFFSIZE)//�ж�д��ָ���Ƿ�Խ��
					{
						pSocket->StructRcvBuff.in=0;
					}
					for(i=0;i<pSocket->RecvLen;i++)
					{
						if(pSocket->RecvBuf[i]==0)
						{
							break;
						}
						pSocket->StructRcvBuff.buff[pSocket->StructRcvBuff.in]=pSocket->RecvBuf[i];
						pSocket->StructRcvBuff.in++;
						if(pSocket->StructRcvBuff.in==BUFFSIZE)
						{
							pSocket->StructRcvBuff.in=0;
						}
					}
					pthread_mutex_unlock(&pSocket->StructRcvBuff.mutex);
					pSocket->RecvBuf[pSocket->RecvLen]=0;
					//printf( "RCV:%s\n", pSocket->RecvBuf);
					//TxLen = pSocket->DataPro( TxBuf );

				}
			}							//�������
		}
	}

	printf( "SocketDataThread finished\n");
	pthread_exit( NULL );
	//�ͷ�TCPCustomָ��
	pSocket->m_pTCPServer->RemoveClientSocketObject( (void*)pSocket );
}



/*--------------------------------------------------------------------
���������ܡ�: ��socket������ͨѶ�߳�
����ڲ�����:  pTCPServerָ��������˼���socket
�����ڲ�����:  (��)
������  ֵ��:  1:�򿪳ɹ�;0:��ʧ��
---------------------------------------------------------------------*/
int CTCPCustom::Open(void* lparam)
{
	int					res, flags;
	pthread_attr_t 		attr;

	m_pTCPServer = (CTCPServer*)lparam;

	//����ͨѶ�߳�, ��������������ָ������߳�
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
	}

	res = pthread_create( &m_thread, &attr, SocketDataThread, this );
	if( res!=0 )
	{
		close( m_socketfd );
		return 0;
	}
	pthread_attr_destroy( &attr );


	//����ͨѶģʽΪ�첽ģʽ
	flags = fcntl(m_socketfd, F_GETFL);
	if( (flags<0)||((fcntl(m_socketfd, F_SETFL, flags |O_ASYNC))<0) )
	{
		perror("fcntl");
	}

	m_SocketEnable = 1;
	return 1;
}

/*--------------------------------------------------------------------
���������ܡ�: �ر�socket���ر��̣߳��ͷ�Socket��Դ
����ڲ�����:  (��)
�����ڲ�����:  (��)
������  ֵ��:  1:�ɹ��ر�;0:�ر�ʧ��
---------------------------------------------------------------------*/
int CTCPCustom::Close()
{
	m_ExitThreadFlag = 1;

   //�ر�Socket���ͷ���Դ
   int err = close(m_socketfd);
   if( err<0 )
   {
	   return 0;
   }
   return 1;
}


/*-----------------------------------------------------------------
���������ܡ�: ��ͻ��˷�������
����ڲ�����: buf: �����͵�����
              len: �����͵����ݳ���
�����ڲ�����: (��)
������  ֵ��: >0: �������ݳɹ�, ���������͵����ݳ���; 
              <0: ��������ʧ�ܡ�
------------------------------------------------------------------*/
int CTCPCustom::SendData(const char *buf , int len )
{
	int nBytes = 0;
	int nSendBytes=0;

	while(nSendBytes < len)
	{
	    nBytes = send(m_socketfd,buf+nSendBytes,len-nSendBytes,0);
		if (nBytes<0 )
		{
			return nBytes;
		}

		nSendBytes = nSendBytes + nBytes;
		
		if (nSendBytes < len)
		{
		    sleep(1);
		}
	} 
	return nSendBytes; 
}

int CTCPCustom::SendCharsToSendBuff(unsigned char *p,int length)
{
	int i=0;
	if( length>0 )
	{
		if(this->m_SocketEnable==1)
		{
			try
			{
				SendData((const char*)p,length);
			}
			catch(char *str)
			{
				std::cout << str << std::endl;
			}
		}
	}


/*	if(this==NULL)
	{
		return -1;
	}

	if(length>=2047)
	{
		return -1;
	}

	pthread_mutex_lock(&StructSendBuff.mutex);//��������
	if(StructSendBuff.in==BUFFSIZE)//�ж�д��ָ���Ƿ�Խ��
	{
		StructSendBuff.in=0;
	}
	for(i=0;i<length;i++)
	{

		if(p[i]=='\0')
		{
			return i;
		}
		StructSendBuff.buff[StructSendBuff.in]=p[i];
		StructSendBuff.in++;
		if(StructSendBuff.in==BUFFSIZE)
		{
			StructSendBuff.in=0;
		}
	}
	pthread_mutex_unlock(&StructSendBuff.mutex);

	*/
	return i;
}


int CTCPCustom::RcveCharsFromRcveBuff(unsigned char *p)
{
	unsigned char charsendbuff[BUFFSIZE];
	memset(charsendbuff,0,sizeof(charsendbuff));
	int i=0,TxLen;
	if(this==NULL)
	{
		return -1;
	}
	pthread_mutex_lock(&StructRcvBuff.mutex);//��������
	if(StructRcvBuff.out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
	{
		StructRcvBuff.out=0;
	}
	while(StructRcvBuff.in!=StructRcvBuff.out)
	{
		p[i]=StructRcvBuff.buff[StructRcvBuff.out];
		StructRcvBuff.out++;
		if(StructRcvBuff.out==BUFFSIZE)//�ж϶���ָ���Ƿ�Խ��
		{
			StructRcvBuff.out=0;
		}
		i++;
	}
/*	std::cout<< "�����룺"<< StructRcvBuff.in <<"���ַ�"<<std::endl;
	std::cout<< "�������"<< StructRcvBuff.out <<"���ַ�"<<std::endl;*/
	pthread_mutex_unlock(&StructRcvBuff.mutex);

	return i;
}
