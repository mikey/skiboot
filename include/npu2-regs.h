/* Copyright 2013-2016 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NPU2_REGS_H
#define __NPU2_REGS_H

struct npu2;
uint64_t npu2_read4(struct npu2 *p, uint64_t reg);
void npu2_write4(struct npu2 *p, uint64_t reg, uint64_t val);
uint64_t npu2_read(struct npu2 *p, uint64_t reg);
void npu2_write(struct npu2 *p, uint64_t reg, uint64_t val);
void npu2_write_mask(struct npu2 *p, uint64_t reg, uint64_t val, uint64_t mask);

/* These aren't really NPU specific registers but we initialise them in NPU
 * code */
#define MCD0_BANK0_CN3 0x301100d
#define MCD1_BANK0_CN3 0x301140d

#define NPU2_REG_OFFSET(stack, block, offset) \
	(((stack) << 20) | ((block) << 16) | (offset))

#define NPU2_NTL_REG_OFFSET(ndev, offset)				\
	NPU2_REG_OFFSET(NPU2_STACK_STCK_0 + ((ndev)->index >> 1),       \
			NPU2_BLOCK_NTL0 + ((ndev)->index % 2)*2, offset)

#define NPU2_NTLU_REG_OFFSET(ndev, offset)				\
	NPU2_REG_OFFSET(NPU2_STACK_STCK_0U + ((ndev)->index >> 1),       \
			NPU2_BLOCK_NTL0 + ((ndev)->index % 2)*2, offset)

#define NPU2_DL_REG_OFFSET(ndev, offset)	\
	NPU2_REG_OFFSET(((ndev)->index >> 1),				\
			8 + ((ndev)->index % 2)*2, offset)

/* Get the offset for this register */
#define NPU2_REG(reg) \
	((reg) & 0xffff)

/* Get the stack number for this register */
#define NPU2_REG_STACK(reg) \
	(((reg) >> 20) & 0xf)

/* XTS tables */
#define NPU2_XTS_BDF_MAP_SIZE	16
#define NPU2_XTS_PID_MAP_SIZE	256

/* Stacks */
#define NPU2_STACK_STCK_0U	0x0
#define NPU2_STACK_STCK_1U	0x1
#define NPU2_STACK_STCK_2U	0x2
#define NPU2_STACK_STCK_0     	0x4
#define NPU2_STACK_STCK_1     	0x5
#define NPU2_STACK_STCK_2     	0x6
#define NPU2_STACK_MISC		0x7
#define NPU2_STACK_ATSD		0x8
#define NPU2_STACK_PHY00	0xc
#define NPU2_STACK_PHY01	0xd
#define NPU2_STACK_PHY10	0xe
#define NPU2_STACK_PHY11	0xf

/* Link stack blocks */
#define NPU2_BLOCK_SM_0	0x0
#define NPU2_BLOCK_SM_1 0x1
#define NPU2_BLOCK_SM_2 0x2
#define NPU2_BLOCK_SM_3 0x3
#define NPU2_BLOCK_CTL	0x4
#define NPU2_BLOCK_DAT	0x5
#define NPU2_BLOCK_NTL0	0x9
#define NPU2_BLOCK_NTL1	0xb

/* MISC stack blocks */
#define NPU2_BLOCK_ATS	0
#define NPU2_BLOCK_XTS	1
#define NPU2_BLOCK_MISC 2

/* ATSD stack blocks */
#define NPU2_BLOCK_ATSD0	0
#define NPU2_BLOCK_ATSD1	1
#define NPU2_BLOCK_ATSD2	2
#define NPU2_BLOCK_ATSD3	3
#define NPU2_BLOCK_ATSD4	4
#define NPU2_BLOCK_ATSD5	5
#define NPU2_BLOCK_ATSD6	6
#define NPU2_BLOCK_ATSD7	7

