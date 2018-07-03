/*
 * IEC104.h
 *
 *  Created on: 2018��7��3��
 *      Author: 15645
 */

#ifndef IEC104_H_
#define IEC104_H_
#include "includs.h"
#define TESTFR_CON    0x43 //����ȷ��
#define TESTFR_ACT    0x83//���Լ���
#define STOPDT_CON    0x13//ֹͣȷ��
#define STOPDT_ACT    0x23//ֹͣ����
#define STARTDT_CON   0x07//��ʼȷ��
#define STARTDT_ACT   0x0B//��ʼ����
#define U_FRM         0X03//u��
#define S_FRM         0x01//s��
#define I_FRM         0x00//i��

#define DL_104_T0     30 //T0��ʱ
#define DL_104_T1     15 //
#define DL_104_T2     10
#define DL_104_T3     20

#define DOT_TYPE_YX 1
#define DOT_TYPE_YC 2
#define DOT_TYPE_YM 3
//T1���ͷ�����һ��I��ʽ���Ļ�U��ʽ���ĺ󣬱�����t1��ʱ���ڵõ����շ����Ͽ�,���������ر�����
//T2�ڽ��յ�I��ʽ���ĺ�������t2ʱ��δ���յ��µ�I��ʽ���ģ���������ͷ�����S��ʽ֡,���Ѿ����յ���I��ʽ���Ľ����Ͽɣ���Ȼt2����С��t1��
//T3��վRTU��ÿ����һ֡I֡��S֡����U֡�����´�����ʱ��t3������t3��δ���յ��κα��ģ�����Է����Ͳ�����·֡TESTFR

#define DL_MAX_SEND_I_PAG 12
#define DL_MAX_REV_I_PAG  8

#ifndef BYTE
typedef unsigned char BYTE;
#endif


enum STI104             //��վ�������ͱ�־
{
	M_SP_NA_1 	= 1	,	//����ң�ű�λ
	M_SP_TA_1 	= 2	,	//����ң�ű�λ��ʱ��
	M_DP_NA_1 	= 3	,	//˫��ң�ű�λ
	M_DP_TA_1 	= 4	,	//˫��ң�ű�λ��ʱ��
	M_ST_NA_1 	= 5	,	//����λ����Ϣ
	M_ST_TA_1 	= 6	,	//����ʱ��Ĳ���λ����Ϣ
	M_BO_NA_1 	= 7	,	//32λ���ش�
	M_BO_TA_1 	= 8	,	//����ʱ���32λ���ش�
	M_ME_NA_1 	= 9	,	//��Ʒ�������Ĺ�һ��ֵ
	M_ME_TA_1 	= 10 ,	//����ʱ���Ʒ�������Ĺ�һ��ֵ
	M_ME_NB_1 	= 11 ,  //��Ʒ�������ı���ϵ��
	M_ME_TB_1 	= 12 ,  //����ʱ���Ʒ�������ı���ϵ��
	M_ME_NC_1 	= 13 ,  //�̸�����
	M_ME_TC_1 	= 14 ,  //����ʱ��Ķ̸�����
	M_IT_NA_1 	= 15 ,  //�ۼ�ֵ
	M_IT_TA_1 	= 16 ,  //����ʱ����ۼ�ֵ
	M_EP_TA_1 	= 17 ,  //��ʱ��ļ̵籣�����غ�բ�豸�����¼�
	M_EP_TB_1 	= 18 ,  //��ʱ��ļ̵籣��װ�ó��������¼�
	M_EP_TC_1 	= 19 ,  //��ʱ��ļ̵籣��װ�ó��������·��Ϣ�¼�
	M_PS_NA_1 	= 20 ,  //����״̬��λ����ĳ��鵥����Ϣ
	M_ME_ND_1 	= 21 ,  //����Ʒ�������Ĺ�һ��ֵ
	M_SP_TB_1 	= 30 ,  //�� CP56Time2a ʱ��ĵ�����Ϣ
	M_DP_TB_1 	= 31 ,  //�� CP56Time2a ʱ���˫����Ϣ
	M_ST_TB_1 	= 32 ,  //�� CP56Time2a ʱ��Ĳ�λ����Ϣ
	M_BO_TB_1 	= 33 ,  //�� CP56Time2a ʱ��� 32 ���ش�
	M_ME_TD_1 	= 34 ,  //�� CP56Time2a ʱ��Ĳ���ֵ��һ��ֵ
	M_ME_TE_1 	= 35 ,  //�� CP56Time2a ʱ��Ĳ���ֵ��Ȼ�ֵ
	M_ME_TF_1	= 36 ,  //�� CP56Time2a ʱ��Ĳ���ֵ�̸�����
	M_IT_TB_1	= 37 ,  //�� CP56Time2a ʱ����ۼ���
	M_EP_TD_1	= 38 ,  //�� CP56Time2a ʱ��ļ̵籣���豸�¼�
	M_EP_TE_1	= 39 ,  //�� CP56Time2a ʱ��ļ̵籣���豸���������¼�
	M_EP_TF_1	= 40 ,  //�� CP56Time2a ʱ��ļ̵籣��װ�ó��������·��Ϣ

