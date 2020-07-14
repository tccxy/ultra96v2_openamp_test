#ifndef _TEST_H_
#define _TEST_H_



extern XScuGic InterruptController;
extern u32 TxFrame[32];
extern u32 RxFrame[32];

#define INTC_DEVICE_ID		XPAR_SCUGIC_0_DEVICE_ID

int TccInit(void);
int TccStart(void);
int CanInit(void);
int CanSend(void);
int rpmsg_send_cb(void *data, int len);
int TccGetCount(void);
#endif
