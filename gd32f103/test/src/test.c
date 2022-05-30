
#include "gd32f10x.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "led.h"
#include "time.h"
#include "log.h"
#include "st7789.h"
#include "ina226.h"
#include "gd25q64.h"
#include "lvgl.h"

lv_obj_t * container;
lv_obj_t * button;
lv_obj_t * button2;
lv_obj_t * label;
lv_obj_t * label2;
lv_obj_t * sswitch;
lv_obj_t * slider;
lv_obj_t * bar;

// custom_hid
// #include "custom_hid_core.h"

// cdc_acm
#include "cdc_acm_core.h"

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

extern uint8_t packet_sent, packet_receive;
extern uint32_t receive_length;
extern uint8_t usb_data_buffer[CDC_ACM_DATA_PACKET_SIZE];

usbd_core_handle_struct  usb_device_dev = 
{
    .dev_desc = (uint8_t *)&device_descriptor,
    .config_desc = (uint8_t *)&configuration_descriptor,
    .strings = usbd_strings,
    .class_init = cdc_acm_init,
    .class_deinit = cdc_acm_deinit,
    .class_req_handler = cdc_acm_req_handler,
    .class_data_handler = cdc_acm_data_handler
};

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable USB pull-up pin clock */ 
    rcu_periph_clock_enable(RCC_AHBPeriph_GPIO_PULLUP);

    /* configure USB model clock from PLL clock */
    rcu_usb_clock_config(RCU_CKUSB_CKPLL_DIV2);

    /* enable USB APB1 clock */
    rcu_periph_clock_enable(RCU_USBD);
}

/*!
    \brief      configure the gpio peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
// void gpio_config(void)
// {
//     /* configure usb pull-up pin */
//     gpio_init(USB_PULLUP, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, USB_PULLUP_PIN);
// }

/*!
    \brief      configure interrupt priority
    \param[in]  none
    \param[out] none
    \retval     none
*/
void nvic_config(void)
{
    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);

    /* enable the USB low priority interrupt */
    nvic_irq_enable(USBD_LP_CAN0_RX0_IRQn, 1, 0);
}

void usb_fs_send_string(unsigned char * string)
{
    unsigned char len = strlen(string);

    memcpy(usb_data_buffer, string, len);
    cdc_acm_data_send(&usb_device_dev, len);
}

void usb_fs_send_fmt_string(unsigned char * format, ...)
{
    unsigned char value[64];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    usb_fs_send_string(value);
}

#define LVGL_TIMER         TIMER1
#define LVGL_TIMER_CLOCK   RCU_TIMER1
#define LVGL_TIMER_CH      TIMER_CH_3
#define LVGL_TIMER_IRQN    TIMER1_IRQn
#define LVGL_TIMER_HANDLER TIMER1_IRQHandler

/*
This gd32 or stm32 mcu timer parm settings 
    TIM_Period    -->     times
    TIM_Prescaler --> prescaler
-----------------------------------------
    Timing 0.5s

    0.5(s) = 500000(us)
    500000 / 5000(times) = 100(us/times)

    T = 1000000(us) / f = 100(us)
    f = 10000(hz)

    84000000(Hz) / prescaler = 10000(hz)
    prescaler = 84000000(hz) / 10000(hz)
              = 8400

    计时 1ms 即 T = 1ms
    T = 1/f=1000000us/1000Hz = 1000us
    溢出次数 = 计时时间 / T
    48000000(Hz)/1000
-----------------------------------------
*/

extern void lvgl_timer_init(unsigned int prescaler_t, unsigned int period_t);
extern void LVGL_TIMER_HANDLER();

