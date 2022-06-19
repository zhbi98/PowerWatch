
#include "MeasView.h"

MeasSence measSence;

void senceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&measSence.style);
    lv_style_init(&measSence.style);
    lv_style_set_radius(&measSence.style, 0);
    lv_style_set_bg_color(&measSence.style, lv_color_hex(0xFFFFFF/*0xF2F1F6*/));
    lv_style_set_bg_opa(&measSence.style, LV_OPA_100);
    lv_style_set_border_width(&measSence.style, 0);
    lv_style_set_border_color(&measSence.style, lv_color_hex(0xFFFFFF/*0xF2F1F6*/));
    lv_style_set_border_opa(&measSence.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&measSence.style, lv_color_hex(0x000000/*0x000000*/));

    lv_obj_add_style(obj, &measSence.style, 0);
}

void mainShowStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&measSence.mainShow.style);
    lv_style_init(&measSence.mainShow.style);
    lv_style_set_radius(&measSence.mainShow.style, 10);
    lv_style_set_bg_color(&measSence.mainShow.style, lv_color_hex(0xE6E5EB));
    lv_style_set_bg_opa(&measSence.mainShow.style, LV_OPA_100);
    lv_style_set_border_width(&measSence.mainShow.style, 0);
    lv_style_set_border_color(&measSence.mainShow.style, lv_color_hex(0xE6E5EB));
    lv_style_set_border_opa(&measSence.mainShow.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&measSence.mainShow.style, lv_color_hex(0x000000));

#if 0
    lv_style_set_shadow_width(&measSence.mainShow.style, 2);
    lv_style_set_shadow_color(&measSence.mainShow.style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_ofs_x(&measSence.mainShow.style, 2);
    lv_style_set_shadow_ofs_y(&measSence.mainShow.style, 2);
#endif

    lv_obj_add_style(obj, &measSence.mainShow.style, 0);
}

void labelStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&measSence.sidebar.labelStyle);
    lv_style_init(&measSence.sidebar.labelStyle);
    lv_style_set_radius(&measSence.sidebar.labelStyle, 2);
    lv_style_set_bg_color(&measSence.sidebar.labelStyle, lv_color_hex(0x047DFF));
    lv_style_set_bg_opa(&measSence.sidebar.labelStyle, LV_OPA_100);
    lv_style_set_border_width(&measSence.sidebar.labelStyle, 0);
    lv_style_set_border_color(&measSence.sidebar.labelStyle, lv_color_hex(0x047DFF));
    lv_style_set_border_opa(&measSence.sidebar.labelStyle, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&measSence.sidebar.labelStyle, lv_color_hex(0x000000));

    lv_obj_add_style(obj, &measSence.sidebar.labelStyle, 0);
}

