#include "bullet_chat.h"
#include "bullet_chat_gui.h"

#include "sys/app_controller.h"
#include "common.h"

#define BULLET_CHAT_APP_NAME "Bullet Chat"

static int bullet_chat_init(void)
{
    bullet_chat_gui_init();
}

static void bullet_chat_process(AppController *sys,const Imu_Action *act_info)
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_FADE_ON;

    if (RETURN == act_info->active)
    {
        sys->app_exit();
        return;
    }

    display_bullet_chat();

    delay(30);
}

static int bullet_chat_exit_callback(void *param)
{
    clear_bullet_chat();
}

static void bullet_chat_message_handle(const char *from, const char *to,
                                   APP_MESSAGE_TYPE type, void *message,
                                   void *ext_info)
{

}

APP_OBJ bullet_chat_app = {
    BULLET_CHAT_APP_NAME,
    &app_bullet_chat,
    "",
    bullet_chat_init,
    bullet_chat_process,
    bullet_chat_exit_callback,
    bullet_chat_message_handle
};