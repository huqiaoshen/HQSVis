/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/17
* @brief   TcpClient 相关.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "HQSTcpClient.h"


// 创建PCB
void TcpClientCreate(TcpClientHQSPCBIP_t *namePcbIP)
{
	namePcbIP->state = 0;
	namePcbIP->namePcb = tcp_new();
	if (namePcbIP->namePcb)
	{
		tcp_bind(namePcbIP->namePcb, IP_ADDR_ANY, namePcbIP->local_port);
		//链接服务器 
		tcp_connect(namePcbIP->namePcb, &(namePcbIP->remote_ip), namePcbIP->remote_port, TcpClientCallBack);
		tcp_arg(namePcbIP->namePcb, namePcbIP); //传递参数
	}

}

                                    



//接受回调函数
err_t TcpClientCallBack(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	if (err == ERR_OK)
	{
		tcp_recv(tpcb, TcpClientRecvCB);    //注册接受回调函数
		tcp_err(tpcb, TcpClientErrCB);      //注册错误回调函数
		tcp_sent(tpcb, TcpClientSendCB);    //注册发送回调函数
		tcp_poll(tpcb, TcpClientPollCB, 1); //注册轮调回调函数
		//链接上服务端
		((TcpClientHQSPCBIP_t *)(tpcb->callback_arg))->state = 1;

	}
	else
	{

	}
}




//接收 回调
err_t TcpClientRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if ((err != ERR_OK) || (p == NULL)) //接收错误 或者 空数据  最后直接关闭链接
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

//回调 回调
err_t TcpClientSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len)
{


}

//轮回 回调
err_t  TcpClientPollCB(void *arg, struct tcp_pcb *tpcb)
{


}

//错误处理 回调
void TcpClientErrCB(void *arg, err_t err)
{


}


//关闭连接 赋空
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
		namePcbIP->state = 0; //未连接
	}
}

//直接发送
err_t TCPClientSend(TcpClientHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length)
{
	err_t err;
	if (namePcbIP->namePcb->state == ESTABLISHED)
	{
		namePcbIP->state = 1; //已连接
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
		namePcbIP->state = 0; //未连接
	}
	return err;
}