void lvgl_timer_init(unsigned int prescaler_t, unsigned int period_t)
{
    /**
     * TIMER configuration: generate PWM signals
     * with different duty cycles:
     * TIMERCLK = SystemCoreClock / 120 = 1MHz
     */
    timer_oc_parameter_struct timer_out_init;
    timer_parameter_struct time_init;

    rcu_periph_clock_enable(LVGL_TIMER_CLOCK);
    timer_deinit(LVGL_TIMER);

    time_init.prescaler         = prescaler_t - 1;
    time_init.alignedmode       = TIMER_COUNTER_EDGE;
    time_init.counterdirection  = TIMER_COUNTER_UP;
    time_init.period            = period_t;
    time_init.clockdivision     = TIMER_CKDIV_DIV1;
    time_init.repetitioncounter = 0;
    timer_init(LVGL_TIMER, &time_init);

    // CH0 config in pwm mode
    // timer_out_init.outputstate  = TIMER_CCX_ENABLE;
    // timer_out_init.outputnstate = TIMER_CCXN_DISABLE;
    // timer_out_init.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    // timer_out_init.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    // timer_out_init.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    // timer_out_init.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    // timer_channel_output_config(LVGL_TIMER,
    //     SUART_TIMER_CH, &timer_out_init);

    // timer_channel_output_pulse_value_config(
    //     LVGL_TIMER, SUART_TIMER_CH, 250);
    // timer_channel_output_mode_config(
    //     LVGL_TIMER, SUART_TIMER_CH, TIMER_OC_MODE_PWM0);
    // timer_channel_output_shadow_config(
    //     LVGL_TIMER, SUART_TIMER_CH, TIMER_OC_SHADOW_DISABLE);
    // timer_primary_output_config(LVGL_TIMER, ENABLE);
    // timer_auto_reload_shadow_enable(LVGL_TIMER);

    nvic_irq_enable(LVGL_TIMER_IRQN, 1, 1);
    timer_interrupt_enable(LVGL_TIMER, TIMER_INT_UP);
    timer_enable(LVGL_TIMER);
}

void LVGL_TIMER_HANDLER()
{
    if (timer_interrupt_flag_get(LVGL_TIMER, TIMER_INT_FLAG_UP) == SET) {
        timer_interrupt_flag_clear(LVGL_TIMER, TIMER_INT_FLAG_UP);
        // 1ms tick
        // usb_fs_send_fmt_string("%s\n", "LVGL TICK");
        lv_tick_inc(1);
        led_controller_handler(&led2);
    }
}

unsigned char flash_buf[20];

void botton_anim(lv_obj_t * bluetooth)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, bluetooth);
    lv_anim_set_values(&a, -30, 30);
    lv_anim_set_early_apply(&a, true);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_start(&a);
}

int main()
{
    unsigned int i = 0;
    unsigned int percent = 0;
    // SystemInit()->system_clock_config()->system_clock_108m_hxtal();
    sys_clock_config();
    lvgl_timer_init(48000, 1);
    led1_gpio_init();
    led2_gpio_init();
    usart_init();
    st7789_init();
    INA226_Init();
    gd25q64_spi_gpio_init();
    sleep_ms(100);
    // gd25q64_page_write(0x0000, 13, "Hello, World!");
    // gd25q64_sector_erase(0x0000);
    // sleep_ms(100);
    memset(flash_buf, '\0', 20);
    gd2564_buffer_read(0x0000, 13, flash_buf);

    lv_init();
    lv_port_disp_init();
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());
// ---------------- LVGL --------------------------
    container = lv_obj_create(lv_scr_act());
    // lv_obj_remove_style_all(container);
    lv_obj_set_size(container, 320, 170);
    lv_obj_center(container);

    button = lv_btn_create(container);
    lv_obj_set_size(button, 80, 40);
    lv_obj_set_pos(button, 10, 20);
    botton_anim(button);

    label = lv_label_create(button);
    lv_label_set_text_fmt(label, "Click:%d", 0);
    lv_obj_center(label);

    button2 = lv_btn_create(container);
    lv_obj_set_size(button2, 80, 40);
    lv_obj_set_pos(button2, 195, 105);

    label2 = lv_label_create(button2);
    lv_label_set_text_fmt(label2, "Click:%d", 0);
    lv_obj_center(label2);

    sswitch = lv_switch_create(container);
    lv_obj_set_size(sswitch, 80, 40);
    lv_obj_set_pos(sswitch, 165, 20);

    slider = lv_slider_create(container);
    lv_obj_set_size(slider, 105, 15);
    // lv_obj_center(slider);
    lv_obj_set_pos(slider, 140, 70);

    bar = lv_bar_create(container);
    lv_obj_set_size(bar, 105, 15);
    // lv_obj_center(bar);
    lv_obj_set_pos(bar, 55, 100);