/* SM block registers */
#define NPU2_CQ_SM_MISC_CFG0			0x000
#define NPU2_CQ_SM_MISC_CFG1			0x008
#define NPU2_PB_EPSILON				0x010
#define NPU2_TIMER_CFG				0x018
#define NPU2_GPU0_MEM_BAR			0x020
#define NPU2_GPU1_MEM_BAR			0x028
#define   NPU2_MEM_BAR_SEL_MEM			PPC_BITMASK(0,2)
#define   NPU2_MEM_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_MEM_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_MEM_BAR_NODE_ADDR		PPC_BITMASK(10,21)
#define   NPU2_MEM_BAR_ADDR			PPC_BITMASK(0,21)
#define   NPU2_MEM_BAR_POISON			PPC_BIT(22)
#define   NPU2_MEM_BAR_GRANULE			PPC_BIT(23)
#define   NPU2_MEM_BAR_BAR_SIZE			PPC_BITMASK(24,27)
#define   NPU2_MEM_BAR_MODE			PPC_BITMASK(28,31)
#define   NPU2_MEM_BAR_MASK			PPC_BITMASK(33,39)
#define NPU2_PHY_BAR				0x030
#define   NPU2_PHY_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_PHY_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_PHY_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_PHY_BAR_NODE_ADDR		PPC_BITMASK(10,30)
#define   NPU2_PHY_BAR_ADDR			PPC_BITMASK(3,30)
#define NPU2_GENID_BAR				0x038
#define   NPU2_GENID_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_GENID_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_GENID_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_GENID_BAR_NODE_ADDR		PPC_BITMASK(10,35)
#define   NPU2_GENID_BAR_ADDR			PPC_BITMASK(3,35)
#define   NPU2_GENID_BAR_POISON			PPC_BIT(39)
#define NPU2_LOW_WATER_MARKS			0x040
#define NPU2_HIGH_WATER_MARKS			0x048
#define NPU2_RELAXED_ORDERING_CFG0		0x050
#define NPU2_RELAXED_ORDERING_CFG1		0x058
#define NPU2_RELAXED_ORDERING_CFG2		0x060
#define NPU2_NTL0_BAR				0x068
#define NPU2_NTL1_BAR				0x070
#define   NPU2_NTL_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_NTL_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_NTL_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_NTL_BAR_NODE_ADDR		PPC_BITMASK(10,35)
#define   NPU2_NTL_BAR_ADDR			PPC_BITMASK(3,35)
#define   NPU2_NTL_BAR_POISON			PPC_BIT(36)
#define   NPU2_NTL_BAR_SIZE			PPC_BITMASK(39,43)
#define NPU2_PERF_CFG				0x078
#define NPU2_INHIBIT_CFG			0x080
#define NPU2_C_ERR_RPT_MSG0			0x088
#define NPU2_C_ERR_RPT_MSG1			0x090
#define NPU2_C_ERR_RPT_MSG2			0x098
#define NPU2_C_ERR_RPT_MSG3			0x0A0
#define NPU2_C_ERR_RPT_MSG4			0x0A8
#define NPU2_CQ_SM_STATUS			0x0B0
#define NPU2_C_ERR_RPT_FIRST0			0x0B8
#define NPU2_C_ERR_RPT_FIRST1			0x0C0
#define NPU2_C_ERR_RPT_FIRST2			0x0C8
#define NPU2_C_ERR_RPT_MASK0			0x0D0
#define NPU2_C_ERR_RPT_MASK1			0x0D8
#define NPU2_C_ERR_RPT_MASK2			0x0E0
#define NPU2_C_ERR_RPT_HOLD0			0x0E8
#define NPU2_C_ERR_RPT_HOLD1			0x0F0
#define NPU2_C_ERR_RPT_HOLD2			0x0F8
#define NPU2_PERF_ADDR_MATCH			0x100
#define NPU2_PERF_MATCH				0x108
#define NPU2_PERF_MASK				0x110
#define NPU2_DBG0_CFG				0x118
#define NPU2_DBG1_CFG				0x120

