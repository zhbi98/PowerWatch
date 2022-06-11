
#include "AboutView.h"

AboutSence aboutSence;

void aboutSenceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&aboutSence.style);
    lv_style_init(&aboutSence.style);
    lv_style_set_radius(&aboutSence.style, 0);
    lv_style_set_bg_color(&aboutSence.style, lv_color_hex(0xFFD8BD));
    lv_style_set_bg_opa(&aboutSence.style, LV_OPA_50);
    lv_style_set_border_width(&aboutSence.style, 0);
    lv_style_set_border_color(&aboutSence.style, lv_color_hex(0xFFD8BD));
    lv_style_set_border_opa(&aboutSence.style, LV_OPA_50);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&aboutSence.style, lv_color_hex(0x000000));

    lv_obj_add_style(obj, &aboutSence.style, 0);
}

void aboutViewCreate(lv_obj_t * root)
{
    lv_obj_t * cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 320, 170);
    lv_obj_center(cont);
    aboutSenceStyleCreate(root);
    aboutSenceStyleCreate(cont);
    aboutSence.cont = cont;

    lv_obj_t * label = lv_label_create(aboutSence.cont);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 8);
    LV_FONT_DECLARE(font_bahnschrift_56);
    lv_obj_set_style_text_font(label, &font_bahnschrift_56, 0);
    lv_label_set_text_fmt(label, "%s", "2020");
    aboutSence.title.label = label;

    lv_obj_t * button = lv_btn_create(aboutSence.cont);
    label = lv_label_create(button);
    lv_label_set_text_fmt(label, "%s", "OK");
    lv_obj_center(label);
    lv_obj_set_size(button, 80, 40);
    lv_obj_set_pos(button, 120, 120);
}

void aboutLoadView(lv_obj_t * root)
{
    aboutViewCreate(root);
}
