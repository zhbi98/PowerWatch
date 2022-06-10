
#include "MeasCenterView.h"

MeasCenterSence MeasSence;

void senceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&MeasSence.style);
    lv_style_init(&MeasSence.style);
    lv_style_set_radius(&MeasSence.style, /*0*//*4*/16);
    lv_style_set_bg_color(&MeasSence.style, lv_color_hex(0x5A75C5));
    lv_style_set_bg_opa(&MeasSence.style, LV_OPA_100);
    lv_style_set_border_width(&MeasSence.style, 0);
    lv_style_set_border_color(&MeasSence.style, lv_color_hex(0x5A75C5));
    lv_style_set_border_opa(&MeasSence.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&MeasSence.style, lv_color_hex(0xFFFFFF));

    lv_obj_add_style(obj, &MeasSence.style, 0);
}

void MainShowStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&MeasSence.mainShow.style);
    lv_style_init(&MeasSence.mainShow.style);
    lv_style_set_radius(&MeasSence.mainShow.style, /*0*//*4*/16);
    lv_style_set_bg_color(&MeasSence.mainShow.style, lv_color_hex(0xFFD8BD));
    lv_style_set_bg_opa(&MeasSence.mainShow.style, LV_OPA_100);
    lv_style_set_border_width(&MeasSence.mainShow.style, 0);
    lv_style_set_border_color(&MeasSence.mainShow.style, lv_color_hex(0xFFD8BD));
    lv_style_set_border_opa(&MeasSence.mainShow.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&MeasSence.mainShow.style, lv_color_hex(0x9A4B03));

    lv_obj_add_style(obj, &MeasSence.mainShow.style, 0);
}

void labelStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&MeasSence.sidebar.labelStyle);
    lv_style_init(&MeasSence.sidebar.labelStyle);
    lv_style_set_radius(&MeasSence.sidebar.labelStyle, 1);
    lv_style_set_bg_color(&MeasSence.sidebar.labelStyle, lv_color_hex(0xFFD8BD));
    lv_style_set_bg_opa(&MeasSence.sidebar.labelStyle, LV_OPA_100);
    lv_style_set_border_width(&MeasSence.sidebar.labelStyle, 0);
    lv_style_set_border_color(&MeasSence.sidebar.labelStyle, lv_color_hex(0xFFD8BD));
    lv_style_set_border_opa(&MeasSence.sidebar.labelStyle, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&MeasSence.sidebar.labelStyle, lv_color_hex(0xFFD8BD));

    lv_obj_add_style(obj, &MeasSence.sidebar.labelStyle, 0);
}

void measCenterViewCreate(lv_obj_t * root)
{
    lv_obj_t * cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 320, 170);
    lv_obj_center(cont);
    senceStyleCreate(root);
    senceStyleCreate(cont);

    mainShowViewCreate(cont);
    sidebarViewCreate(cont);
    MeasSence.cont = cont;
}

void mainShowViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 173, 170);
    lv_obj_set_pos(cont, 0, 0);
    MainShowStyleCreate(cont);
    MeasSence.mainShow.cont = cont;

    lv_obj_t * label = lv_label_create(MeasSence.mainShow.cont);
    // lv_obj_set_size(label, 160, 80);
    lv_obj_set_pos(label, 10, 45);
    LV_FONT_DECLARE(font_bahnschrift_65);
    lv_obj_set_style_text_font(label, &font_bahnschrift_65, 0);
    lv_label_set_text_fmt(label, "%s", "60.00");
    MeasSence.mainShow.lableValue = label;

    label = lv_label_create(MeasSence.mainShow.cont);
    // lv_obj_set_size(label, 160, 80);
    lv_obj_set_pos(label, 21, 100);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "km/h");
    MeasSence.mainShow.lableUnit = label;

    // lv_obj_t * bar = lv_bar_create(MeasSence.mainShow.cont);
    // lv_obj_set_size(bar, 120, 15);
    // lv_obj_set_pos(bar, 22, 130);
    // lv_bar_set_value(bar, 50, LV_ANIM_ON);
}

void sidebarViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 144, 170);
    lv_obj_set_pos(cont, 176, 0);
    senceStyleCreate(cont);
    MeasSence.sidebar.cont = cont;

    lv_obj_t * label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 120, 38);
    lv_obj_set_pos(label, 192 - 176, 16);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "10.00 mA");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 182 - 176, 18);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 192 - 176, 54);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "10.00 mW");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue2 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 182 - 176, 56);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 192 - 176, 88);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "10.00 mAh");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue3 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 182 - 176, 90);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 192 - 176, 125);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "10.00 mWh");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue4 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 182 - 176, 127);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;
}

void measCenterLoadView(lv_obj_t * root)
{
    measCenterViewCreate(root);
}