/* CTL block registers */
#define NPU2_CQ_CTL_MISC_CFG			0x000
#define NPU2_CQ_FUTURE_CFG1			0x008
#define NPU2_CQ_FUTURE_CFG2			0x010
#define NPU2_CQ_FUTURE_CFG3			0x018
#define NPU2_CQ_PERF_MATCH			0x020
#define NPU2_CQ_PERF_MASK			0x028
#define NPU2_CQ_CTL_PMU_CNT			0x030
#define NPU2_CQ_PERF_CFG			0x038
#define NPU2_CQ_DBG0_CFG			0x040
#define NPU2_CQ_DBG1_CFG			0x048
#define NPU2_CQ_BRICK0_BDF2PE_MAP0		0x050
#define NPU2_CQ_BRICK0_BDF2PE_MAP1		0x058
#define NPU2_CQ_BRICK0_BDF2PE_MAP2		0x060
#define NPU2_CQ_BRICK1_BDF2PE_MAP0		0x068
#define NPU2_CQ_BRICK1_BDF2PE_MAP1		0x070
#define NPU2_CQ_BRICK1_BDF2PE_MAP2		0x078
#define    NPU2_CQ_BRICK_BDF2PE_MAP_ENABLE	PPC_BIT(0)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_WILDCARD	PPC_BIT(1)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_PE		PPC_BITMASK(4,7)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_BDF		PPC_BITMASK(8,23)
#define NPU2_CQ_LPC_THRESHOLD_CFG		0x080
#define NPU2_CQ_INHIBIT_CFG			0x088
#define NPU2_CQ_CTL_STATUS			0x090
#define NPU2_CQ_C_ERR_RPT_MSG0			0x0C0
#define NPU2_CQ_C_ERR_RPT_MSG1			0x0C8
#define NPU2_CQ_C_ERR_RPT_FIRST0		0x0D0
#define NPU2_CQ_C_ERR_RPT_FIRST1		0x0D8
#define NPU2_CQ_C_ERR_RPT_MASK0			0x0E0
#define NPU2_CQ_C_ERR_RPT_MASK1			0x0E8
#define NPU2_CQ_C_ERR_RPT_HOLD0			0x0F0
#define NPU2_CQ_C_ERR_RPT_HOLD1			0x0F8

/* DAT block registers */
#define NPU2_CQ_DAT_MISC_CFG			0x008
#define NPU2_CQ_DAT_ECC_CFG			0x010
#define NPU2_CQ_DAT_SCRATCH0			0x018
#define NPU2_CQ_DAT_ECC_STATUS			0x020
#define NPU2_CQ_DAT_ECC_MASK			0x028
#define NPU2_CQ_DAT_ECC_FIRST			0x030
#define NPU2_CQ_DAT_PARITY			0x038
#define NPU2_CQ_DAT_PARITY_MASK			0x040
#define NPU2_CQ_DAT_PARITY_FIRST		0x048
#define NPU2_CQ_DAT_LOGIC			0x050
#define NPU2_CQ_DAT_LOGIC_MASK			0x058
#define NPU2_CQ_DAT_LOGIC_FIRST			0x060
#define NPU2_CQ_DAT_RAS_MSG0			0x068
#define NPU2_CQ_DAT_RAS_MSG1			0x070
#define NPU2_CQ_DAT_DBG0_CFG			0x080
#define NPU2_CQ_DAT_DBG1_CFG			0x088
#define NPU2_CQ_DAT_SCRATCH1			0x0E0
#define NPU2_CQ_DAT_BE_BUF_CTL			0x100
#define NPU2_CQ_DAT_BE_BUF_WORD0		0x108
#define NPU2_CQ_DAT_BE_BUF_WORD1		0x110
#define NPU2_CQ_DAT_BE_BUF_STATUS		0x118
#define NPU2_CQ_DAT_ERR_INJCT			0x130
#define NPU2_CQ_DAT_ERR_RPT_INJCT		0x138
#define NPU2_CQ_DAT_INHIBIT_CFG			0x140

