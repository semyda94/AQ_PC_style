#ifndef _AQ_PC_STYLE_SCREEN_H
#define _AQ_PC_STYLE_SCREEN_H

#include <Arduino.h>
#include <string>
#include <vector>
#include <functional>

#include "../../ui/ui.h"
#include "Form.h"


// Use std::function for better type safety and flexibility
typedef std::function<void(void*)> ButtonCallback;
typedef std::function<void(void*)> LoadCallback;
typedef std::function<void(void*)> FocusCallback;

class Screen {    
public:
    String name; //Screen name
    bool isActionable = false; //Is screen actionable
    LoadCallback onLoad; //On load function

    /// Screen navigation pointers/Actors
    Screen* next; //Next screen in the list
    lv_obj_t* nextScreenSwitchEventActor; //Actor to trigger switch to next screen
    Screen* previous; //Previous screen in the list
    lv_obj_t* previousScreenSwitchEventActor; //Actor to trigger switch to previous screen
    
    int focusedFormId = -1;
    Form* focusedForm = nullptr;
    std::vector<Form*> forms;


    int focusedElementId = -1;
    Element* focusedElement = nullptr;
    std::vector<Element*> elements;

    // Constructor for better initialization
    Screen(
            const String& name, //Screen name
            bool isActionable = false, //Is screen actionable on load
            LoadCallback onLoadFunc = nullptr, //On load function
            lv_obj_t* nextScreenSwitchEventActor = nullptr, //Actor to trigger switch to next screen
            lv_obj_t* previousScreenSwitchEventActor = nullptr, //Actor to trigger switch to previous screen

            //ButtonsActions
            ButtonCallback onButton1 = nullptr,
            ButtonCallback onButton2 = nullptr,
            ButtonCallback onButton3 = nullptr,
            ButtonCallback onButton4 = nullptr
            );
    
    // Destructor for cleanup
    ~Screen();

    void onLoadScreen();

    // Navigation methods
    void switchToNext();
    void switchToPrevious();
    
    // Form navigation methods
    void focusNextForm();
    void focusPreviousForm();
    void focusForm(String name);
    void defocusCurrentForm();

    // Element navigation methods
    void focusNextElement();
    void focusPreviousElement();
    // void focusElement(int elementId);
    // void defocusCurrentElement();
    
    // Button handlers - each button has a specific purpose
    void handleButton1();  // Back/exit
    void handleButton2();  // Navigate previous
    void handleButton3();  // Navigate down/next
    void handleButton4();  // Select/enter
    
    
    // Add forms to screen
    void addForm(Form* form);
    
    //Add elements to screen
    void addElement(Element* element);

private:
    void updateFocusedForm();

    // Action button callbacks
    ButtonCallback onButton1;
    ButtonCallback onButton2;
    ButtonCallback onButton3;
    ButtonCallback onButton4;
};

#endif