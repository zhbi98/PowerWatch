
#include "AboutView.h"

void aboutViewStyle(lv_obj_t * obj)
{
    static lv_style_t style;

    // Reset style to free memory
    lv_style_reset(&style);
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_hex(0xFFAA4A/*0xFCDFDB*/));
    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_color(&style, lv_color_hex(0xFCDFDB));
    lv_style_set_border_opa(&style, LV_OPA_100);
    // lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_color(&style, lv_color_hex(0x2196F3));

    lv_obj_add_style(obj, &style, 0);
}

void aboutViewCreate(lv_obj_t * root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, 320, 170);
    lv_obj_set_y(root, 0);
    lv_obj_set_x(root, 0);

    aboutViewStyle(root);

    lv_obj_t * button = lv_btn_create(root);
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
