/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/17
* @brief   TcpClient ���.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "HQSTcpClient.h"


// ����PCB
void TcpClientCreate(TcpClientHQSPCBIP_t *namePcbIP)
{
	namePcbIP->state = 0;
	namePcbIP->namePcb = tcp_new();
	if (namePcbIP->namePcb)
	{
		tcp_bind(namePcbIP->namePcb, IP_ADDR_ANY, namePcbIP->local_port);
		//���ӷ����� 
		tcp_connect(namePcbIP->namePcb, &(namePcbIP->remote_ip), namePcbIP->remote_port, TcpClientCallBack);
		tcp_arg(namePcbIP->namePcb, namePcbIP); //���ݲ���
	}

}

                                    



//���ܻص�����
err_t TcpClientCallBack(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	if (err == ERR_OK)
	{
		tcp_recv(tpcb, TcpClientRecvCB);    //ע����ܻص�����
		tcp_err(tpcb, TcpClientErrCB);      //ע�����ص�����
		tcp_sent(tpcb, TcpClientSendCB);    //ע�ᷢ�ͻص�����
		tcp_poll(tpcb, TcpClientPollCB, 1); //ע���ֵ��ص�����
		//�����Ϸ����
		((TcpClientHQSPCBIP_t *)(tpcb->callback_arg))->state = 1;

	}
	else
	{

	}
}




//���� �ص�
err_t TcpClientRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if ((err != ERR_OK) || (p == NULL)) //���մ��� ���� ������  ���ֱ�ӹر�����
	{
		if (p != NULL)
		{
			/* Inform TCP that we have taken the data. */
			tcp_recved(tpcb, p->tot_len);
			pbuf_free(p);
		}
		TcpServerClose(tpcb);
		return ERR_OK;
	}
	/*�������ݳɹ�*/





	return ERR_OK;
}

//�ص� �ص�
err_t TcpClientSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len)
{


}

//�ֻ� �ص�
err_t  TcpClientPollCB(void *arg, struct tcp_pcb *tpcb)
{


}

//������ �ص�
void TcpClientErrCB(void *arg, err_t err)
{


}


//�ر����� ����
void TcpClientClose(TcpClientHQSPCBIP_t *namePcbIP)
{
	err_t err;
//	tcp_abort(namePcbIP->namePcb);
	tcp_arg(namePcbIP->namePcb, NULL);
	tcp_recv(namePcbIP->namePcb, NULL);
	tcp_sent(namePcbIP->namePcb, NULL);
	tcp_err(namePcbIP->namePcb, NULL);
	tcp_poll(namePcbIP->namePcb, NULL, 0);
	err = tcp_close(namePcbIP->namePcb);
	if (err != ERR_OK)
	{
		LWIP_DEBUGF(HTTPD_DEBUG, ("Error %d closing %p\n", err, (void*)pcb));
		/* error closing, try again later in poll */
		tcp_poll(namePcbIP->namePcb, TcpClientPollCB, 1);
	}
	else
	{
		namePcbIP->state = 0; //δ����
	}
}

//ֱ�ӷ���
err_t TCPClientSend(TcpClientHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length)
{
	err_t err;
	if (namePcbIP->namePcb->state == ESTABLISHED)
	{
		namePcbIP->state = 1; //������
		if (tcp_sndbuf(namePcbIP->namePcb) >= length)
		{
			err = tcp_write(namePcbIP->namePcb, buff, length, TCP_WRITE_FLAG_COPY);
			tcp_output(namePcbIP->namePcb);
		}
		else
		{

		}
	}
	else
	{
		//	tcp_close(namePcb);
		tcp_abort(namePcbIP->namePcb);
		TcpClientCreate(namePcbIP);
		TcpClientConnService(namePcbIP);
		namePcbIP->state = 0; //δ����
	}
	return err;
}