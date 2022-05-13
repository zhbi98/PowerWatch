
#ifndef __TIMER_H__
#define __TIMER_H__

#include "gd32f30x.h"

#include "hub.h"
#include "controller.h"

#define HUB_TIMER         TIMER1
#define HUB_TIMER_CLOCK   RCU_TIMER1
#define HUB_TIMER_CH      TIMER_CH_3
#define HUB_TIMER_IRQN    TIMER1_IRQn
#define HUB_TIMER_HANDLER TIMER1_IRQHandler

extern void hub_timer_init(unsigned int prescaler_t, unsigned int period_t);
extern void HUB_TIMER_HANDLER();

#endif
