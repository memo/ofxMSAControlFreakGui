#include "ofMain.h"

// This is a very minimal example that shows how to link the Parameters created in ofxMSAControlFreak to a GUI
// In this case using a simple custom opengl GUI

// include the ControlFreakGui
#include "ofxMSAControlFreakGui.h"

// Check the contents of ofxMSAControlFreakTutorial.h to see how to use ofxMSAControlFreak to create and use parameters
#include "ofxMSAControlFreakTutorial.h"
// Normally you wouldn't include this file, instead just define your own Parameters
// I just put everything in this file so I can keep this code separate and reuse it in different addons


class ofApp : public ofSimpleApp {
public:

    // declare a Gui
    msa::controlfreak::gui::Gui gui;

    // this is defined in ofxMSAControlFreakTutorial.h
    TutorialModule tutorial;

    void setup() {
        // initialise all parameters
        tutorial.setup();

        // create a GUI out of the parameters. The GUI will constuct all the nessecary controls and link each one to the relevant parameters
        // this is in effect duplicating the structure of the params in the GUI, so it isn't ideal
        // this is why I now prefer ImGui (and ofxMSAControlFreakImGui https://github.com/memo/ofxMSAControlFreakImGui)
        gui.addPage(tutorial.params);

        // default keys are space (toggle show/hide)
        gui.setDefaultKeys(true);
    }

    void draw() {
        tutorial.draw();
    }

    void keyPressed(int key) {
        switch (key) {
        case 's': tutorial.params.saveXmlValues(); break;
        case 'S': tutorial.params.saveXmlSchema(); break;
        case 'l': tutorial.params.loadXmlValues(); break;
        case 'L': tutorial.params.loadXmlSchema(); break;
        }
    }
};

//========================================================================
int main() {
    ofSetupOpenGL(1100, 800, OF_WINDOW);
    ofRunApp(new ofApp);
}