/* NTL block registers */
#define NPU2_NTL_MISC_CFG2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x000)
#define NPU2_NTL_MISC_CFG3(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x008)
#define NPU2_NTL_ERR_HOLD1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x010)
#define NPU2_NTL_ERR_MASK1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x018)
#define NPU2_NTL_ERR_FIRST1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x020)
#define NPU2_NTL_ERR_FIRST1_MASK(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x028)
#define NPU2_NTL_ERR_HOLD2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x030)
#define NPU2_NTL_ERR_MASK2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x038)
#define NPU2_NTL_ERR_FIRST2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x040)
#define NPU2_NTL_ERR_FIRST2_MASK(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x048)
#define NPU2_NTL_SCRATCH2(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x050)
#define NPU2_NTL_SCRATCH(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x058)
#define NPU2_NTL_DBG0(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x060)
#define NPU2_NTL_DBG1(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x068)
#define NPU2_NTL_PERF_CFG(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x070)
#define NPU2_NTL_PERF_CNT(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x078)
#define NPU2_NTL_CREQ_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x080)
#define NPU2_NTL_PRB_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x088)
#define NPU2_NTL_ATR_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x090)
#define NPU2_NTL_RSP_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x098)
#define NPU2_NTL_CRED_DATA(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x0A0)
#define NPU2_NTL_RSP_DATA(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x0A8)
#define NPU2_NTL_PRI_CFG(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x0B0)
#define NPU2_NTL_MISC_CFG1(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x0C0)
#define NPU2_NTL_SCRATCH1(ndev)			NPU2_NTLU_REG_OFFSET(ndev, 0x0D0)
#define NPU2_NTL_LOW_POWER_CFG(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x0E0)
#define NPU2_NTL_DBG_INHIBIT_CFG(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x220)
#define NPU2_NTL_DISPLAY_CTL(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x280)
#define NPU2_NTL_DISPLAY_DATA0(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x288)
#define NPU2_NTL_DISPLAY_DATA1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x290)
#define NPU2_NTL_DISPLAY_DATA2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x298)
#define NPU2_NTL_RAS_ERR_MSG0(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x300)
#define NPU2_NTL_RAS_ERR_MSG1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x308)
#define NPU2_NTL_RAS_ERR_MSG2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x310)
#define NPU2_NTL_RAS_ERR_MSG3(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x318)
#define NPU2_NTL_ECC_ERR_INJCT(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x340)
#define NPU2_NTL_CRED_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x400)
#define NPU2_NTL_PRB_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x410)
#define NPU2_NTL_ATR_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x418)
#define NPU2_NTL_RSP_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x428)
#define NPU2_NTL_CRED_DATA_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x430)
#define NPU2_NTL_RSP_DATA_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x438)
#define NPU2_NTL_CRED_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x440)
#define NPU2_NTL_DBD_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x448)
#define NPU2_NTL_ATSD_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x460)
#define NPU2_NTL_RSP_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x468)
#define NPU2_NTL_CRED_DATA_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x470)
#define NPU2_NTL_RSP_DATA_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x478)
#define NPU2_NTL_RB_CREDIT_RX(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x480)
#define NPU2_NTL_WAB_CREDIT_RX(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x488)
#define NPU2_NTL_CQ_FENCE_STATUS(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x500)
#define NPU2_NTL_DL_CONTROL(ndev)		NPU2_DL_REG_OFFSET(ndev, 0xFFF4)
#define NPU2_NTL_DL_CONFIG(ndev)		NPU2_DL_REG_OFFSET(ndev, 0xFFF8)

/* Misc block registers. Unlike the SM/CTL/DAT/NTL registers above
 * there is only a single instance of each of these in the NPU so we
 * define them as absolute offsets. */
