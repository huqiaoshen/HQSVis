#include "HQSUDP.h"


struct udp_pcb * udp_query_pcb;     //用于网络中搜索本机    54504
#define UDP_QUERY_PORT     54504   //端口固定

struct udp_pcb *udp_message_pcb;   //其他通信              44533

// 创建PCB
struct tcp_pcb * UdpCreate(uint16  port)
{
	struct tcp_pcb *namePcb;
	namePcb = udp_new();
	tcp_bind(namePcb, IP_ADDR_ANY, port);
	return namePcb;
}


void UdpRemoteipInit(void)
{			
	udp_query_pcb = udp_new();
	udp_bind(udp_query_pcb, IP_ADDR_ANY, UDP_QUERY_PORT);  //绑定本地IP 固定端口
	udp_recv(udp_query_pcb, Udp_QueryRecv, NULL);


}

void Udp_QueryRecv(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	ip_addr_t *addr, u16_t port)
{
	if (p != NULL)
	{
		udp_sendto(pcb, p, addr, port);
		pbuf_free(p);
		
	}
}



void Udp_QuerySend_Data()
{
	struct pbuf *q = NULL;
	const char* reply = "I'm here ! Are you There ? \n";
	//struct udp_pcb *upcb;
	//struct ip_addr addr;
	//IP4_ADDR(&addr, 192, 168, 1, 242);

	//upcb = udp_new();
	//udp_bind(udp_query_pcb, IP_ADDR_ANY, UDP_QUERY_PORT);

	q = pbuf_alloc(PBUF_TRANSPORT, strlen(reply) + 1, PBUF_RAM);
	if (!q)
	{
		printf("out of PBUF_RAM\n");
		return;
	}
	memset(q->payload, 0, q->len);
	memcpy(q->payload, reply, strlen(reply));
	//udp_sendto(upcb, q, &addr, 8080);
	udp_sendto(udp_query_pcb, q, IP_ADDR_BROADCAST, 8080);
	pbuf_free(q);
}




void Udp_Send_Data(struct udp_pcb *udppcb) 
{
	struct pbuf *ptr;

	//申请内存
	//ptr = pbuf_alloc();

}