	M_EI_NA_1 	= 70   //��ʼ������

};


enum MTI104                 //��վ�������ͱ�־
{
	C_SC_NA_1	= 45	,	//	����ң��
	C_DC_NA_1	= 46	,	//	˫��ң��
	C_RC_NA_1	= 47	,	//	��������
	C_SE_NA_1 	= 48	,	//	�趨��һ��ֵ����
	C_SE_NB_1 	= 49	,	//	�趨����ϵ��ֵ����
	C_SE_NC_1 	= 50	,	//	�趨������ֵ����
	C_BO_NA_1	= 51	,	//	32λ���ش�
	C_SC_TA_1 	= 58	,	//	����ʱ�굥��ң��(CP56)
	C_DC_TA_1 	= 59	,	//	����ʱ��˫��ң��(CP56)
	C_RC_TA_1	= 60	,	//	����ʱ����������(CP56)
	C_SE_TA_1	= 61	,	//	����ʱ���趨��һ��ֵ����(CP56)
	C_SE_TB_1 	= 62	,	//	����ʱ���趨����ϵ��ֵ����(CP56)
	C_SE_TC_1 	= 63	,	//	����ʱ���趨������ֵ����(CP56)
	C_BO_TA_1 	= 64	,	//	����ʱ��32λ���ش�(CP56)
	C_IC_NA_1 	= 100	,	//	���ٻ�
	C_CI_NA_1 	= 101	,	//	���������ٻ�����
	C_RD_NA_1 	= 102	,	//	����������
	C_CS_NA_1 	= 103	,	//	ʱ��ͬ������
	C_TS_NA_1 	= 104	,	//	��������
	C_RP_NA_1 	= 105	,	//	��λ��������
	C_CD_NA_1 	= 106	,	//	��ʱ�������
	C_TS_TA_1 	= 107	,	//	����ʱ���������
	P_ME_NA_1 	= 110	,	//	��һ��ֵ�Ĳ���
	P_ME_NB_1 	= 111	,	//	����ϵ���Ĳ���
	P_ME_NC_1 	= 112	,	//	������ֵ�Ĳ���
	P_AC_NA_1 	= 113		//	�����ļ���

};

