#include "bullet_chat_gui.h"

#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "stdio.h"


#define MAX_WIDTH 240
#define MAX_HEIGHT 200

lv_obj_t *bullet_chat_scr = NULL;

lv_obj_t *canvas = NULL;
// lv_obj_t *margin_block = NULL;

// static lv_style_t margin_block_style;

// 每一帧 弹幕移动的像素值
static double bullet_speed[] = {1,1,2,1};

static lv_style_t canvas_style;
static lv_style_t default_style;

static int cbuf_size = LV_CANVAS_BUF_SIZE_TRUE_COLOR(MAX_WIDTH, MAX_HEIGHT);

// static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(MAX_WIDTH, MAX_HEIGHT)];

static lv_color_t * cbuf;


// 控件及样式初始化
void bullet_chat_gui_init()
{

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style,LV_STATE_DEFAULT,LV_COLOR_BLACK);
    // lv_style_set_pad_top(&default_style,LV_STATE_DEFAULT,40);
    bullet_chat_scr = NULL;
    canvas = NULL;
    
    bullet_chat_scr = lv_obj_create(NULL,NULL);
    lv_obj_add_style(bullet_chat_scr, LV_OBJ_PART_MAIN, &default_style);
    // lv_obj_add_style(bullet_chat_scr, LV_BTN_PART_MAIN, &default_style);

    
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

    cbuf = (lv_color_t*)malloc(cbuf_size);
    // lv_style_init(&margin_block_style);
    // lv_style_set_bg_color(&margin_block_style,LV_STATE_DEFAULT,LV_COLOR_BLACK);
    // lv_style_set_pad_top(&margin_block_style,LV_STATE_DEFAULT,20);
    // margin_block = lv_cont_create(bullet_chat_scr,NULL);

    // lv_obj_add_style(margin_block,LV_CONT_PART_MAIN,&margin_block_style);

    // canvas = lv_canvas_create(margin_block, NULL);

    canvas = lv_canvas_create(bullet_chat_scr, NULL);
    // lv_style_set_pad_top(&canvas_style,LV_STATE_DEFAULT,100);
    // lv_style_set_margin_top(&canvas_style,LV_STATE_DEFAULT,20);

    // lv_obj_add_style(canvas,LV_CANVAS_PART_MAIN,&canvas_style);
    lv_canvas_set_buffer(canvas, cbuf, MAX_WIDTH, MAX_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, LV_OPA_COVER);
    lv_obj_set_pos(canvas,0,20);

    // lv_draw_label_dsc_t label_dsc;
    // lv_draw_label_dsc_init(&label_dsc);
    // label_dsc.color = LV_COLOR_WHITE;
    // lv_canvas_draw_text(canvas,0,0,240,&label_dsc,"Lurk",LV_LABEL_ALIGN_LEFT);

}

short* get_bullet_position(struct BulletInfo bulletInfo)
{
    // double x = bulletInfo.trace*50;
    // double y = (short) bullet_speed[bulletInfo.trace]*bulletInfo.time;
    // short xy[] = {x,y};

    short xy[2] = {0,0};
    // xy[0] = x;
    // xy[1] = y;
    return xy;
}

void draw_text(struct BulletInfo bulletInfo){
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = LV_COLOR_WHITE;

    // lv_canvas_draw_text(canvas,0,0,240,&label_dsc,"Lurk",LV_LABEL_ALIGN_LEFT);


    // short* xy = get_bullet_position(bulletInfo);

    // short xy[] = {0,50};

    short y = bulletInfo.trace*50;
    short x = (short) bullet_speed[bulletInfo.trace]*bulletInfo.time;

    short real_x = MAX_WIDTH - x;

    if(real_x > 0){
        lv_canvas_draw_text(canvas,real_x,y,240,&label_dsc,bulletInfo.content,LV_LABEL_ALIGN_LEFT);
    }

}

void display_bullet_chat(struct BulletInfo *bulletInfo,int bullet_len)
{
    display_bullet_chat_init();

    // int bullet_len = sizeof(bulletInfo)/sizeof(bulletInfo[0]);
    // Serial.print("Width = ");
    // Serial.print("Width = "); Serial.print(w); Serial.print(", height = "); Serial.println(h);

    int i;

    for(i=0; i < bullet_len; i++){
        struct BulletInfo info = (struct BulletInfo) *(bulletInfo+i);
        draw_text(info);

        // struct BulletInfo info1 = {
        //     80 ,"LURK",i
        // };

        // draw_text(info1);
    }

    
    
    lv_scr_load(bullet_chat_scr);
}

void clear_bullet_chat()
{
    if(NULL != bullet_chat_scr)
    {
        lv_obj_clean(bullet_chat_scr);
        bullet_chat_scr = NULL;
    }
    free(cbuf);
}