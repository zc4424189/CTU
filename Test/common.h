#define PERMS 0777
#define TCPCLIENT_MAX_NUM 8
#define BUFFSIZE 2048

//全局的结构体定义
struct Buff
{
	unsigned char buff[BUFFSIZE];
	int in;
	int out;
	pthread_mutex_t mutex;
};

//全局变量定义
extern int fdjlafodajfiodajfiodajifod;

