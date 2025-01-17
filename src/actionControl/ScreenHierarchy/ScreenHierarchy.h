#ifndef _AQ_PC_STYLE_SCREEN_HIERARCHY_H
#define _AQ_PC_STYLE_SCREEN_HIERARCHY_H

#include <Arduino.h>
#include <string>

#include "../../ui/ui.h"


void setupScreens();

class Screen;
class Element;

typedef void (*onLoadFunc)(void*);

class Screen {    
    public:
        lv_obj_t * object;
        String name;
        lv_obj_t * SwitchEventActor;
        onLoadFunc onLoad;
        
        Screen * next;
        Element * focusedElement;

        void Init(String newName, Screen * newNext, lv_obj_t * newSwitchEventActor, Element * newFocusedElement, onLoadFunc newOnLoadFunc = NULL ) {
            name = newName;
            next = newNext;
            SwitchEventActor = newSwitchEventActor;
            focusedElement = newFocusedElement;
            onLoad = newOnLoadFunc;
        };

        void SwitchScreen();
        void SwitchSelectedChiled();
        void OnLoad();

};

class Element {
    private:
        Screen * ParentScreen;
        Screen * ChildScreen;
        Element * next;
        Element * previous;

    public:
        String name;
        lv_obj_t * eventActor;

    void Init(
            Screen * newParentScreen,
            Screen * newChildScreen,
            String newName, 
            Element * newNext,
            Element * newPrevious,
            lv_obj_t * newEventActor) {
        ParentScreen = newParentScreen;
        ChildScreen = newChildScreen;
        name = newName;
        next = newNext;
        previous = newPrevious;
        eventActor = newEventActor;
    }

    void MoveToNext();
    void MoveToPrevious();
    void Select();
};

extern Screen * ActiveScreen;
extern Screen * ActiveChild;

#endif