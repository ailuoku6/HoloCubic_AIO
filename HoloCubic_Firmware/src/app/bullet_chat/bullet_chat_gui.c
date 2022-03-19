#include "bullet_chat_gui.h"

#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "stdio.h"

#define MAX_WIDTH 240
#define MAX_HEIGHT 240

lv_obj_t *bullet_chat_scr = NULL;

lv_obj_t *canvas = NULL;
static lv_style_t canvas_style;
static lv_style_t default_style;

// 控件及样式初始化
void bullet_chat_gui_init()
{

    lv_style_init(&default_style);

    bullet_chat_scr = NULL;
    canvas = NULL;
    
    bullet_chat_scr = lv_obj_create(NULL,NULL);
    lv_obj_add_style(bullet_chat_scr, LV_BTN_PART_MAIN, &default_style);

    
}

void display_bullet_chat_init(void)
{
    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (act_obj == bullet_chat_scr)
        return;
    // if (NULL != local_ip_label)
    // {
    //     lv_obj_clean(local_ip_label);
    //     lv_obj_clean(ap_ip_label);
    //     lv_obj_clean(domain_label);
    //     lv_obj_clean(title_label);
    // }
    lv_obj_clean(act_obj); // 清空此前页面

    canvas = lv_canvas_create(bullet_chat_scr, NULL);
    
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = LV_COLOR_BLACK;
    lv_canvas_draw_text(canvas,120,120,240,&label_dsc,"LURK",LV_LABEL_ALIGN_LEFT);

}

void display_bullet_chat()
{
    display_bullet_chat_init();

    lv_scr_load(bullet_chat_scr);
}

void clear_bullet_chat()
{
    if(NULL != bullet_chat_scr)
    {
        lv_obj_clean(bullet_chat_scr);
        bullet_chat_scr = NULL;
    }
}