#include <common.h>

#include "MwCv.h"

class MwNetComm_c{
private:
	static MwNetComm_c *m_pThis;
	ID m_recvTskId;
        ID m_UdpRecvTskId;
	MwCV_c * m_pMwCV;
public:
	void Init(void);
	void Run(void);
	void Link(MwCV_c *pArgMwCV);
	MwNetComm_c();
	static void recvTask(void);
	static void UdpRecverTask(void);
};

