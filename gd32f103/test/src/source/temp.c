
#include "temp.h"

void temp_adc_rcu_config()
{
    /* enable ADC clock */
    rcu_periph_clock_enable(ADC_CLOCK);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV12);
}

/*!
    \brief      configure the ADC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void temp_adc_config()
{
    temp_adc_rcu_config();

    /* ADC SCAN function enable */
    adc_special_function_config(/*ADC0*/CURRENT_ADC, ADC_SCAN_MODE,ENABLE);  
    /* ADC trigger config */
    adc_external_trigger_source_config(/*ADC0*/CURRENT_ADC, ADC_INSERTED_CHANNEL, ADC0_1_2_EXTTRIG_INSERTED_NONE);
    /* ADC data alignment config */
    adc_data_alignment_config(/*ADC0*/CURRENT_ADC, ADC_DATAALIGN_RIGHT);
    /* ADC mode config */
    adc_mode_config(ADC_MODE_FREE);  
    /* ADC channel length config */
    adc_channel_length_config(/*ADC0*/CURRENT_ADC, ADC_INSERTED_CHANNEL, 2);

    /* ADC temperature sensor channel config */
    adc_inserted_channel_config(/*ADC0*/CURRENT_ADC, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_239POINT5);
    /* ADC internal reference voltage channel config */
    adc_inserted_channel_config(/*ADC0*/CURRENT_ADC, 1, ADC_CHANNEL_17, ADC_SAMPLETIME_239POINT5);

    /* ADC external trigger enable */
    adc_external_trigger_config(/*ADC0*/CURRENT_ADC, ADC_INSERTED_CHANNEL,ENABLE);

    /* ADC temperature and Vrefint enable */
    adc_tempsensor_vrefint_enable();
    
    /* enable ADC interface */
    adc_enable(/*ADC0*/CURRENT_ADC);
    sleep_ms(5);    
    /* ADC calibration and reset calibration */
    adc_calibration_enable(/*ADC0*/CURRENT_ADC);
}

int read_temp()
{
#if 1 // GD32F103 TEMP SENSOR TEST
		float temperature = 0.0;
		float vref_value = 0.0;

        adc_software_trigger_enable(CURRENT_ADC, ADC_INSERTED_CHANNEL);
        sleep_ms(100);

        temperature = (1.43 - ADC_IDATA0(CURRENT_ADC)*3.3/4096) * 1000 / 4.3 + 25;
        vref_value = (ADC_IDATA1(CURRENT_ADC) * 3.3 / 4096);

        // usb_fs_send_fmt_string("Temp: %2.0f\n", temperature);
        // sleep_ms(100);
        // usb_fs_send_fmt_string("Vref: %5.3fV\n", vref_value);
        // sleep_ms(500);
        return (int)temperature;
#endif
}