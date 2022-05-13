
#include "timer.h"

/*
This gd32 or stm32 mcu timer parm settings 
    TIM_Period    -->     times
    TIM_Prescaler --> prescaler
-----------------------------------------
    Timing 0.1s

    0.1(s) = 100000(us)
    100000 / 5000(times) = 20(us/times)

    T = 1000000(us) / f = 20(us)
    f = 50000(hz)

    84000000(hz) / prescaler = 50000(hz)
    prescaler = 84000000(hz) / 50000(hz)
              = 1680
-----------------------------------------
    Timing 0.5s

    0.5(s) = 500000(us)
    500000 / 5000(times) = 100(us/times)

    T = 1000000(us) / f = 100(us)
    f = 10000(hz)

    84000000(hz) / prescaler = 10000(hz)
    prescaler = 84000000(hz) / 10000(hz)
              = 8400
-----------------------------------------
*/

void hub_timer_init(unsigned int prescaler_t, unsigned int period_t)
{
    /**
     * TIMER configuration: generate PWM signals
     * with different duty cycles:
     * TIMERCLK = SystemCoreClock / 120 = 1MHz
     */
    timer_oc_parameter_struct timer_out_init;
    timer_parameter_struct time_init;

    rcu_periph_clock_enable(HUB_TIMER_CLOCK);
    timer_deinit(HUB_TIMER);

    time_init.prescaler         = prescaler_t - 1;
    time_init.alignedmode       = TIMER_COUNTER_EDGE;
    time_init.counterdirection  = TIMER_COUNTER_UP;
    time_init.period            = period_t;
    time_init.clockdivision     = TIMER_CKDIV_DIV1;
    time_init.repetitioncounter = 0;
    timer_init(HUB_TIMER, &time_init);

    // CH0 config in pwm mode
    // timer_out_init.outputstate  = TIMER_CCX_ENABLE;
    // timer_out_init.outputnstate = TIMER_CCXN_DISABLE;
    // timer_out_init.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    // timer_out_init.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    // timer_out_init.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    // timer_out_init.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    // timer_channel_output_config(HUB_TIMER,
    //     SUART_TIMER_CH, &timer_out_init);

    // timer_channel_output_pulse_value_config(
    //     HUB_TIMER, SUART_TIMER_CH, 250);
    // timer_channel_output_mode_config(
    //     HUB_TIMER, SUART_TIMER_CH, TIMER_OC_MODE_PWM0);
    // timer_channel_output_shadow_config(
    //     HUB_TIMER, SUART_TIMER_CH, TIMER_OC_SHADOW_DISABLE);
    // timer_primary_output_config(HUB_TIMER, ENABLE);
    // timer_auto_reload_shadow_enable(HUB_TIMER);

    nvic_irq_enable(HUB_TIMER_IRQN, 1, 1);
    timer_interrupt_enable(HUB_TIMER, TIMER_INT_UP);
    timer_enable(HUB_TIMER);
}

void HUB_TIMER_HANDLER()
{
    if (timer_interrupt_flag_get(HUB_TIMER, TIMER_INT_FLAG_UP) == SET) {
        timer_interrupt_flag_clear(HUB_TIMER, TIMER_INT_FLAG_UP);
        // 1ms interrupt
        if (hub_data_return_time > 0)
            hub_data_return_time--;

        client_exist_timing();
    }
}
