#ifndef _AQ_PC_STYLE_UI_SETUP_H
#define _AQ_PC_STYLE_UI_SETUP_H

#include <TFT_eSPI.h>

#ifdef __cplusplus
extern "C" {
#endif

//Local Inclusion
#include "../ui/ui.h"
// #include "TFT_eSPI.h"
// #include <lvgl.h>
// #include "../.pio/libdeps/esp32-c3-devkitm-1/TFT_eSPI/TFT_eSPI.h"

// #if defined __has_include
//   #if __has_include("lvgl.h")
//     #include "lvgl.h"
//   #elif __has_include("lvgl/lvgl.h")
//     #include "lvgl/lvgl.h"
//   #else
//     #include "lvgl.h"
//   #endif
//   #if __has_include("TFT_eSPI.h")
//     #include "TFT_eSPI.h"
//   #else
//     #include "TFT_eSPI.h"
//   #endif
// #else
//   #include "lvgl.h"
// #endif

#define ScreenWidth 320
#define ScreenHeight 240

void tft_ui_setup(void);
void amimationLoop(void* pvParameters);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
