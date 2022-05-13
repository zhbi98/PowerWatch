
#include "gd32f10x.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "led.h"
#include "time.h"
#include "log.h"
#include "st7789.h"
#include "ina226.h"

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

int main()
{
    // SystemInit()->system_clock_config()->system_clock_108m_hxtal();
    sys_clock_config();
    led1_gpio_init();
    led2_gpio_init();
    usart_init();
    st7789_init();
    INA226_Init();

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
        led_controller_handler(&led2);

        // info("Helo, World!");
        // sleep_ms(25);

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

        get_power();
        usb_fs_send_fmt_string("voltageVal:%.2fmV\n", ina226_data.voltageVal);
        sleep_ms(100);
        usb_fs_send_fmt_string("Shunt_voltage:%.2fuV\n", ina226_data.Shunt_voltage);
        sleep_ms(100);
        usb_fs_send_fmt_string("Shunt_Current:%.2fmA\n", ina226_data.Shunt_Current);
        sleep_ms(100);
        usb_fs_send_fmt_string("Power1:%.2fmW\n", ina226_data.Power);
        sleep_ms(100);
        usb_fs_send_fmt_string("Power2:%.2fmW\n", ina226_data.Power_Val);
        sleep_ms(100);
    }

    return 0;
}