#define NPU2_MISC_DBG_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x000)
#define NPU2_MISC_RELAXTED_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x008)
#define NPU2_MISC_LCO_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x010)
#define NPU2_MISC_OPTICAL_IO_CFG0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x018)
#define NPU2_MISC_ERR_RPT_HOLD			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x020)
#define NPU2_MISC_ERR_RPT_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x028)
#define NPU2_MISC_CFG				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x030)
#define NPU2_MISC_INHIBIT_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x038)
#define NPU2_MISC_FREEZE_ENABLE0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x040)
#define NPU2_MISC_FREEZE_ENABLE1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x048)
#define NPU2_MISC_FENCE_ENABLE0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x050)
#define NPU2_MISC_FENCE_ENABLE1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x058)
#define NPU2_MISC_IRQ_ENABLE0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x060)
#define NPU2_MISC_IRQ_ENABLE1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x068)
#define NPU2_MISC_NPU_VERSION			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x080)
#define NPU2_MISC_ERR_CTL_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x088)
#define NPU2_MISC_RING_ACK_ERR			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x090)
#define NPU2_MISC_IRQ_BASE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x098)
#define NPU2_MISC_ERR_BRICK_GROUP		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0A0)
#define NPU2_MISC_FREEZE_STATE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0A8)
#define NPU2_MISC_FENCE_STATE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0B0)
#define NPU2_MISC_IRQ_REQUEST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0B8)
#define NPU2_MISC_BRICK0_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x100)
#define NPU2_MISC_BRICK0_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x108)
#define NPU2_MISC_BRICK0_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x110)
#define NPU2_MISC_BRICK1_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x118)
#define NPU2_MISC_BRICK1_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x120)
#define NPU2_MISC_BRICK1_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x128)
#define NPU2_MISC_BRICK2_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x130)
#define NPU2_MISC_BRICK2_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x138)
#define NPU2_MISC_BRICK2_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x140)
#define NPU2_MISC_BRICK3_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x148)
#define NPU2_MISC_BRICK3_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x150)
#define NPU2_MISC_BRICK3_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x158)
#define NPU2_MISC_BRICK4_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x160)
#define NPU2_MISC_BRICK4_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x168)
#define NPU2_MISC_BRICK4_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x170)
#define NPU2_MISC_BRICK5_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x178)
#define NPU2_MISC_BRICK5_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x180)
#define NPU2_MISC_BRICK5_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x188)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_ENABLE	PPC_BIT(0)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_PE		PPC_BITMASK(4,7)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_BDF	PPC_BITMASK(8,23)
#define NPU2_MISC_PESTB00			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x200)
#define NPU2_MISC_PESTB01			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x208)
#define NPU2_MISC_PESTB02			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x210)
#define NPU2_MISC_PESTB03			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x218)
#define NPU2_MISC_PESTB04			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x220)
#define NPU2_MISC_PESTB05			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x228)
#define NPU2_MISC_PESTB06			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x230)
#define NPU2_MISC_PESTB07			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x238)
#define NPU2_MISC_PESTB08			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x240)
#define NPU2_MISC_PESTB09			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x248)
#define NPU2_MISC_PESTB10			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x250)
#define NPU2_MISC_PESTB11			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x258)
#define NPU2_MISC_PESTB12			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x260)
#define NPU2_MISC_PESTB13			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x268)
#define NPU2_MISC_PESTB14			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x270)
#define NPU2_MISC_PESTB15			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x278)
#define NPU2_MISC_IRQ_LOG0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x300)
#define NPU2_MISC_IRQ_LOG01			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x308)
#define NPU2_MISC_IRQ_LOG02			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x310)
#define NPU2_MISC_IRQ_LOG03			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x318)
#define NPU2_MISC_IRQ_LOG04			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x320)
#define NPU2_MISC_IRQ_LOG05			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x328)
#define NPU2_MISC_IRQ_LOG06			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x330)
#define NPU2_MISC_IRQ_LOG07			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x338)
#define NPU2_MISC_IRQ_LOG08			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x340)
#define NPU2_MISC_IRQ_LOG09			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x348)
#define NPU2_MISC_IRQ_LOG10			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x350)
#define NPU2_MISC_IRQ_LOG11			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x358)
#define NPU2_MISC_IRQ_LOG12			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x360)
#define NPU2_MISC_IRQ_LOG13			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x368)
#define NPU2_MISC_IRQ_LOG14			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x370)
#define NPU2_MISC_IRQ_LOG15			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x378)

