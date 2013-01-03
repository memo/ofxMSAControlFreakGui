

#pragma once

#include "ofMain.h"
//#include "ofxXmlSettings.h"

#include "ofxMSAControlFreakGui/src/Config.h"
#include "ofxMSAControlFreakGui/src/Panel.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
    namespace ControlFreak {

        namespace gui {
            
            class BoolButton;
            class Config;
            
            class Gui {
            public:
                Config config;
                
                Gui();
                
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

                void nextPageWithBlank();		// cycles through pages, and closes after last page
                
                int getNumPages();
                Panel& getPage(int i);				// 1 based index of page
                Panel& getPage(string name);			// returns page by name
                Panel& getCurrentPage();				// returns current page
                
//                // create and add a page with given name
//                Panel& addPage(string name = "");
                
                // create and add a page from the given parameter group
                Panel& addPage(ParameterGroupPtr parameters);
                
                // add a page
                Panel& addPanel(PanelPtr page);
                
                // append given parameter group to current page
//                Panel& addParameters(ParameterGroupPtr parameters);
                

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
                vector<PanelPtr> pages;
                
                void addListeners();
                void removeListeners();
            };
            
        }
    }
}

