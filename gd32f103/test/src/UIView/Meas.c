
#include "Meas.h"

Energy energy = {
    .mAh  = 0.0,
    .mWh  = 0.0,
};

Average average = {
    .sum = 0.0,
    .avg = 0.0,
};

struct data_pool_t data_pool;

void electricalEnergy()
{
    energy.mAh = energy.mAh + (float)(ina226_data.Shunt_Current * ENERGY_TIME);
    energy.mWh = energy.mWh + (float)(ina226_data.Power * ENERGY_TIME);
}

void electricalAverage()
{
    pool_data_t pool_data;

    if (pool_full(&data_pool) == true) {
        output_pool(&data_pool, &pool_data);
        input_pool(&data_pool, ina226_data.Shunt_Current);

        for (char i = 0; i < 32; i++) {
            average.sum = average.sum + data_pool.buf[i];
        }

        average.avg = average.sum / 32;
        average.sum = 0;
    } else {
        input_pool(&data_pool, ina226_data.Shunt_Current);
    }
}

void measCenterLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    measCenterViewCreate(root);

    measCenterAttachEvent(measSence.cont);
    measCenterAttachEvent(measSence.mainShow.cont1);
    measCenterAttachEvent(measSence.mainShow.cont2);
}

void measCenterLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, measSence.cont);
    lv_group_add_obj(group, measSence.mainShow.cont1);
    lv_group_add_obj(group, measSence.mainShow.cont2);
}

void measCenterAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, measCenterOnEvent, LV_EVENT_ALL, NULL);
}

const unsigned char * fmt_str[] = {
    "%5.3f", // 1.000
    "%5.2f", // 10.00
    "%5.1f", // 100.0
};

const unsigned char * unit_str[][2] = {
    {"mV",   "V"},
    {"mA",   "A"},
    {"mW",   "W"},
    {"mAh", "Ah"},
    {"mWh", "Wh"},
};

float param_fmt(float value)
{
    if (value >= 1000.0)
        return (float)(value / 1000.0);
    return value;
}

unsigned char get_param_fmt(float value)
{
    if ((value >= 0) && (value < 10.0)) {
        return 0;
    } else if ((value >= 10.0) && (value < 100.0)) {
        return 1;
    } else if ((value >= 100.0) && (value < 1000.0)) {
        return 2;
    }
}

unsigned char get_param_unit(float value)
{
    if (value >= 1000.0)
        return 1;
    return 0;
}

void measCenterUpdate()
{
    static unsigned int i = 20000;

    float fmt = 0.0;
    unsigned char index = 0;
    unsigned char buf[12];

    if (i == 20000) {
        i = 0;
        get_power();

        memset(buf, '\0', 10);
        fmt = param_fmt(ina226_data.voltageVal);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.mainShow.lableValue1, "%s", buf);
        lv_label_set_text_fmt(measSence.mainShow.lableUnit1, "%s", unit_str[0][get_param_unit(ina226_data.voltageVal)]);

        memset(buf, '\0', 10);
        fmt = param_fmt(average.avg);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.mainShow.lableValue2, "%s", buf);
        lv_label_set_text_fmt(measSence.mainShow.lableUnit2, "%s", unit_str[1][get_param_unit(average.avg)]);

        memset(buf, '\0', 10);
        fmt = param_fmt(ina226_data.Shunt_Current);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue1, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit1, "%s", unit_str[1][get_param_unit(ina226_data.Shunt_Current)]);

        memset(buf, '\0', 10);
        fmt = param_fmt(ina226_data.Power);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue2, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit2, "%s", unit_str[2][get_param_unit(ina226_data.Power)]);

        memset(buf, '\0', 10);
        fmt = param_fmt(energy.mAh);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue3, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit3, "%s", unit_str[3][get_param_unit(energy.mAh)]);

        memset(buf, '\0', 10);
        fmt = param_fmt(energy.mWh);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue4, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit4, "%s", unit_str[4][get_param_unit(energy.mWh)]);
    }
    i++;
}

void measCenterOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        uiViewLoad("About");
    }
}