/* ATS block registers */
#define NPU2_ATS_PMU_CTL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x000)
#define NPU2_ATS_PMU_CNT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x008)
#define NPU2_ATS_ERR_INJCT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x010)
#define NPU2_ATS_DBG_CTL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x018)
#define NPU2_ATS_CHICKEN_SWITCH			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x020)
#define NPU2_ATS_ERR_RPT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x028)
#define NPU2_ATS_ERR_RPT_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x030)
#define NPU2_ATS_CTL				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x100)
#define NPU2_ATS_IODA_TBL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x108)
#define   NPU2_ATS_IODA_TBL_TVT			9
#define      NPU2_ATS_IODA_TBL_TVT_TTA		PPC_BITMASK(0,47)
#define      NPU2_ATS_IODA_TBL_TVT_LEVEL	PPC_BITMASK(48,50)
#define      NPU2_ATS_IODA_TBL_TVT_SIZE		PPC_BITMASK(51,55)
#define      NPU2_ATS_IODA_TBL_TVT_PSIZE	PPC_BITMASK(59,63)
#define   NPU2_ATS_IODA_TBL_TCD			10
#define   NPU2_ATS_IODA_TBL_TDR			11
#define   NPU2_ATS_IODA_TBL_TDRMEM		12
#define   NPU2_ATS_IODA_TBL_XLTEA		16
#define   NPU2_ATS_IODA_TBL_AUTOINC		PPC_BIT(0)
#define   NPU2_ATS_IODA_TBL_SELECT		PPC_BITMASK(11,15)
#define   NPU2_ATS_IODA_TBL_INDEX		PPC_BITMASK(54,63)
#define NPU2_ATS_IODA_DATA			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x110)
#define NPU2_ATS_DMA_SYNC			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x118)
#define NPU2_ATS_TCE_KILL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x120)
#define   NPU2_ATS_TCE_KILL_ALL			PPC_BIT(0)
#define   NPU2_ATS_TCE_KILL_ONE			PPC_BIT(2)
#define   NPU2_ATS_TCE_KILL_PENUM		PPC_BITMASK(4, 7)
#define NPU2_ATS_QUIESCE_DMA			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x128)
#define NPU2_ATS_TCE_TIMEOUT_CTL		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x130)
#define NPU2_ATS_ERR_STATUS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x138)
#define NPU2_ATS_ERR_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x140)
#define NPU2_ATS_ERR_FIRST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x148)
#define NPU2_ATS_ERR_FIRST_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x150)

