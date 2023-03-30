#ifndef _MW_CV_H_
#define _MW_CV_H_

#include <common.h>

class MwCV_c{
private:
	static MwCV_c *m_pThis;
	ID m_recvTskId;
	ID m_buffId;
public:
	void Init(void);
	void Run(void);
	void Link(void){}
	MwCV_c();
	static void recvTask(void);
	ID getBuffId(void);
};

#endif

