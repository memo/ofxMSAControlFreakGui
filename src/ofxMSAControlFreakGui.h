

#pragma once

#include "ofMain.h"

#include "ofxMSAControlFreakGui/src/Config.h"
#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/Panel.h"
#include "ofxMSAControlFreakGui/src/Config.h"
#include "ofxMSAControlFreakGui/src/LayoutSettings.h"
#include "ofxMSAControlFreakGui/src/Controls/BoolButton.h"
#include "ofxMSAControlFreakGui/src/Controls/BoolSimpleBox.h"
#include "ofxMSAControlFreakGui/src/Controls/BoolSimpleCircle.h"
#include "ofxMSAControlFreakGui/src/Controls/BoolTitle.h"
#include "ofxMSAControlFreakGui/src/Controls/BoolToggle.h"
#include "ofxMSAControlFreakGui/src/Controls/ColorPicker.h"
#include "ofxMSAControlFreakGui/src/Controls/Content.h"
#include "ofxMSAControlFreakGui/src/Controls/DropdownList.h"
#include "ofxMSAControlFreakGui/src/Controls/List.h"
#include "ofxMSAControlFreakGui/src/Controls/Options.h"
#include "ofxMSAControlFreakGui/src/Controls/FPSCounter.h"
#include "ofxMSAControlFreakGui/src/Controls/QuadWarp.h"
#include "ofxMSAControlFreakGui/src/Controls/ScrollBar.h"
#include "ofxMSAControlFreakGui/src/Controls/Slider2d.h"
#include "ofxMSAControlFreakGui/src/Controls/SliderT.h"
#include "ofxMSAControlFreakGui/src/Renderer.h"

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton;
            class Config;
            
            class Gui {
            public:
                Config config;
                
                Gui();
                ~Gui();
                
                void setup();
                
                void setDefaultKeys(bool b);
                
                void setDraw(bool b);
                void toggleDraw();
                void show();		// simply calls setDraw(true);
                void hide();		// simply calls setDraw(false);
                bool isOn();
                
                void nextPage();
                void prevPage();
                void setPage(int i);				// 1 based index of page
                void setPage(string name);

//                void nextPageWithBlank();		// cycles through pages, and closes after last page
                
                int getNumPages();
                Panel& getPage(int i);				// 1 based index of page
                Panel& getPage(string name);			// returns page by name
                Panel& getCurrentPage();				// returns current page
                
//                // create and add a page with given name
//                Panel& addPage(string name = "");
                
                // create and add a page from the given parameter group
                Panel& addPage(ParameterGroup &parameters);
                
                // add a page
                Panel& addPanel(Panel* page);
                
                // append given parameter group to current page
//                Panel& addParameters(ParameterGroup* parameters);
                

                //--------------------------------------------------------------
                // ADVANCED FUNCTIONS
                
                // by default all gui events are managed automatically (registered when gui is visible, de-registered when gui is not visible)
                // over that behaviour with these
                void enableAutoEvents();
                void disableAutoEvents();
                bool getAutoEvents();
                
                
                // by default these are called automatically so you don't need to call them
                // however if you've disabled AutoEvents, then you need to call them manually from your app. IMPORTANT!
                void update(ofEventArgs& e);
                void draw(ofEventArgs& e);
                void mouseMoved(ofMouseEventArgs& e);
                void mousePressed(ofMouseEventArgs& e);
                void mouseDragged(ofMouseEventArgs& e);
                void mouseReleased(ofMouseEventArgs& e);
                void keyPressed(ofKeyEventArgs& e);
                void keyReleased(ofKeyEventArgs& e);

                
            protected:
                bool    isSetup;
                bool    doAutoEvents;
                bool    eventsAreRegistered;
                bool    doDefaultKeys;
                int     currentPageIndex;
                bool    doDraw;
                vector<Panel*> pages;
                
                void addListeners();
                void removeListeners();
            };
            
        }
    }
}

