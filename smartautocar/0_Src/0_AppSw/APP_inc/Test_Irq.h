/*
 * Test_Irq.h
 *
 *  Created on: 2015. 3. 19.
 *      Author: kimwayne
 */

#ifndef TEST_IRQ_H_
#define TEST_IRQ_H_


#define ISR_PRIORITY_STM			147
#define ISR_PRIORITY_TIMER_1us      148
#define ISR_PRIORITY_TIMER_1ms      149

#define ISR_PRIORITY_ASCLIN0_TX		15
#define ISR_PRIORITY_ASCLIN0_RX		14
#define ISR_PRIORITY_ASCLIN0_ER		13

#define ISR_PRIORITY_ASCLIN1_TX		12
#define ISR_PRIORITY_ASCLIN1_RX		11
#define ISR_PRIORITY_ASCLIN1_ER		10

#define ISR_PRIORITY_CAN0_TX		103
#define ISR_PRIORITY_CAN0_RX		102

#define ISR_PRIORITY_CAN1_TX		101
#define ISR_PRIORITY_CAN1_RX		100

#define ISR_PRIORITY_CAN2_TX		99
#define ISR_PRIORITY_CAN2_RX		98

#define ISR_PRIORITY_CAN3_TX		97
#define ISR_PRIORITY_CAN3_RX		96


 #define ISR_PRIORITY_CCU60_CC60_ICU	  172 // for CCU6
 #define ISR_PRIORITY_CCU60_CC61_ICU	  173 // for CCU6
 #define ISR_PRIORITY_CCU60_CC62_ICU	  174 // for CCU6
 #define ISR_PRIORITY_CCU61_CC60_ICU	  175 // for CCU6


 #define ISR_PRIORITY_SCUERU			  180

 // GTM TIM ICU interrupt
 #define ISR_PRIORITY_GTM_TIM3_7_ICU      171 // GTM TIM27 for ICU
 #define ISR_PRIORITY_GTM_TIM3_6_ICU      170 // GTM TIM26 for ICU
 #define ISR_PRIORITY_GTM_TIM3_5_ICU      169 // GTM TIM25 for ICU
 #define ISR_PRIORITY_GTM_TIM3_4_ICU      168 // GTM TIM25 for ICU

 #define ISR_PRIORITY_GTM_TIM2_7_ICU      167 // GTM TIM27 for ICU
 #define ISR_PRIORITY_GTM_TIM2_6_ICU      165 // GTM TIM26 for ICU
 #define ISR_PRIORITY_GTM_TIM2_5_ICU      164 // GTM TIM25 for ICU
 #define ISR_PRIORITY_GTM_TIM2_4_ICU      163 // GTM TIM24 for ICU
 #define ISR_PRIORITY_GTM_TIM2_3_ICU      162 // GTM TIM23 for ICU
 #define ISR_PRIORITY_GTM_TIM2_2_ICU      161 // GTM TIM22 for ICU
 #define ISR_PRIORITY_GTM_TIM2_1_ICU      160 // GTM TIM21 for ICU
 #define ISR_PRIORITY_GTM_TIM2_0_ICU      159 // GTM TIM20 for ICU

 #define ISR_PRIORITY_GTM_TIM1_7_ICU      158 // GTM TIM17 for ICU
 #define ISR_PRIORITY_GTM_TIM1_6_ICU      157 // GTM TIM16 for ICU
 #define ISR_PRIORITY_GTM_TIM1_5_ICU      156 // GTM TIM15 for ICU
 #define ISR_PRIORITY_GTM_TIM1_4_ICU      155 // GTM TIM14 for ICU
 #define ISR_PRIORITY_GTM_TIM1_3_ICU      154 // GTM TIM13 for ICU
 #define ISR_PRIORITY_GTM_TIM1_2_ICU      153 // GTM TIM12 for ICU
 #define ISR_PRIORITY_GTM_TIM1_1_ICU      152 // GTM TIM11 for ICU
 #define ISR_PRIORITY_GTM_TIM1_0_ICU      151 // GTM TIM10 for ICU

 #define ISR_PRIORITY_GTM_TIM0_7_ICU      149 // GTM TIM07 for ICU
 #define ISR_PRIORITY_GTM_TIM0_6_ICU      148 // GTM TIM06 for ICU
 #define ISR_PRIORITY_GTM_TIM0_5_ICU      147 // GTM TIM05 for ICU
 #define ISR_PRIORITY_GTM_TIM0_4_ICU      146 // GTM TIM04 for ICU
 #define ISR_PRIORITY_GTM_TIM0_3_ICU      145 // GTM TIM03 for ICU
 #define ISR_PRIORITY_GTM_TIM0_2_ICU      144 // GTM TIM02 for ICU
 #define ISR_PRIORITY_GTM_TIM0_1_ICU      143 // GTM TIM01 for ICU
 #define ISR_PRIORITY_GTM_TIM0_0_ICU      142 // GTM TIM00 for ICU
 #define ISR_PRIORITY_ENCODER	  150


 #define ISR_PRIORITY_SENT_CH0             60
 #define ISR_PRIORITY_SENT_CH1             61
 #define ISR_PRIORITY_SENT_CH2             62

 // QSPI priorities

 #define ISR_PRIORITY_QSPI0_RX               34 // DMA CH0 transfer done interrupt priority (QSPI TX DMA done)
 #define ISR_PRIORITY_QSPI1_RX               33 // DMA CH0 transfer done interrupt priority (QSPI TX DMA done)
 #define ISR_PRIORITY_QSPI2_RX               32 // DMA CH1 transfer done interrupt priority (QSPI RX DMA done)
 #define ISR_PRIORITY_QSPI3_RX               31 // DMA CH1 transfer done interrupt priority (QSPI RX DMA done)

 #define ISR_PRIORITY_QSPI0_ERR         0

 #define ISR_PRIORITY_QSPI_TX           ISR_PRIORITY_QSPI0_TX // DMA channel 1
 #define ISR_PRIORITY_QSPI_RX           ISR_PRIORITY_QSPI0_RX // DMA channel 2
 #define ISR_PRIORITY_QSPI_ERR          ISR_PRIORITY_QSPI0_ERR


 #define  ISR_PRIORITY_TIMER			50

#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)

/** \brief extract the priority out of the ISR object */
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)

/** \brief extract the service provider  out of the ISR object */
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)



#endif /* TEST_IRQ_H_ */
