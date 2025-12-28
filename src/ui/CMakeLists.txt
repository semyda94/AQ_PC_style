SET(SOURCES ui_LoadingScreen.c
    ui_TempHumScreen.c
    ui_DateTimeScreen.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_loading_screen_png.c
    ui_img_loadingbox1_png.c
    ui_img_loadingbox2_png.c
    ui_img_loadingbox3_png.c
    ui_img_default_screen_png.c
    ui_img_temphummainframe_png.c
    ui_img_datetimetabinactive_png.c
    ui_img_hometabactive_png.c
    ui_img_settingstabinactive_png.c
    ui_img_nextbuttonactive_png.c
    ui_img_datetimescreenmainframe_png.c
    ui_img_hometabinactive_png.c
    ui_img_datetimetabactive_png.c
    ui_img_previousbuttonactive_png.c
    ui_img_minutearrow_png.c
    ui_img_hourarrow_png.c)

add_library(ui ${SOURCES})