void measViewCreate(lv_obj_t * root)
{
    lv_obj_t * cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 320, 170);
    lv_obj_center(cont);
    senceStyleCreate(root);
    senceStyleCreate(cont);

    mainShowViewCreate(cont);
    sidebarViewCreate(cont);
    measSence.cont = cont;
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
    lv_obj_set_size(cont, 160, 55);
    lv_obj_set_pos(cont, 10, 10);
    mainShowStyleCreate(cont);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xE6E5EB/*0x232514*/), 0);
    lv_obj_set_style_text_color(cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x047DFF), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x414141), LV_STATE_PRESSED);
    measSence.mainShow.cont1 = cont;

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 160, 55);
    lv_obj_set_pos(cont, 10, 70);
    mainShowStyleCreate(cont);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xE6E5EB/*0x232514*/), 0);
    lv_obj_set_style_text_color(cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x047DFF), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x414141), LV_STATE_PRESSED);
    measSence.mainShow.cont2 = cont;

    cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 105, 24);
    lv_obj_set_pos(cont, 65, 130);
    mainShowStyleCreate(cont);
    lv_obj_set_style_radius(cont, 5, 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xE6E5EB/*0x232514*/), 0);
    lv_obj_set_style_text_color(cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x047DFF), LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(cont, lv_color_hex(0xFFFFFF), LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x414141), LV_STATE_PRESSED);
    measSence.mainShow.cont3 = cont;

    lv_obj_t * label = lv_label_create(par);
    // lv_obj_set_size(label, 160, 80);
    lv_obj_set_pos(label, 15, 132);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x047DFF), 0);
    lv_label_set_text_fmt(label, "%s", "AVG");

    label = lv_label_create(measSence.mainShow.cont1);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 20, 20);
    LV_FONT_DECLARE(font_bahnschrift_56);
    lv_obj_set_style_text_font(label, &font_bahnschrift_56, 0);
    lv_label_set_text_fmt(label, "%s", "00.00");
    lv_obj_align(label, LV_ALIGN_CENTER, /*-18*/-22, 0);
    measSence.mainShow.lableValue1 = label;

    label = lv_label_create(measSence.mainShow.cont1);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 136, 20);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "V");
    // lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, -5, 5);
    measSence.mainShow.lableUnit1 = label;

    label = lv_label_create(measSence.mainShow.cont2);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 20, 20);
    LV_FONT_DECLARE(font_bahnschrift_56);
    lv_obj_set_style_text_font(label, &font_bahnschrift_56, 0);
    lv_label_set_text_fmt(label, "%s", "00.00");
    lv_obj_align(label, LV_ALIGN_CENTER, /*-18*/-22, 0);
    measSence.mainShow.lableValue2 = label;

    label = lv_label_create(measSence.mainShow.cont2);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 136, 20);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "A");
    // lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, -5, 5);
    measSence.mainShow.lableUnit2 = label;

    label = lv_label_create(measSence.mainShow.cont3);
    // lv_obj_set_size(label, 160, 80);
    // lv_obj_set_pos(label, 20, 20);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "00:00:00");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    measSence.mainShow.lableValue3 = label;

    // mainShowAnim(cont);
}

void sidebarViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 144, 170);
    lv_obj_set_pos(cont, 176, 0);
    senceStyleCreate(cont);
    measSence.sidebar.cont = cont;
// -------------------------------------------------------------------
    lv_obj_t * label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 6, 24);
    lv_obj_set_pos(label, 6, 12);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 120, 38);
    lv_obj_set_pos(label, 20, 8);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    measSence.sidebar.labelValue1 = label;

    label = lv_label_create(measSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 90, 16);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mA");
    // labelStyleCreate(label);
    measSence.sidebar.labelUnit1 = label;
// -------------------------------------------------------------------
    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 6, 24);
    lv_obj_set_pos(label, 6, 51);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 20, 48);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    measSence.sidebar.labelValue2 = label;

    label = lv_label_create(measSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 90, 56);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mW");
    // labelStyleCreate(label);
    measSence.sidebar.labelUnit2 = label;
// -------------------------------------------------------------------
    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 6, 24);
    lv_obj_set_pos(label, 6, 91);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);

    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 20, 88);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    measSence.sidebar.labelValue3 = label;

    label = lv_label_create(measSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 90, 96);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mAh");
    // labelStyleCreate(label);
    measSence.sidebar.labelUnit3 = label;
// -------------------------------------------------------------------
    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 6, 24);
    lv_obj_set_pos(label, 6, 129);
    lv_label_set_text_fmt(label, "%s", " ");
    labelStyleCreate(label);
    
    label = lv_label_create(measSence.sidebar.cont);
    lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 20, 126);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "0.000");
    // labelStyleCreate(label);
    measSence.sidebar.labelValue4 = label;

    label = lv_label_create(measSence.sidebar.cont);
    // lv_obj_set_size(label, 140, 40);
    lv_obj_set_pos(label, 90, 134);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "mWh");
    // labelStyleCreate(label);
    measSence.sidebar.labelUnit4 = label;
}