enum COT104               //����ԭ��
{
	PER_CRC_104 = 1	,     //����ѭ��per cyc
	BACK_104 = 2	,     //����ɨ��back
	SPONT_104 = 3	,     //ͻ��spont
	INIT_104 = 4	,     //��ʼ��init
	REQ_104 = 5	,         //��������� req
	ACT_104 = 6	,         //����act
	ACTCON_104 = 7	,     //����ȷ��actcon
	DEACT_104 = 8	,     //ֹͣ����deact
	DEACTCON_104 = 9	, //ֹͣ����ȷ��deactcon
	ACTTERM_104 = 10	, //�������actterm
	RETREM_104 = 11	,     //Զ����������ķ�����Ϣretrem
	RETLOC_104 = 12	,     //������������ķ�����Ϣretloc
	FILE_104 = 13	,     //�ļ�����file
	INTROGEN_104 = 20	, //��Ӧ���ٻ�introgen
	REQCOGCN = 37	,     //��Ӧ���������ٻ�reqcogcn
	REQCON1 = 38	,     //��Ӧ�� 1��������ٻ�reqco1
	REQCON2 = 39	,     //��Ӧ�� 2��������ٻ�reqco2
	REQCON3 = 40	,     //��Ӧ�� 3��������ٻ�reqco3
	REQCON4 = 41	,     //��Ӧ�� 4��������ٻ�reqco4

	UNDEFINE_TI = 44     ,   //δ���崫������
	UNDEFINE_COT = 45     ,   //δ���崫��ԭ��
	UNDEFINE_COMM_ADDR = 46 ,     //δ֪�Ĺ�����ַ
    UNDEFINE_INFO_ADDR = 47     //δ֪����Ϣ��ַ
};

// CP56Time2a ʱ��ṹ�嶨��
typedef struct CP56TIME2A {
	BYTE  ByteYear ;       //��
	BYTE  ByteMonth ;      //��
	BYTE  ByteDay ;        //��
	BYTE  ByteHour ;       //ʱ
	BYTE  ByteMin ;        //��
	BYTE  ByteSec ;        //��
	BYTE  ByteMilliSec ;   //����
};



typedef struct IEC104_SIQ //��Ʒ�������ʵĵ�����Ϣ
{
	BYTE ByteSPI :1;
	BYTE ByteRES :2;
	BYTE ByteBL :1; // blocked/not blocked
	BYTE ByteSB:1; // substituted/not substituted
	BYTE ByteNT :1; // not topical/topical
	BYTE ByteIV :1; // valid/invalid
};

typedef struct IEC104_DIQ //��Ʒ�������ʵĵ�����Ϣ
{
	BYTE ByteSPI :1;
	BYTE ByteRES :2;
	BYTE ByteBL :1; // blocked/not blocked
	BYTE ByteSB:1; // substituted/not substituted
	BYTE ByteNT :1; // not topical/topical
	BYTE ByteIV :1; // valid/invalid
};

typedef struct IEC104_QDS
{
    unsigned char var :2;
    unsigned char res :2;
    unsigned char bl :1; // blocked/not blocked
    unsigned char sb :1; // substituted/not substituted
    unsigned char nt :1; // not topical/topical
    unsigned char iv :1; // valid/invalid
};
typedef struct _EXTRACTFRM_INFO
{
	BYTE ByteFrmType ;    //֡���� ���� U /I /S
	BYTE ByteTranType ;   //��������  ��ӦSTI104 MTI104 ��U��ʽ��6������
	short ByteTranCot ;    //����ԭ��  ��ӦCOT104
	short ByteRevS ;       //�������
	short ByteSendS ;      //�������
	BYTE  ByteVar   ;      //���������ṹ�����õ�
	BYTE  ByteSQNum ;      //�ɱ�ṹ�޶���
    short  ByteAPDUaddr ;   //APDU��ַ
    BYTE* pinfo   ;      //��Ϣ����Ϣ

}EXTRACTFRM_INFO;

//��վ��Ϣ��ṹ ���忪ʼ


//��վ��Ϣ��ṹ �������
typedef struct _APCI_104
{
	BYTE bHead ;      //0x68
	BYTE bAPDUlen ;   //APDU�ĳ��� ��󳤶�Ϊ253
	BYTE bCtlArr1 ;   //������8λλ��1
	BYTE bCtlArr2 ;   //������8λλ��2
	BYTE bCtlArr3 ;   //������8λλ��3
	BYTE bCtlArr4 ;   //������8λλ��4

}APCI_104;
class IEC104 {
public:
	IEC104();
	virtual ~IEC104();
};

#endif /* IEC104_H_ */