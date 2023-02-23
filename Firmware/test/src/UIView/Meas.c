
#include "Meas.h"

DisplayMode displayMode = {
    .cont1_mode = 0,
    .cont2_mode = 0,
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
    lv_indev_wait_release(lv_indev_get_act());
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

void measUpdate()
{
    /********************************
     *         MAIN SHOW
     *******************************/
    switch (displayMode.cont1_mode) {
    case 0:
        data_curation_handler(ina226_data.voltageVal, FMT_VOLTAGE);
        break;
    case 1:
        data_curation_handler(ina226_data.Shunt_Current, FMT_CURRENT);
        break;
    case 2:
        data_curation_handler(ina226_data.Power, FMT_POWER);
        break;
    }
    lv_label_set_text_fmt(measSence.mainShow.labelValue1, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.mainShow.labelUnit1, "%s", curation.unit_buf);

    switch (displayMode.cont2_mode) {
    case 0:
        data_curation_handler(average_calc.average, FMT_VOLTAGE);
        break;
    case 1:
        data_curation_handler(average_calc.average, FMT_CURRENT);
        break;
    case 2:
        data_curation_handler(average_calc.average, FMT_POWER);
        break;
    }
    lv_label_set_text_fmt(measSence.mainShow.labelValue2, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.mainShow.labelUnit2, "%s", curation.unit_buf);

    unsigned char buf[15];
    memset(buf, '\0', 15);
    int hour = (int)(get_elec_calc_time()) / 3600;
    int min  = (int)(get_elec_calc_time()) % 3600 / 60;
    int sec  = (int)(get_elec_calc_time()) % 3600 % 60;
    snprintf(buf, 13, "TIM:%02d:%02d:%02d", hour, min, sec);
    lv_label_set_text_fmt(measSence.mainShow.labelValue3, "%s", buf);

    /********************************
     *        SIDE BAR
     *******************************/
    switch (displayMode.cont1_mode) {
    case 0:
        data_curation_handler(ina226_data.Shunt_Current, FMT_CURRENT);
        break;
    case 1:
        data_curation_handler(ina226_data.voltageVal, FMT_VOLTAGE);
        break;
    case 2:
        data_curation_handler(ina226_data.Shunt_Current, FMT_CURRENT);
        break;
    }
    lv_label_set_text_fmt(measSence.sidebar.labelValue1, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.sidebar.labelUnit1, "%s", curation.unit_buf);

    switch (displayMode.cont1_mode) {
    case 0:
        data_curation_handler(ina226_data.Power, FMT_POWER);
        break;
    case 1:
        data_curation_handler(ina226_data.Power, FMT_POWER);
        break;
    case 2:
        data_curation_handler(ina226_data.voltageVal, FMT_VOLTAGE);
        break;
    }
    lv_label_set_text_fmt(measSence.sidebar.labelValue2, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.sidebar.labelUnit2, "%s", curation.unit_buf);

    data_curation_handler(get_elec_calc_mah(), FMT_MAH);
    lv_label_set_text_fmt(measSence.sidebar.labelValue3, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.sidebar.labelUnit3, "%s", curation.unit_buf);

    data_curation_handler(get_elec_calc_mwh(), FMT_MWH);
    lv_label_set_text_fmt(measSence.sidebar.labelValue4, "%s", curation.value_buf);
    lv_label_set_text_fmt(measSence.sidebar.labelUnit4, "%s", curation.unit_buf);
}

void measOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == measSence.cont) {
        if (code == LV_EVENT_CLICKED) {
            uiViewLoad("Sheet");
        }
    } else if (obj == measSence.mainShow.cont1) {
        if (code == LV_EVENT_CLICKED) {
            displayMode.cont1_mode++;
            if (displayMode.cont1_mode > 2)
                displayMode.cont1_mode = 0;
        }
    } else if (obj == measSence.mainShow.cont2) {
        if (code == LV_EVENT_CLICKED) {
            displayMode.cont2_mode++;
            if (displayMode.cont2_mode > 2)
                displayMode.cont2_mode = 0;
            average_calc_reset();
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
