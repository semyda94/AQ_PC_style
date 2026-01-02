#pragma once

#ifndef _UI_CUSTOM_CALENDAR_TABLE_H
#define _UI_CUSTOM_CALENDAR_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <lvgl.h>
    #include "../ui.h"

    lv_obj_t* calendar_table_create(lv_obj_t* parent);
    void calendar_table_set_month(lv_obj_t* table, int year, int month1_12, int active_day);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
