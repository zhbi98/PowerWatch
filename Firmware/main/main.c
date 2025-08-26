/**
 * @file main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "gd32f10x.h"

#include <stdint.h>
#include "led.h"
#include "key.h"
#include "time.h"
#include "log.h"
#include "usbd_cdc.h"
#include "st7789.h"
#include "ina226.h"
#include "gd25q64.h"
#include "temp.h"
#include "ina226.h"
#include "kalman.h"

#include "lvgl.h"
#include "nt_pm.h"
#include "nt_minitask.h"

#include "qflow.h"
#include "blight.h"

#include "dialplateview.h"
#include "dialplate.h"
#include "infosview.h"
#include "infos.h"
#include "recentview.h"
#include "recent.h"

#include "resource.h"

/**********************
 * GLOBAL FUNCTIONS
 **********************/

/**
  * 说明 : 初始化内核时钟(108M)
  * 参数 : 无
  * 返回 : 无
  */ 
void sys_clock_config(void)
{
    /** 使能外部晶振 */
    rcu_osci_on(RCU_HXTAL);
    /** 等待晶振稳定 */
    while (rcu_osci_stab_wait(RCU_HXTAL) != SUCCESS);

    /** 设置PREDV0 */
    rcu_predv0_config(RCU_PREDV0_DIV1);
    /** PLL设置 */
    rcu_pll_config(RCU_PLLSRC_HXTAL, RCU_PLL_MUL9);
    /** 使能PLL */
    rcu_osci_on(RCU_PLL_CK);
    /** 等待PLL稳定 */
    while (rcu_osci_stab_wait(RCU_HXTAL) != SUCCESS);

    /** 总线时钟配置 */
    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV2);
    rcu_apb2_clock_config(RCU_APB2_CKAHB_DIV1); 
    /** 系统时钟源选择 */
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);
    while(rcu_system_clock_source_get() != RCU_SCSS_PLL);

    /** 更新SystemCoreClock全局变量 */
    SystemCoreClockUpdate();
}

/*
-----------------------------------------
    Timing 0.1s

    Prescaler = AHB Clock / Timing Clock
              = 84(MHz) / 50(KHz)
              = 84000000(hz) / 50000(hz)
              = 1680

    T = 1 / f
      = 1(s) / f(Hz)
      = 1000000(us) / 50000(hz)
      = 20(us/times)

    Period = Timing / T
           = 0.1(s) / 20(us/times)
           = 100000(us) / 20(us/times)
           = 5000(times)

-----------------------------------------
    Timing 0.5s
    
    Prescaler = AHB Clock / Timing Clock
              = 84(MHz) / 10(KHz)
              = 84000000(hz) / 10000(hz)
              = 8400

    T = 1 / f
      = 1(s) / f(Hz)
      = 1000000(us) / 10000(hz)
      = 100(us/times)

    Period = Timing / T
           = 0.5(s) / 100(us/times)
           = 500000(us) / 100(us/times)
           = 5000(times)
-----------------------------------------
*/

void _timer_init(uint32_t _prescaler, uint32_t _period)
{
    /**
     * TIMER configuration: generate PWM signals
     * with different duty cycles:
     * TIMERCLK = SystemCoreClock / 120 = 1MHz
     */
    timer_oc_parameter_struct timer_out_init;
    timer_parameter_struct time_init;

    rcu_periph_clock_enable(RCU_TIMER1);
    timer_deinit(TIMER1);

    time_init.prescaler         = _prescaler - 1;
    time_init.alignedmode       = TIMER_COUNTER_EDGE;
    time_init.counterdirection  = TIMER_COUNTER_UP;
    time_init.period            = _period;
    time_init.clockdivision     = TIMER_CKDIV_DIV1;
    time_init.repetitioncounter = 0;
    timer_init(TIMER1, &time_init);

#if 0
    CH0 config in pwm mode
    timer_out_init.outputstate  = TIMER_CCX_ENABLE;
    timer_out_init.outputnstate = TIMER_CCXN_DISABLE;
    timer_out_init.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_out_init.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_out_init.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_out_init.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1,
        SUART_TIMER_CH, &timer_out_init);

    timer_channel_output_pulse_value_config(
        TIMER1, SUART_TIMER_CH, 250);
    timer_channel_output_mode_config(
        TIMER1, SUART_TIMER_CH, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(
        TIMER1, SUART_TIMER_CH, TIMER_OC_SHADOW_DISABLE);
    timer_primary_output_config(TIMER1, ENABLE);
    timer_auto_reload_shadow_enable(TIMER1);
#endif

    nvic_irq_enable(TIMER1_IRQn, 1, 1);
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);
    timer_enable(TIMER1);
}

void TIMER1_IRQHandler()
{
    if (timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP) == SET) {
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
        lv_tick_inc(1);
        nt_task_tick_inc(1);

        QFLOW_TICK_INC(1);
        QFLOW_TAKE(
            ina226_filte_get_cur(), 
            ina226_filte_get_pow());
        qflow_work();
    }
}

void ina226_update()
{
    ina226_filte_work();
    qflow_dura_work();
}

void key_update()
{
    switch (key_read_event()) {
    case KEY1_EVT:
        lcd_light_state_reset();
        break;
    case KEY2_EVT:
        lcd_light_state_reset();
        break;
    case KEY3_EVT:
        lcd_light_state_reset();
        break;
    case KEY4_EVT:
        lcd_light_state_repeat();
        break;
    }
    lcd_light_state_work();
    led_light_work(&led1);
    led_light_work(&led2);
    avg_filte_work();
}

extern lv_indev_t * indev_keypad;

int main()
{
    /*SystemInit()->system_clock_config()->system_clock_108m_hxtal();*/
    sys_clock_config();
    _timer_init(960, 100); /*Timer tick 1ms*/
    led_gpio_init();
    key_gpio_init();
    usart_init();
    usb_cdc_init();
    st7789_init();
    INA226_Init();
    inside_temp_adc_init();
    gd25q64_spi_gpio_init();

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    lv_group_t * group = lv_group_create();
    lv_indev_set_group(indev_keypad, group);
    lv_group_set_default(group);

    /** 定义一个活动屏幕, 否则 `lv_disp_set_bg_color` 屏幕背景颜色设置无效 */
    lv_obj_t * scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_disp_set_bg_color(
        lv_disp_get_default(), 
        lv_color_white()
        /*lv_color_black()*/
    );

    _nt_resource_init();

    _nt_view_pointer_init(&dialplateview);
    _nt_view_pointer_init(&recentview);
    _nt_view_pointer_init(&infosview);
    _NT_START_PAGE(dialplateview);

    nt_task_add(ina226_update, 50, 50);
    nt_task_add(key_update, 100, 100);

    for (;;) {
        lv_task_handler();
        nt_task_handler();
    }

    return 0;
}
