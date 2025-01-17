SET(SOURCES screens/ui_LoadingScreen.c
    screens/ui_DataScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_retroboxicon1_png.c
    images/ui_img_loadingbar_png.c
    images/ui_img_loader_ind__1_png.c
    images/ui_img_loader_ind_2_png.c
    images/ui_img_loader_ind_3_png.c
    images/ui_img_wallpaper_png.c
    images/ui_img_datascreen_420_320_png.c
    images/ui_img_settingsscreen_png.c
    images/ui_img_network_connections_png.c
    images/ui_img_appearence_png.c
    images/ui_img_date_and_time_png.c
    images/ui_img_networkconnectionsscreen_png.c)

add_library(ui ${SOURCES})
