
#include "NormalModeView.h"

UINormalMode uiNormalModeView;

void normalModeViewStyle(lv_obj_t * obj)
{
    static lv_style_t style;

    // Reset style to free memory
    lv_style_reset(&style);
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_hex(/*0xFCDFDB*/0x080808));
    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_color(&style, lv_color_hex(/*0xFCDFDB*/0x080808));
    lv_style_set_border_opa(&style, LV_OPA_100);
    // lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_color(&style, lv_color_hex(0x2196F3));

    lv_obj_add_style(obj, &style, 0);
}

void normalModeViewCreate(lv_obj_t * root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, 320, 170);
    lv_obj_set_y(root, 0);
    lv_obj_set_x(root, 0);

    normalModeViewStyle(root);

    lv_obj_t * label = lv_label_create(root);
    lv_obj_set_size(label, 80, 80);
    lv_obj_set_pos(label, 10, 45);
    LV_FONT_DECLARE(font_bahnschrift_17);
    lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    lv_label_set_text_fmt(label, "%s", "OUT123");

    lv_style_reset(&uiNormalModeView.uiOutputLabel.styleOutputLabel);
    lv_style_init(&uiNormalModeView.uiOutputLabel.styleOutputLabel);
    lv_style_set_radius(&uiNormalModeView.uiOutputLabel.styleOutputLabel, 10);
    lv_style_set_bg_color(&uiNormalModeView.uiOutputLabel.styleOutputLabel, lv_color_hex(0xFDD25E));
    lv_style_set_bg_opa(&uiNormalModeView.uiOutputLabel.styleOutputLabel, LV_OPA_100);
    lv_style_set_border_width(&uiNormalModeView.uiOutputLabel.styleOutputLabel, 1);
    lv_style_set_border_color(&uiNormalModeView.uiOutputLabel.styleOutputLabel, lv_color_hex(0xFDD25E));
    lv_style_set_border_opa(&uiNormalModeView.uiOutputLabel.styleOutputLabel, LV_OPA_100);
    lv_style_set_text_color(&uiNormalModeView.uiOutputLabel.styleOutputLabel, lv_color_hex(0x000000));
    lv_obj_add_style(label, &uiNormalModeView.uiOutputLabel.styleOutputLabel, 0);

    uiNormalModeView.uiOutputLabel.outputLabel = label;
}

void normalModeLoadView(lv_obj_t * root)
{
	normalModeViewCreate(root);
}
