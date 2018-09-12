#ifndef __XSCOM_P10_REGS_H__
#define __XSCOM_P10_REGS_H__

/* Core FIR (Fault Isolation Register) */
#define P10_CORE_FIR		0x440

/* Core WOF (Whose On First) */
#define P10_CORE_WOF		0x448

#define P10_EC_CORE_THREAD_STATE	0x412 /* XXX P10 is this right? */
#define P10_THREAD_STOPPED(t)		PPC_BIT(56 + (t))

#define P10_EC_THREAD_INFO		0x413
#define P10_THREAD_ACTIVE(t)		PPC_BIT(t)

#define P10_EC_RAS_STATUS		0x454
#define P10_THREAD_MAINT(t)		PPC_BIT(0 + 8*(t))
#define P10_THREAD_QUIESCED(t)		PPC_BIT(1 + 8*(t))
#define P10_THREAD_ICT_EMPTY(t)		PPC_BIT(2 + 8*(t))

#define P10_EC_DIRECT_CONTROLS		0x449
#define P10_THREAD_STOP(t)		PPC_BIT(7 + 8*(t))
#define P10_THREAD_START(t)		PPC_BIT(6 + 8*(t))
#define P10_THREAD_SRESET(t)		PPC_BIT(4 + 8*(t))
#define P10_THREAD_CLEAR_MAINT(t)	PPC_BIT(3 + 8*(t))
#define P10_THREAD_PWR(t)		PPC_BIT(32 + 8*(t))

#define P10_QME_FIR			0x000

#define P10_QME_SPWU_HYP		0x83c
#define P10_SPWU_REQ			PPC_BIT(0)
#define P10_SPWU_DONE			PPC_BIT(4)

#define P10_QME_SSH_HYP			0x82c
#define P10_SSH_CORE_GATED		PPC_BIT(0)
#define P10_SSH_SPWU_DONE		PPC_BIT(1)

#endif /* __XSCOM_P10_REGS_H__ */
