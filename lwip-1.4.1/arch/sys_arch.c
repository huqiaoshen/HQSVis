#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/mem.h"
#include "sys_arch.h"

u32_t LWipTimeClk; //lwipÊ±ÖÓ¼ÆÊýÆ÷
u32_t sys_now(void)
{
	return LWipTimeClk;
}




