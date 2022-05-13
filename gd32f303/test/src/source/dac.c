
#include "dac.h"

void dac_gpio_init()
{
    rcu_periph_clock_enable(DAC_CHANEL_CLOCK);
    gpio_init(DAC_CHANEL_GPIO, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, DAC_CHANEL_PIN);
}

void dac_init()
{
    dac_gpio_init();

    rcu_periph_clock_enable(DAC_CLOCK);

    dac_deinit();
    // configure the DAC
    dac_trigger_disable(DAC);
    dac_wave_mode_config(DAC, DAC_WAVE_DISABLE);
    dac_output_buffer_enable(DAC);

    // enable DAC and set data
    dac_enable(DAC);
    dac_data_set(DAC, DAC_ALIGN_12B_L, DAC_OUT_VAL);
}

void dac_put(unsigned int dacv)
{
    dac_data_set(DAC, DAC_ALIGN_12B_L, dacv);
}
