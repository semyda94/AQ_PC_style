SET(SOURCES ui_LoadingScreen.c
    ui_HomeScreen.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_loadingscreenframe_png.c
    ui_img_loadingbox1_png.c
    ui_img_loadingbox2_png.c
    ui_img_loadingbox3_png.c
    ui_img_main_app_frame_png.c
    ui_img_homeframe_png.c
    ui_img_nextbutton_active_png.c)

add_library(ui ${SOURCES})
