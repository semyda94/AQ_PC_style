// calendar_table.cpp (LVGL 8.3.11)
// A 7x6 calendar day grid using lv_table, with "active day" highlight.
// - No built-in lv_calendar widget
// - Sunday-first
// - Table size: 122x84 (6 rows * 14px target height)
// - Active cell highlight: BG #2057ED, Text #FFFFFF (done via DRAW_PART event, reliable in LVGL 8)

#include "calendar_table.h"

#include <lvgl.h>
#include <time.h>
#include <stdio.h>

// -------------------- CONFIG --------------------
static constexpr int kCols = 7;
static constexpr int kRows = 6;

const char* monthToShortName(int tm_mon);

// -------------------- INTERNAL STATE --------------------
// For a single calendar instance. If you need multiple calendars at once,
// store this per-table via user_data or a small map keyed by lv_obj_t*.
static int g_active_cell_id = -1; // cell index = row*kCols + col

// -------------------- HELPERS --------------------
static bool is_leap(int y) {
    return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

static int days_in_month(int year, int month1_12) {
    static const int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month1_12 == 2) return d[1] + (is_leap(year) ? 1 : 0);
    if (month1_12 < 1 || month1_12 > 12) return 30;
    return d[month1_12 - 1];
}

// -------------------- DRAW CALLBACK (ACTIVE CELL HIGHLIGHT) --------------------
static void calendar_table_draw_cb(lv_event_t* e)
{
    lv_obj_draw_part_dsc_t* dsc = (lv_obj_draw_part_dsc_t*)lv_event_get_param(e);
    if (!dsc) return;

    // We only care about table cells
    if (dsc->part != LV_PART_ITEMS) return;

    // LVGL 8 table: dsc->id is cell index in row-major order:
    // id = row*col_cnt + col
    if ((int)dsc->id != g_active_cell_id) return;

    // Ensure descriptors exist
    if (dsc->rect_dsc) {
        dsc->rect_dsc->bg_opa   = LV_OPA_COVER;
        dsc->rect_dsc->bg_color = lv_color_hex(0x2057ED);
        dsc->rect_dsc->radius   = 3; // optional rounded highlight
    }

    if (dsc->label_dsc) {
        dsc->label_dsc->color = lv_color_hex(0xFFFFFF);
    }
}

// -------------------- PUBLIC API --------------------
lv_obj_t* calendar_table_create(lv_obj_t* parent)
{
    lv_obj_t* table = lv_table_create(parent);

    // Grid size
    lv_table_set_col_cnt(table, kCols);
    lv_table_set_row_cnt(table, kRows);

    // Target size (width 122, height 6*14 = 84)
    lv_obj_set_size(table, 122, 84);

    // Positioning is done outside (ui_custom_init), e.g.:
    // lv_obj_align(table, LV_ALIGN_CENTER, -73, 6);

    // Remove background/borders to match your style
    lv_obj_set_style_bg_opa(table, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(table, 0, LV_PART_MAIN);
    lv_obj_set_style_border_opa(table, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_pad_all(table, 0, LV_PART_MAIN);

    lv_obj_set_style_border_width(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_border_opa(table, LV_OPA_TRANSP, LV_PART_ITEMS);
    lv_obj_set_style_pad_all(table, 0, LV_PART_ITEMS);

    // Column widths to total 122px: 122/7 = 17 remainder 3
    // Distribute remainder across first 3 columns => 18,18,18, then 17,17,17,17
    for (int c = 0; c < kCols; c++) {
        int w = (c < 3) ? 18 : 17;
        lv_table_set_col_width(table, c, w);
    }

    // Center text in cells
    lv_obj_set_style_text_align(table, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS);

    // Tight paddings (helps fit ~14px row height)
    lv_obj_set_style_pad_top(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_pad_bottom(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_pad_left(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_pad_right(table, 0, LV_PART_ITEMS);

    // Disable scrolling; it's a static grid
    lv_obj_clear_flag(table, LV_OBJ_FLAG_SCROLLABLE);

    // Hook draw callback to highlight active day reliably (LVGL 8)
    lv_obj_add_event_cb(table, calendar_table_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Clear cells
    for (int r = 0; r < kRows; r++)
        for (int c = 0; c < kCols; c++)
            lv_table_set_cell_value(table, r, c, "");

    return table;
}

void calendar_table_set_month(lv_obj_t* table, int year, int month1_12, int active_day)
{
    if (!table) return;

    char yearBuff[20];
    snprintf (yearBuff, sizeof(yearBuff), "%04d", year);
    lv_label_set_text(ui_DateTimeScreenYearLabel, yearBuff );
    lv_label_set_text(ui_DateTimeScreenMonthLabel, monthToShortName(month1_12 - 1) );

    // Reset active cell
    g_active_cell_id = -1;

    // Clear all cells
    for (int r = 0; r < kRows; r++) {
        for (int c = 0; c < kCols; c++) {
            lv_table_set_cell_value(table, r, c, "");
        }
    }

    // weekday of 1st day: tm_wday 0=Sun..6=Sat (Sunday-first)
    struct tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon  = month1_12 - 1;
    t.tm_mday = 1;
    mktime(&t);

    int first_wday = t.tm_wday; // 0..6
    int dim = days_in_month(year, month1_12);

    // Stable storage for cell text (must remain valid after function returns)
    static char cell_txt[kRows][kCols][3]; // "31\0"

    // Clear text buffers too (optional)
    for (int r = 0; r < kRows; r++)
        for (int c = 0; c < kCols; c++)
            cell_txt[r][c][0] = '\0';

    // Fill day numbers
    for (int day = 1; day <= dim; day++) {
        int idx = first_wday + (day - 1); // 0..41
        int row = idx / kCols;
        int col = idx % kCols;

        if (row < 0 || row >= kRows) continue;

        snprintf(cell_txt[row][col], sizeof(cell_txt[row][col]), "%d", day);
        lv_table_set_cell_value(table, row, col, cell_txt[row][col]);

        if (day == active_day) {
            g_active_cell_id = row * kCols + col;
        }
    }

    // Force redraw so highlight applies immediately
    lv_obj_invalidate(table);
}

const char* monthToShortName(int tm_mon)
{
    static const char* months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    if (tm_mon < 0 || tm_mon > 11) return "???";
    return months[tm_mon];
}

void clock_set_time(int hour, int minute)
{
    char timeBuff[20];
    snprintf (timeBuff, sizeof(timeBuff), "%02d:%02d", hour, minute);
    lv_label_set_text(ui_DateTimeScreenTimeLabel, timeBuff );

    // Calculate angles
    // degrees
    float min_deg  = minute * 6.0f;       // optional smooth
    float hour_deg = (hour % 12) * 30.0f + minute * 0.5f; // smooth hour

    // LVGL often uses 0.1 degree units:
    int16_t min10  = (int16_t)(min_deg * 10);
    int16_t hour10 = (int16_t)(hour_deg * 10);

    // set pivot once (do it at init)
    // lv_img_set_pivot(ui_min_hand, pivot_x, pivot_y);
    // lv_img_set_pivot(ui_hour_hand, pivot_x, pivot_y);

    lv_img_set_angle(ui_MinuteArrow,  min10);
    lv_img_set_angle(ui_HourArrow, hour10);
}