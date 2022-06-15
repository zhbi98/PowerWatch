
#include "AboutView.h"

AboutSence aboutSence;

void aboutSenceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&aboutSence.style);
    lv_style_init(&aboutSence.style);
    lv_style_set_radius(&aboutSence.style, 0);
    lv_style_set_bg_color(&aboutSence.style, lv_color_hex(0x262922));
    lv_style_set_bg_opa(&aboutSence.style, LV_OPA_60);
    lv_style_set_border_width(&aboutSence.style, 0);
    lv_style_set_border_color(&aboutSence.style, lv_color_hex(0x262922));
    lv_style_set_border_opa(&aboutSence.style, LV_OPA_60);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&aboutSence.style, lv_color_hex(0xFFFFFF));

    lv_obj_add_style(obj, &aboutSence.style, 0);
}

void titleStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&aboutSence.title.style);
    lv_style_init(&aboutSence.title.style);
    lv_style_set_radius(&aboutSence.title.style, 10);
    lv_style_set_bg_color(&aboutSence.title.style, lv_color_hex(0xFFF6ED));
    lv_style_set_bg_opa(&aboutSence.title.style, LV_OPA_100);
    lv_style_set_border_width(&aboutSence.title.style, 0);
    lv_style_set_border_color(&aboutSence.title.style, lv_color_hex(0xFFF6ED));
    lv_style_set_border_opa(&aboutSence.title.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&aboutSence.title.style, lv_color_hex(0x000000));

#if 0
    lv_style_set_shadow_width(&aboutSence.title.style, 2);
    lv_style_set_shadow_color(&aboutSence.title.style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_ofs_x(&aboutSence.title.style, 2);
    lv_style_set_shadow_ofs_y(&aboutSence.title.style, 2);
#endif

    lv_obj_add_style(obj, &aboutSence.title.style, 0);
}

void aboutViewCreate(lv_obj_t * root)
{
    lv_obj_t * cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 320, 170);
    lv_obj_center(cont);
    aboutSenceStyleCreate(root);
    aboutSenceStyleCreate(cont);
    
    titleViewCreate(cont);
    infoViewCreate(cont);

    aboutSence.cont = cont;
}

void titleViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 145, 80);
    lv_obj_set_pos(cont, 10, 80);
    titleStyleCreate(cont);
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0xFEFEFE), 0);
    // lv_obj_set_style_text_color(cont, lv_color_hex(0x000000), 0);
    aboutSence.title.cont = cont;

    lv_obj_t * label = lv_label_create(par);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "ELECAL");
    lv_obj_set_pos(label, 42, 25);
    // lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    aboutSence.title.labelTitle = label;

    label = lv_label_create(aboutSence.title.cont);
    LV_FONT_DECLARE(symbol_chip_20);
    lv_obj_set_style_text_font(label, &symbol_chip_20, 0);
    lv_label_set_text_fmt(label, "%s", USR_SYMBOL_CHIP_20);
    lv_obj_align(label, LV_ALIGN_CENTER, -28, 0);
    // lv_obj_center(label);
    // lv_obj_set_size(label, 80, 40);
    // lv_obj_set_pos(label, 120, 120);
    aboutSence.title.labelLogo = label;

    label = lv_label_create(aboutSence.title.cont);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "25.0");
    lv_obj_align(label, LV_ALIGN_CENTER, 16, 0);
    // lv_obj_center(label);
    // lv_obj_set_size(label, 80, 40);
    // lv_obj_set_pos(label, 120, 120);
    aboutSence.title.labelTemp = label;
}

void infoViewCreate(lv_obj_t * par)
{
    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 145, 150);
    lv_obj_set_pos(cont, 165, 10);
    titleStyleCreate(cont);
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0xFEFEFE), 0);
    // lv_obj_set_style_text_color(cont, lv_color_hex(0x000000), 0);
    aboutSence.deviceInfo.cont = cont;

    lv_obj_t * label = lv_label_create(aboutSence.deviceInfo.cont);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "LVGL8.2.0");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);
    aboutSence.deviceInfo.labelLvgl = label;

    label = lv_label_create(aboutSence.deviceInfo.cont);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "GD32F103");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    aboutSence.deviceInfo.labelMcu = label;

    label = lv_label_create(aboutSence.deviceInfo.cont);
    LV_FONT_DECLARE(font_bahnschrift_32);
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_label_set_text_fmt(label, "%s", "GD25Q64");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -10);
    aboutSence.deviceInfo.labelFlash = label;
}
