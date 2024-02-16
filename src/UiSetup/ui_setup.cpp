#include "ui_setup.h"
#include <lvgl.h>

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ ScreenWidth * ScreenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(ScreenWidth, ScreenHeight); /* TFT instance */


void amimationLoop(void* pvParameters){
  while (1) {
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
  }
}

// /* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void tft_ui_setup(void)
{
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println( LVGL_Arduino );
  Serial.println( "I am LVGL_Arduino" );

  lv_init();

  tft.begin();          /* TFT init */
  tft.setRotation( 3 ); /* Landscape orientation, flipped */


  lv_disp_draw_buf_init( &draw_buf, buf, NULL, ScreenWidth * ScreenHeight / 10 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = ScreenWidth;
  disp_drv.ver_res = ScreenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  // indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );
    
  Serial.println( "TFT Setup done" );

  /* Init SquareLine prepared UI */
  ui_init();

  Serial.println( "UI Setup done" );

  xTaskCreatePinnedToCore (
    amimationLoop,     // Function to implement the task
    "amimationLoop",   // Name of the task
    4096*2,      // Stack size in words
    NULL,      // Task input parameter
    5,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );
}