/* XTS block registers */
#define NPU2_XTS_ERR_RPT_STATUS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x000)
#define NPU2_XTS_ERR_RPT_INJCT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x008)
#define NPU2_XTS_ERR_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x010)
#define NPU2_XTS_ERR_FIRST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x018)
#define NPU2_XTS_CFG				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x020)
#define   NPU2_XTS_CFG_MMIOSD			PPC_BIT(1)
#define   NPU2_XTS_CFG_TRY_ATR_RO		PPC_BIT(6)
#define NPU2_XTS_CFG2				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x028)
#define   NPU2_XTS_CFG2_NO_FLUSH_ENA		PPC_BIT(49)
#define NPU2_XTS_DBG_CFG0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x030)
#define NPU2_XTS_DBG_CFG1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x038)
#define NPU2_XTS_PMU_CNT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x040)
#define NPU2_XTS_ATR_MISS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x050)
#define NPU2_XTS_ATR_MISS_CLR			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x058)
#define NPU2_XTS_ATR_MISS2			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x060)
#define NPU2_XTS_MMIO_ATSD0_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x100)
#define NPU2_XTS_MMIO_ATSD1_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x108)
#define NPU2_XTS_MMIO_ATSD2_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x110)
#define NPU2_XTS_MMIO_ATSD3_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x118)
#define NPU2_XTS_MMIO_ATSD4_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x120)
#define NPU2_XTS_MMIO_ATSD5_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x128)
#define NPU2_XTS_MMIO_ATSD6_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x130)
#define NPU2_XTS_MMIO_ATSD7_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x138)
#define NPU2_XTS_BDF_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x4000)
#define   NPU2_XTS_BDF_MAP_VALID		PPC_BIT(0)
#define   NPU2_XTS_BDF_MAP_STACK		PPC_BITMASK(4, 6)
#define   NPU2_XTS_BDF_MAP_BRICK		PPC_BIT(7)
#define   NPU2_XTS_BDF_MAP_BDF			PPC_BITMASK(16, 31)
#define   NPU2_XTS_BDF_MAP_XLAT			PPC_BITMASK(39, 40)
#define   NPU2_XTS_BDF_MAP_LPCR_ISL		PPC_BIT(44)
#define   NPU2_XTS_BDF_MAP_LPCR_TC		PPC_BIT(45)
#define   NPU2_XTS_BDF_MAP_LPARSHORT		PPC_BITMASK(48, 51)
#define   NPU2_XTS_BDF_MAP_LPARID		PPC_BITMASK(52, 63)
#define NPU2_XTS_PID_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8000)
#define   NPU2_XTS_PID_MAP_VALID_ATRGPA0	PPC_BIT(0)
#define   NPU2_XTS_PID_MAP_VALID_ATRGPA1	PPC_BIT(1)
#define   NPU2_XTS_PID_MAP_VALID_ATSD		PPC_BIT(2)
#define   NPU2_XTS_PID_MAP_MSR_DR		PPC_BIT(25)
#define   NPU2_XTS_PID_MAP_MSR_TA		PPC_BIT(26)
#define   NPU2_XTS_PID_MAP_MSR_HV		PPC_BIT(27)
#define   NPU2_XTS_PID_MAP_MSR_PR		PPC_BIT(28)
#define   NPU2_XTS_PID_MAP_MSR_US		PPC_BIT(29)
#define   NPU2_XTS_PID_MAP_MSR_SF		PPC_BIT(30)
#define   NPU2_XTS_PID_MAP_MSR_UV		PPC_BIT(31)
#define   NPU2_XTS_PID_MAP_LPARSHORT		PPC_BITMASK(40, 43)
#define   NPU2_XTS_PID_MAP_PASID       		PPC_BITMASK(44, 63)
#define NPU2_XTS_SEIDR_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8008)
#define NPU2_XTS_AMR_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8010)

/* XTS ATSD block */
#define NPU2_XTS_MMIO_ATSD_LAUNCH		0x000
#define NPU2_XTS_MMIO_ATSD_AVA			0x008
#define NPU2_XTS_MMIO_ATSD_STATUS		0x010

/* ALTD SCOM addresses */
#define NPU2_DD1_MISC_SCOM_IND_SCOM_ADDR	0x38e
#define NPU2_MISC_SCOM_IND_SCOM_ADDR		0x68e
#define  NPU2_MISC_DA_ADDR			PPC_BITMASK(0, 23)
#define  NPU2_MISC_DA_LEN			PPC_BITMASK(24, 25)
#define   NPU2_MISC_DA_LEN_4B			2
#define   NPU2_MISC_DA_LEN_8B			3
#define NPU2_DD1_MISC_SCOM_IND_SCOM_DATA	0x38f
#define NPU2_MISC_SCOM_IND_SCOM_DATA		0x68f

#endif /* __NPU2_REGS_H */
