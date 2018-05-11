
#include "HQSTcpService.h"


// 创建PCB
void TcpServiceCreate(TcpServiceHQSPCBIP_t *namePcbIP)
{
	struct tcp_pcb *pcb;
	namePcbIP->namePcb = tcp_new(); //创建PCB
	if (namePcbIP->namePcb)
	{
		tcp_setprio(namePcbIP->namePcb , TCP_PRIO_MIN);  //设置优先及
		tcp_bind(namePcbIP->namePcb, IP_ADDR_ANY, namePcbIP->local_port); //绑定本地地址及端口

		namePcbIP->namePcb = tcp_listen(namePcbIP->namePcb); //监听
		tcp_accept(namePcbIP->namePcb, TcpServerAcceptCB);

		tcp_arg(namePcbIP->namePcb, namePcbIP); //传递参数
	}
}


//新的链接
err_t TcpServerAcceptCB(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	TcpServiceHQSPCBIP_t *namePcbIP;
	namePcbIP =(TcpServiceHQSPCBIP_t *) arg;
	struct tcp_pcb_listen *lpcb = (struct tcp_pcb_listen*)(namePcbIP->namePcb);

	/* Decrease the listen backlog counter */
	tcp_accepted(lpcb);  //减小监听累计计数器

	tcp_setprio(newpcb, TCP_PRIO_MIN);


	tcp_recv(newpcb, TcpServerRecvCB);
	tcp_err(newpcb,  TcpServerErrCB);
	tcp_poll(newpcb, TcpServerPollCB, 1);
	tcp_sent(newpcb, TcpServerSendCB);




	/***********************************
	客户端链接上了服务器
	此时记录LWIP分配 客户端 的PCB，
	也可通过查询LWIP 活动的PCB 获得 （tcp_active_pcbs）
	************************************/
	TcpServiceHQSPCBIP_t * tmp;
	tmp = (TcpServiceHQSPCBIP_t *)(newpcb->callback_arg);
	tmp->namePcb = newpcb;
	tmp->remote_ip = newpcb->remote_ip;
	tmp->remote_port = newpcb->remote_port;

	return ERR_OK;  //一定返回 不然LWIP 判断是错误 
}


//发送 回调
err_t TcpServerSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len)
{

}


//接收 当远程主机成功接收（也就是应答信号）到数据时，该函数指定的回调函数被调用；发送数据并且被远端主机确认
err_t TcpServerRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if ( (err != ERR_OK) || (p == NULL)) //接收错误 或者 空数据  最后直接关闭链接
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
	/*接收数据成功*/



	return ERR_OK;
}


//轮回 回调
err_t  TcpServerPollCB(void *arg, struct tcp_pcb *tpcb)
{
	
}


//错误处理 回调
void TcpServerErrCB(void *arg, err_t err)
{


}



//关闭链接
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




//直接发送(谨慎使用)
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
