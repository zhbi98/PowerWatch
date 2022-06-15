
#include "MeasCenter.h"

Energy energy = {
    .mAh  = 0.0,
    .mWh  = 0.0,
};

Average average = {
    .sum = 0.0,
    .avg = 0.0,
};

void electricalEnergy()
{
    energy.mAh = energy.mAh + (float)(ina226_data.Shunt_Current * ENERGY_TIME);
    energy.mWh = energy.mWh + (float)(ina226_data.Power * ENERGY_TIME);
}

void measCenterLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    measCenterViewCreate(root);

    measCenterAttachEvent(MeasSence.cont);
    measCenterAttachEvent(MeasSence.mainShow.cont1);
    measCenterAttachEvent(MeasSence.mainShow.cont2);
}

void measCenterLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, MeasSence.cont);
    lv_group_add_obj(group, MeasSence.mainShow.cont1);
    lv_group_add_obj(group, MeasSence.mainShow.cont2);
}

void measCenterAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, measCenterOnEvent, LV_EVENT_ALL, NULL);
}

void measCenterUpdate()
{
    static int i = 0;

    if (i == 2000) {
        i = 0;

        unsigned char buf[10];

        get_power();

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", ina226_data.voltageVal / 1000);
        lv_label_set_text_fmt(MeasSence.mainShow.lableValue1, "%s", buf);

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", average.avg);
        lv_label_set_text_fmt(MeasSence.mainShow.lableValue2, "%s", buf);

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", ina226_data.Shunt_Current);
        lv_label_set_text_fmt(MeasSence.sidebar.labelValue1, "%s", buf);

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", ina226_data.Power);
        lv_label_set_text_fmt(MeasSence.sidebar.labelValue2, "%s", buf);

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", energy.mAh);
        lv_label_set_text_fmt(MeasSence.sidebar.labelValue3, "%s", buf);

        memset(buf, '\0', 10);
        sprintf(buf, "%05.2f", energy.mWh);
        lv_label_set_text_fmt(MeasSence.sidebar.labelValue4, "%s", buf);
    }
    i++;
}

void measCenterOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        UIViewLoad("About");
    }
}
