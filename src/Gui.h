

#include "ofxMSAControlFreakGui/src/Container.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton;
            class Config;
            
            class Gui : public Container {
            public:
                Config config;
                
                Gui();
                ~Gui();
                
                void setup();
                
                void setDefaultKeys(bool b);
                
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
                Page& getPage(int i);				// 1 based index of page
                Page& getPage(string name);			// returns page by name
                Page& getCurrentPage();				// returns current page
                
                //                // create and add a page with given name
                //                Page& addPage(string name = "");
                
                // create and add a page from the given parameter group
                Page& addParameters(ParameterGroup &parameters);
                
                // add a page
                Page& addPage(Page* page);
                
                // append given parameter group to current page
                //                Page& addParameters(ParameterGroup* parameters);
                
                
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
                vector<Page*> pages;
                
                void addListeners();
                void removeListeners();
                void setDraw(bool b);
            };
            
        }
    }
}