// -------------------------------------------------

    /* system clocks configuration */
    rcu_config();

    /* GPIO configuration */
    // gpio_config();

    /* USB device configuration */
    usbd_core_init(&usb_device_dev);

    /* NVIC configuration */
    nvic_config();

    /* enabled USB pull-up */
    gpio_bit_set(USB_PULLUP, USB_PULLUP_PIN);

    /* now the usb device is connected */
    usb_device_dev.status = USBD_CONNECTED;

    for (;;) {
        lv_task_handler();

#if 0 // USART TEST
        info("Helo, World!");
        sleep_ms(25);
#endif

#if 0 // USB CDC ACM TEST
        // if (USBD_CONFIGURED == usb_device_dev.status) {
        //     if (1 == packet_receive && 1 == packet_sent) {
        //         packet_sent = 0;
        //         /* receive datas from the host when the last packet datas have sent to the host */
        //         cdc_acm_data_receive(&usb_device_dev);
        //     } else {
        //         if (0 != receive_length) {
        //             /* send receive datas */
        //             cdc_acm_data_send(&usb_device_dev, receive_length);
        //             receive_length = 0;
        //         }
        //     }
        // }
        // memcpy(usb_data_buffer, "Hello, world!\n", 14);
        // cdc_acm_data_send(&usb_device_dev, 14);
        // sleep_ms(100);
        // memcpy(usb_data_buffer, "Hello, gd32f103!\n", 17);
        // cdc_acm_data_send(&usb_device_dev, 17);
        // sleep_ms(100);
        // memcpy(usb_data_buffer, "Hello, USB virtual usart!\n", 26);
        // cdc_acm_data_send(&usb_device_dev, 26);
        // sleep_ms(100);
        // usb_fs_send_string("GD32F103 USB FS\n");
#endif

#if 0 // INA226 TEST
        usb_fs_send_fmt_string("Bus Voltage  : 0x%04x", INA226_GetVoltage(INA226_ADDR1));
        sleep_ms(2000);
        usb_fs_send_fmt_string("Shunt Voltage: 0x%04x", INA226_GetShuntVoltage(INA226_ADDR1));
        sleep_ms(2000);
        usb_fs_send_fmt_string("Current      : 0x%04x", INA226_GetShunt_Current(INA226_ADDR1));
        sleep_ms(2000);
        usb_fs_send_fmt_string("Power        : 0x%04x", INA226_Get_Power(INA226_ADDR1));
        sleep_ms(2000);
        usb_fs_send_fmt_string("........................");
        sleep_ms(100);

        usb_fs_send_fmt_string("Bus Voltage  : %.3f(mV)", INA226_GetVoltage(INA226_ADDR1) * 1.25);
        sleep_ms(2000);
        usb_fs_send_fmt_string("Shunt Voltage: %.3f(uV)", INA226_GetShuntVoltage(INA226_ADDR1) * 2.5);
        sleep_ms(2000);
        usb_fs_send_fmt_string("Current      : %.3f(mA)", INA226_GetShunt_Current(INA226_ADDR1) * 0.02);
        sleep_ms(2000);
        usb_fs_send_fmt_string("Power        : %.3f(mW)", INA226_Get_Power(INA226_ADDR1) * 0.02 * 25.0);
        sleep_ms(2000);
        // Calcu Current(mA) = Shunt Voltage(mV) / Sampling resistor(Oumu)
        usb_fs_send_fmt_string("Calcu Current: %.3f(mA)", INA226_GetShuntVoltage(INA226_ADDR1) * 2.5 * 0.001 / 0.1);
        sleep_ms(2000);
        usb_fs_send_fmt_string("========================");
        sleep_ms(100);
#endif

#if 0 // IPS SCREEN DISPLAY TEST
        clear(0xFD49);
        sleep_ms(100);
        clear(0xFF95);
        sleep_ms(100);
#endif

#if 0 // GD25Q64 FLASH TEST
        usb_fs_send_fmt_string("FLASH ID: %x\n", gd25q64_read_id());
        sleep_ms(100);
        usb_fs_send_fmt_string("FLASH DATA: %s\n", flash_buf);
        sleep_ms(100);
#endif

#if 1 // LVGL TEST
        lv_label_set_text_fmt(label, "Click:%d", i);
        lv_label_set_text_fmt(label2, "Click:%d", i);
        lv_bar_set_value(slider, i, LV_ANIM_ON);
        lv_bar_set_value(bar, i, LV_ANIM_ON);

        i++;
        if (i > 100) {
            i = 1;
        }
#endif
    }

    return 0;
}

/**
 * Power = Bus Voltage x Current
 * --------------------------------
 * 1(V) x 1(A) = 1W
 * 1(mW) = 0.001(W)
 * 
 * 0.001(V) x 1(A) = 0.001(W) = 1(mW)
 * OR
 * 1(V) x 0.001(A) = 0.001(W) = 1(mW)
 * 
 * 1(mV) x 1(A) = 1(mW)
 * OR
 * 1(V) x 1(mA) = 1(mW)
 */
