#pragma once

#ifndef _UI_CUSTOM_INIT_H
#define _UI_CUSTOM_INIT_H

#include "../ui.h"

#ifdef __cplusplus
extern lv_obj_t* g_calendar_table;
#endif
    
#ifdef __cplusplus
extern "C" {
#endif
    void ui_custom_init(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
