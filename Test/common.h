#define PERMS 0777
#define TCPCLIENT_MAX_NUM 8
#define BUFFSIZE 2048

//ȫ�ֵĽṹ�嶨��
struct Buff
{
	unsigned char buff[BUFFSIZE];
	int in;
	int out;
	pthread_mutex_t mutex;
};

//ȫ�ֱ�������
extern int fdjlafodajfiodajfiodajifod;

