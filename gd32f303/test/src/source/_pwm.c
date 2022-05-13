
/**
 * how to use
 *
 * #include "timer.h"
 *
 * int main()
 * {
 *     pwm_init();
 *
 *     while (1) {
 *
 *     }
 * }
 */

#include "_pwm.h"

void _pwm_gpio_init()
{
    rcu_periph_clock_enable(_PWM_CLOCK);
    gpio_pin_remap_config(GPIO_TIMER1_FULL_REMAP, ENABLE);
    gpio_init(_PWM_GPIO, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, _PWM_PIN);
}

void _timers_init()
{
    // TIMER1CLK       = 80M
    uint32_t period_cnt = 24; // yuv 24 correct
    timer_oc_parameter_struct timer_out_init;
    timer_parameter_struct time_init;

    rcu_periph_clock_enable(_TIMER_CLOCK);
    timer_deinit(_TIMER);

    time_init.prescaler         = 0;
    time_init.alignedmode       = TIMER_COUNTER_EDGE;
    time_init.counterdirection  = TIMER_COUNTER_UP;
    time_init.period            = period_cnt - 1;
    time_init.clockdivision     = TIMER_CKDIV_DIV1;
    time_init.repetitioncounter = 0;
    timer_init(_TIMER, &time_init);

    // CH0 config in pwm mode
    timer_out_init.outputstate  = TIMER_CCX_ENABLE;
    timer_out_init.outputnstate = TIMER_CCXN_DISABLE;
    timer_out_init.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_out_init.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_out_init.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_out_init.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(_TIMER, _TIMER_CH, &timer_out_init);

    timer_channel_output_pulse_value_config(_TIMER, _TIMER_CH, period_cnt / 2);
    timer_channel_output_mode_config(_TIMER, _TIMER_CH, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(_TIMER, _TIMER_CH, TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(_TIMER, ENABLE);

    timer_auto_reload_shadow_enable(_TIMER);
    timer_enable(_TIMER);
}

void _pwm_init()
{
    pwm_gpio_init();
    timers_init();
}

void _pwm_out(unsigned int pwmv)
{
    timer_channel_output_pulse_value_config(_TIMER, _TIMER_CH, pwmv);
}

/**
 * How to output pwm:
 * TIMER   :select TIMER 
 * TIMER_CH:PWM output channel
 * value   :pwm width value
 * timer_channel_output_pulse_value_config(TIMER, TIMER_CH, value);
 */
