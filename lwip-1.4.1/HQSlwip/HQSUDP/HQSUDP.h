/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/17
* @brief   UDP ���.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "HQSlwip.h"
#include "lwip/udp.h"
#include "HQS_typedef.h"

void UdpRemoteipInit(void);

void UdpSetRemoteip(void);

//ѯ��ģʽ ����(�ص�����)
void Udp_QueryRecv(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	ip_addr_t *addr, u16_t port);

//����
void Udp_QuerySend_Data();


//����
void Udp_Send_Data();


//�ر�
void Udp_Conn_Close();



