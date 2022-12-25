#ifndef APP_BULLET_CHAT_GUI_H
#define APP_BULLET_CHAT_GUI_H

struct BulletInfo
{
    int time;// 已经经历过的帧数
    char* content;//弹幕内容
    short trace;// 弹幕所处的泳道
};

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
#define ANIEND                      \
    while (lv_anim_count_running()) \
        lv_task_handler(); //等待动画完成

    void bullet_chat_gui_init(void);
    void display_bullet_chat_init(void);
    void display_bullet_chat(struct BulletInfo *bulletInfo,int bullet_len);
    void clear_bullet_chat(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t app_bullet_chat;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif