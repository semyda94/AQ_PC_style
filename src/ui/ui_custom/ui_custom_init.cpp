#include "ui_custom_init.h"
#include "calendar_table.h"

// Keep pointer if you need to update later

lv_obj_t* g_calendar_table = nullptr;

void ui_custom_init(void)
{
    // Parent is your SquareLine container
    g_calendar_table = calendar_table_create(ui_DateTimeScreenCalendarContainer);

    // Position it inside the container (choose coordinates)
    // Example: x=10,y=40
    lv_obj_set_pos(g_calendar_table, 0, 0);
}
