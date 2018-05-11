
#include "HQSTcpService.h"


// ����PCB
void TcpServiceCreate(TcpServiceHQSPCBIP_t *namePcbIP)
{
	struct tcp_pcb *pcb;
	namePcbIP->namePcb = tcp_new(); //����PCB
	if (namePcbIP->namePcb)
	{
		tcp_setprio(namePcbIP->namePcb , TCP_PRIO_MIN);  //�������ȼ�
		tcp_bind(namePcbIP->namePcb, IP_ADDR_ANY, namePcbIP->local_port); //�󶨱��ص�ַ���˿�

		namePcbIP->namePcb = tcp_listen(namePcbIP->namePcb); //����
		tcp_accept(namePcbIP->namePcb, TcpServerAcceptCB);

		tcp_arg(namePcbIP->namePcb, namePcbIP); //���ݲ���
	}
}


//�µ�����
err_t TcpServerAcceptCB(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	TcpServiceHQSPCBIP_t *namePcbIP;
	namePcbIP =(TcpServiceHQSPCBIP_t *) arg;
	struct tcp_pcb_listen *lpcb = (struct tcp_pcb_listen*)(namePcbIP->namePcb);

	/* Decrease the listen backlog counter */
	tcp_accepted(lpcb);  //��С�����ۼƼ�����

	tcp_setprio(newpcb, TCP_PRIO_MIN);


	tcp_recv(newpcb, TcpServerRecvCB);
	tcp_err(newpcb,  TcpServerErrCB);
	tcp_poll(newpcb, TcpServerPollCB, 1);
	tcp_sent(newpcb, TcpServerSendCB);




	/***********************************
	�ͻ����������˷�����
	��ʱ��¼LWIP���� �ͻ��� ��PCB��
	Ҳ��ͨ����ѯLWIP ���PCB ��� ��tcp_active_pcbs��
	************************************/
	TcpServiceHQSPCBIP_t * tmp;
	tmp = (TcpServiceHQSPCBIP_t *)(newpcb->callback_arg);
	tmp->namePcb = newpcb;
	tmp->remote_ip = newpcb->remote_ip;
	tmp->remote_port = newpcb->remote_port;

	return ERR_OK;  //һ������ ��ȻLWIP �ж��Ǵ��� 
}


//���� �ص�
err_t TcpServerSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len)
{

}


//���� ��Զ�������ɹ����գ�Ҳ����Ӧ���źţ�������ʱ���ú���ָ���Ļص����������ã��������ݲ��ұ�Զ������ȷ��
err_t TcpServerRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if ( (err != ERR_OK) || (p == NULL)) //���մ��� ���� ������  ���ֱ�ӹر�����
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


//�ֻ� �ص�
err_t  TcpServerPollCB(void *arg, struct tcp_pcb *tpcb)
{
	
}


//������ �ص�
void TcpServerErrCB(void *arg, err_t err)
{


}



//�ر�����
void TcpServerClose(struct tcp_pcb *pcb)
{
	err_t err;
	tcp_recv(pcb, NULL);
	tcp_err(pcb, NULL);
	tcp_poll(pcb, NULL, 0);
	tcp_sent(pcb, NULL);
	err = tcp_close(pcb);
	if (err != ERR_OK) 
	{
		LWIP_DEBUGF(HTTPD_DEBUG, ("Error %d closing %p\n", err, (void*)pcb));
		/* error closing, try again later in poll */
		tcp_poll(pcb, TcpServerPollCB, 1);
	}

}




//ֱ�ӷ���(����ʹ��)
err_t TCPServiceSend(TcpServiceHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length)
{
	err_t err = ERR_OK;
	struct tcp_pcb *cpcb;

	for (cpcb = tcp_active_pcbs; cpcb != NULL; cpcb = cpcb->next)
	{
		if (cpcb->state == ESTABLISHED)
			if (cpcb->local_port == namePcbIP->local_port)
			{
				err_t err = ERR_OK;
				//tcp_write(cpcb, buff, length, TCP_WRITE_FLAG_COPY);
				//tcp_output(cpcb);
			}
	}

	if (namePcbIP->namePcb->state == ESTABLISHED)
	{
		if (tcp_sndbuf(namePcbIP->namePcb) > length)
		{
			tcp_write(namePcbIP->namePcb, buff, length, TCP_WRITE_FLAG_COPY);
			tcp_recved(namePcbIP->namePcb, length);
			tcp_output(namePcbIP->namePcb);

		}

	}

	return err;
}