#ifndef _AQ_PC_STYLE_SCREEN_HIERARCHY_H
#define _AQ_PC_STYLE_SCREEN_HIERARCHY_H

#include <Arduino.h>
#include <string>

#include "../../ui/ui.h"

#include <vector>
#include <iostream>


void setupScreens();

class Screen;
class Form;
class Element;

typedef void (*onLoadFunc)(void*);

class Screen {    
    public:
        lv_obj_t * object;
        bool isActionable = false;
        String name;
        lv_obj_t * SwitchEventActor;
        onLoadFunc onLoad;

        
        Screen * next;
        int focusedFormId = -1;
        int formsCount = 0;
        std::vector<Form> forms;
        
        Form * focusedForm;

        void Init(String nameParam, Screen * nextScreenParam, bool isActionableParam, lv_obj_t * switchEventActorParam, std::vector<Form> formsParam, onLoadFunc newOnLoadFunc = NULL ) {
            name = nameParam;
            next = nextScreenParam;
            isActionable = isActionableParam;
            SwitchEventActor = switchEventActorParam;

            forms = formsParam;
            formsCount = formsParam.size();

            onLoad = newOnLoadFunc;
        };

        void SwitchScreen();
        void SwitchSelectedChiled();
        void OnLoad();

        void FocusForm(int formId);
        void DefocusForm();

};

typedef void (*onButton1FormFunc)(void*);
typedef void (*onButton2FormFunc)(void*);
typedef void (*onButton3FormFunc)(void*);
typedef void (*onButton4FormFunc)(void*);
typedef void (*onFormFocusFunc)(void*);
typedef void (*onFormDefocusFunc)(void*);


class Form {
    public:
        String name;
        bool isFocused = false;
        
        Screen * ParentScreen;
        Screen * ChildScreen;

        int focusedElementId = 0;
        int elementsCount = 0;
        std::vector<Element> elements;

        onFormFocusFunc onFocus;
        onFormDefocusFunc onDefocus;

        onButton1FormFunc onButton1;
        onButton2FormFunc onButton2;
        onButton3FormFunc onButton3;
        onButton4FormFunc onButton4;

    void Init(
            Screen * parentScreenParam,
            Screen * childScreenParam,
            String nameParam,

            std::vector<Element> elementsParam,

            onFormFocusFunc onFocusParam = NULL,
            onFormDefocusFunc onDefocusParam = NULL,
            onButton1FormFunc onButton1Param = NULL,
            onButton2FormFunc onButton2Param = NULL,
            onButton3FormFunc onButton3Param = NULL,
            onButton4FormFunc onButton4Param = NULL 
        ) 
    {

        ParentScreen = parentScreenParam;
        ChildScreen = childScreenParam;
        name = nameParam;

        elements = elementsParam;
        elementsCount = elementsParam.size();

        onFocus= onFocusParam;
        onDefocus = onDefocusParam;

        onButton1 = onButton1Param;
        onButton2 = onButton2Param;
        onButton3 = onButton3Param;
        onButton4 = onButton4Param;
    };
};

class Element {
    public:
        String name;
        bool isFocused = false;

        Form * ParentForm;

        lv_obj_t * eventActor;

        void Init(
            Form * parentFormParam,
            String nameParam,
            lv_obj_t * eventActorParam
        ) 
    {
        ParentForm = parentFormParam;
        name = nameParam;
        eventActor = eventActorParam;
    };
};

extern Screen * ActiveScreen;
extern Screen * ActiveChild;

#endif