
#include "AboutView.h"

AboutSence aboutSence;

void aboutSenceStyleCreate(lv_obj_t * obj)
{
    // Reset style to free memory
    lv_style_reset(&aboutSence.style);
    lv_style_init(&aboutSence.style);
    lv_style_set_radius(&aboutSence.style, /*0*//*4*/16);
    lv_style_set_bg_color(&aboutSence.style, lv_color_hex(0x5A75C5));
    lv_style_set_bg_opa(&aboutSence.style, LV_OPA_100);
    lv_style_set_border_width(&aboutSence.style, 0);
    lv_style_set_border_color(&aboutSence.style, lv_color_hex(0x5A75C5));
    lv_style_set_border_opa(&aboutSence.style, LV_OPA_100);
    // lv_palette_main(LV_PALETTE_BLUE)
    lv_style_set_text_color(&aboutSence.style, lv_color_hex(0xFFFFFF));

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

    lv_obj_t * button = lv_btn_create(cont);
    lv_obj_set_size(button, 60, 35);
    lv_obj_set_pos(button, 5, 102);
    lv_obj_t * label = lv_label_create(button);
    lv_label_set_text_fmt(label, "%s", "About");
    lv_obj_center(label);
}

void aboutLoadView(lv_obj_t * root)
{
    aboutViewCreate(root);
}
