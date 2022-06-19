
#include "Meas.h"

Average average = {
    .sum = 0.0,
    .avg = 0.0,
    .type = 0,
};

struct data_pool_t avg_pool;

void electricalAverage()
{
    pool_data_t pool_data;

    if (pool_full(&avg_pool) == true) {
        output_pool(&avg_pool, &pool_data);
        input_pool(&avg_pool, ina226_data.Shunt_Current);

        for (char i = 0; i < 32; i++) {
            average.sum = average.sum + avg_pool.buf[i];
        }

        average.avg = average.sum / 32;
        average.sum = 0;
    } else {
        input_pool(&avg_pool, ina226_data.Shunt_Current);
    }
}

DisplayMode displayMode = {
    .mode = 0,
};

void measLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    measViewCreate(root);

    measAttachEvent(measSence.cont);
    measAttachEvent(measSence.mainShow.cont1);
    measAttachEvent(measSence.mainShow.cont2);
    measAttachEvent(measSence.mainShow.cont3);
}

void measLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, measSence.cont);
    lv_group_add_obj(group, measSence.mainShow.cont1);
    lv_group_add_obj(group, measSence.mainShow.cont2);
    lv_group_add_obj(group, measSence.mainShow.cont3);
}

void measAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, measOnEvent, LV_EVENT_ALL, NULL);
}

const unsigned char * fmt_str[] = {
    "%5.3f", // 1.000
    "%5.2f", // 10.00
    "%5.1f", // 100.0
    "%5.0f", // 1000.
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
        return value / 1000.0;
    else if (value <= 0.0)
        return 0.0;
    else
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
    } else if ((value >= 1000.0) && (value < 10000.0)) {
        return 3;
    }
}

unsigned char get_param_unit(float value)
{
    if (value >= 1000.0)
        return 1;
    return 0;
}

void measUpdate()
{
    static unsigned int i = 20000;

    float fmt = 0.0;
    unsigned char index = 0;
    unsigned char buf[15];

    if (i == 20000) {
        i = 0;
        get_power();

        memset(buf, '\0', 10);
        if (displayMode.mode == 0) {
            fmt = param_fmt(ina226_data.voltageVal);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.mainShow.lableUnit1, "%s", unit_str[0][get_param_unit(ina226_data.voltageVal)]);
        } else if (displayMode.mode == 1) {
            fmt = param_fmt(ina226_data.Shunt_Current);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.mainShow.lableUnit1, "%s", unit_str[1][get_param_unit(ina226_data.Shunt_Current)]);
        } else if (displayMode.mode == 2) {
            fmt = param_fmt(ina226_data.Power);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.mainShow.lableUnit1, "%s", unit_str[2][get_param_unit(ina226_data.Power)]);
        }
        lv_label_set_text_fmt(measSence.mainShow.lableValue1, "%s", buf);

        memset(buf, '\0', 10);
        fmt = param_fmt(average.avg);
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.mainShow.lableValue2, "%s", buf);
        lv_label_set_text_fmt(measSence.mainShow.lableUnit2, "%s", unit_str[1][get_param_unit(average.avg)]);

        int hour = (int)(get_elec_calc_time()) / 3600;
        int min  = (int)(get_elec_calc_time()) % 3600 / 60;
        int sec  = (int)(get_elec_calc_time()) % 3600 % 60;
        memset(buf, '\0', 10);
        snprintf(buf, 13, "TIM:%02d:%02d:%02d", hour, min, sec);
        lv_label_set_text_fmt(measSence.mainShow.lableValue3, "%s", buf);

        memset(buf, '\0', 10);
        if (displayMode.mode == 0) {
            fmt = param_fmt(ina226_data.Shunt_Current);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit1, "%s", unit_str[1][get_param_unit(ina226_data.Shunt_Current)]);
        } else if (displayMode.mode == 1) {
            fmt = param_fmt(ina226_data.voltageVal);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit1, "%s", unit_str[0][get_param_unit(ina226_data.voltageVal)]);
        } else if (displayMode.mode == 2) {
            fmt = param_fmt(ina226_data.Shunt_Current);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit1, "%s", unit_str[1][get_param_unit(ina226_data.Shunt_Current)]);
        }
        lv_label_set_text_fmt(measSence.sidebar.labelValue1, "%s", buf);

        memset(buf, '\0', 10);
        if (displayMode.mode == 0) {
            fmt = param_fmt(ina226_data.Power);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit2, "%s", unit_str[2][get_param_unit(ina226_data.Power)]);
        } else if (displayMode.mode == 1) {
            fmt = param_fmt(ina226_data.Power);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit2, "%s", unit_str[2][get_param_unit(ina226_data.Power)]);
        } else if (displayMode.mode == 2) {
            fmt = param_fmt(ina226_data.voltageVal);
            index = get_param_fmt(fmt);
            snprintf(buf, 10, fmt_str[index], fmt);
            lv_label_set_text_fmt(measSence.sidebar.labelUnit2, "%s", unit_str[0][get_param_unit(ina226_data.voltageVal)]);
        }
        lv_label_set_text_fmt(measSence.sidebar.labelValue2, "%s", buf);

        memset(buf, '\0', 10);
        fmt = param_fmt(get_elec_calc_mah());
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue3, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit3, "%s", unit_str[3][get_param_unit(get_elec_calc_mah())]);

        memset(buf, '\0', 10);
        fmt = param_fmt(get_elec_calc_mwh());
        index = get_param_fmt(fmt);
        snprintf(buf, 10, fmt_str[index], fmt);
        lv_label_set_text_fmt(measSence.sidebar.labelValue4, "%s", buf);
        lv_label_set_text_fmt(measSence.sidebar.labelUnit4, "%s", unit_str[4][get_param_unit(get_elec_calc_mwh())]);
    }
    i++;
}

void measOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == measSence.cont) {
        if (code == LV_EVENT_CLICKED) {
            uiViewLoad("About");
        }
    } else if (obj == measSence.mainShow.cont1) {
        if (code == LV_EVENT_CLICKED) {
            displayMode.mode++;
            if (displayMode.mode > 2)
                displayMode.mode = 0;
        }
    } else if (obj == measSence.mainShow.cont2) {
        if (code == LV_EVENT_CLICKED) {

        }
    } else if (obj == measSence.mainShow.cont3) {
        if (code == LV_EVENT_CLICKED) {
            if (!get_elec_status())
                set_elec_status(1);
            else
                set_elec_status(0);
        } else if (code == LV_EVENT_LONG_PRESSED) {
            elec_calc_clear();
        }
    }
}
