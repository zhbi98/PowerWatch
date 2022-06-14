
#include "About.h"

void aboutLoadView(lv_obj_t * root)
{
    lv_obj_set_size(root, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    aboutViewCreate(root);

    aboutAttachEvent(aboutSence.cont);
    aboutAttachEvent(aboutSence.button);
}

void aboutLoadGroup()
{
    // lv_indev_wait_release(lv_indev_get_act());
    lv_group_t * group = lv_group_get_default();
    lv_group_remove_all_objs(group);

    lv_group_add_obj(group, aboutSence.cont);
    lv_group_add_obj(group, aboutSence.button);
}

void aboutAttachEvent(lv_obj_t * obj)
{
    lv_obj_add_event_cb(obj, aboutOnEvent, LV_EVENT_ALL, NULL);
}

void aboutViewUpdate()
{
    static int i = 0, j = 0;

    if (i == 5000) {
        i = 0;
        unsigned char buf[10];
        memset(buf, '\0', 10);
        sprintf(buf, "%04d", j);
        lv_label_set_text_fmt(aboutSence.title.label, "%s", buf);
        j++;
    }
    i++;
}

void aboutOnEvent(lv_event_t * event)
{
    lv_obj_t * obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        UIViewLoad("MeasCenter");
    }
}
