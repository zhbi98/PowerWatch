
#include "_dac.h"

void _dac_gpio_init()
{
    rcu_periph_clock_enable(_DAC_CHANEL_CLOCK);
    gpio_init(_DAC_CHANEL_GPIO, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, _DAC_CHANEL_PIN);
}

void _dac_init()
{
    _dac_gpio_init();

    rcu_periph_clock_enable(_DAC_CLOCK);

    dac_deinit();
    // configure the DAC
    dac_trigger_disable(_DAC);
    dac_wave_mode_config(_DAC, DAC_WAVE_DISABLE);
    dac_output_buffer_enable(_DAC);

    // enable DAC and set data
    dac_enable(_DAC);
    dac_data_set(_DAC, DAC_ALIGN_12B_L, _DAC_OUT_VAL);
}

void _dac_put(unsigned int dacv)
{
    dac_data_set(_DAC, DAC_ALIGN_12B_L, dacv);
}

