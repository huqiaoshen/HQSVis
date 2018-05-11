/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/21
* @brief   TCP Service ���.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "lwip/tcp.h"
#include "HQSlwip.h"
#include "HQS_typedef.h"

typedef struct TcpServiceHQSPCBIP_t
{
	struct tcp_pcb *namePcb;
	uint16    local_port;
	ip_addr_t remote_ip;
	uint16    remote_port;
	uint8     state;
}TcpServiceHQSPCBIP_t;


// ����PCB
void TcpServiceCreate(TcpServiceHQSPCBIP_t *namePcbIP);
//void TcpServiceCreate();

//����                 
void TcpServiceListen(TcpServiceHQSPCBIP_t *namePcbIP);

//ֱ�ӷ���(��������)
err_t TCPServiceSend(TcpServiceHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length);

//���ܻص�����
err_t TcpServerAcceptCB(void *arg, struct tcp_pcb *newpcb, err_t err);


//�ر����� �ص� ����



//�ص� �ص�
err_t TcpServerSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len);

//���� �ص�
err_t TcpServerRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

//�ֻ� �ص�
err_t  TcpServerPollCB(void *arg, struct tcp_pcb *tpcb);

//������ �ص�
void  TcpServerErrCB(void *arg, err_t err);



//ֱ�ӷ���
//err_t TCPServiceSend(TcpServiceHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length);







