#ifndef _AQ_PC_STYLE_SCREEN_HIERARCHY_H
#define _AQ_PC_STYLE_SCREEN_HIERARCHY_H

#include <Arduino.h>
#include "Screen.h"

void setupScreens();


// // Navigation manager class for global state
// class NavigationManager {
// public:
//     static NavigationManager& getInstance();
    
//     void handleGlobalButton1();
//     void handleGlobalButton2();
//     void handleGlobalButton3();
//     void handleGlobalButton4();
    
//     void setActiveScreen(Screen* screen);
//     Screen* getActiveScreen() const { return activeScreen; }
//     Screen* getActiveChild() const { return activeChild; }

// private:
//     Screen* activeScreen = nullptr;
//     Screen* activeChild = nullptr;
    
//     NavigationManager() = default;
//     NavigationManager(const NavigationManager&) = delete;
//     NavigationManager& operator=(const NavigationManager&) = delete;
// };

// // Global access points
extern Screen* ActiveScreen;

#endif