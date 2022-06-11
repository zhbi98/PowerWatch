
#include "MeasCenterView.h"

MeasCenterSence MeasSence;

void senceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&MeasSence.style);
    lv_style_init(&MeasSence.style);
    lv_style_set_radius(&MeasSence.style, 0);
    lv_style_set_bg_color(&MeasSence.style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&MeasSence.style, LV_OPA_100);
    lv_style_set_border_width(&MeasSence.style, 0);
    lv_style_set_border_color(&MeasSence.style, lv_color_hex(0xFFFFFF));
    lv_style_set_border_opa(&MeasSence.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&MeasSence.style, lv_color_hex(0x000000));

    lv_obj_add_style(obj, &MeasSence.style, 0);
}

void mainShowStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&MeasSence.mainShow.style);
    lv_style_init(&MeasSence.mainShow.style);
    lv_style_set_radius(&MeasSence.mainShow.style, 10);
    lv_style_set_bg_color(&MeasSence.mainShow.style, lv_color_hex(0xFFD8BD));
    lv_style_set_bg_opa(&MeasSence.mainShow.style, LV_OPA_40);
    lv_style_set_border_width(&MeasSence.mainShow.style, 0);
    lv_style_set_border_color(&MeasSence.mainShow.style, lv_color_hex(0xFFD8BD));
    lv_style_set_border_opa(&MeasSence.mainShow.style, LV_OPA_40);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&MeasSence.mainShow.style, lv_color_hex(0x000000));

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

lv_anim_t mainShowAnim(lv_obj_t * obj)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, -160, 10);
    lv_anim_set_early_apply(&a, true);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_start(&a);
    return a;
}

void mainShowViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 160, 60);
    lv_obj_set_pos(cont, 10, 10);
    mainShowStyleCreate(cont);
    MeasSence.mainShow.cont = cont;

    lv_obj_t * label = lv_label_create(MeasSence.mainShow.cont);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 20, 20);
    lv_obj_align(label, LV_ALIGN_CENTER, -10, 0);
    LV_FONT_DECLARE(font_bahnschrift_56);
    lv_obj_set_style_text_font(label, &font_bahnschrift_56, 0);
    lv_label_set_text_fmt(label, "%s", "00.00");
    MeasSence.mainShow.lableValue = label;

    label = lv_label_create(MeasSence.mainShow.cont);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 136, 20);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, -8, 5);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "V");
    MeasSence.mainShow.lableUnit = label;

    // label = lv_label_create(MeasSence.mainShow.cont);
    // lv_obj_set_pos(label, 20, 120);
    // LV_FONT_DECLARE(symbol_chip_20);
    // lv_obj_set_style_text_font(label, &symbol_chip_20, 0);
    // lv_label_set_text_fmt(label, USR_SYMBOL_CHIP_20);
    mainShowAnim(cont);
}

void sidebarViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 144, 170);
    lv_obj_set_pos(cont, 176, 0);
    senceStyleCreate(cont);
    MeasSence.sidebar.cont = cont;
// -------------------------------------------------------------------
    lv_obj_t * label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 6, 8);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 120, 38);
    lv_obj_set_pos(label, 16, 8);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue1 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 99, 16);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mA");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelUnit2 = label;
// -------------------------------------------------------------------
    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 6, 48);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 16, 48);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue2 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 99, 56);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mW");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelUnit2 = label;
// -------------------------------------------------------------------
    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 6, 88);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 16, 88);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue3 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 99, 96);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mAh");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelUnit3 = label;
// -------------------------------------------------------------------
    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 4, 30);
    lv_obj_set_pos(label, 6, 128);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    
    label = lv_label_create(MeasSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 16, 128);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelValue4 = label;

    label = lv_label_create(MeasSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 99, 136);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mWh");
    // labelStyleCreate(label);
    MeasSence.sidebar.labelUnit4 = label;
}

void measCenterLoadView(lv_obj_t * root)
{
    measCenterViewCreate(root);
}
