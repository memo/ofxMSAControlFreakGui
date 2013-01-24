

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class GuiControls;
            
            class Gui : public Container {
            public:
                Gui();
                ~Gui();
                
                void setDefaultKeys(bool b);
                
                void toggleDraw();
                void show();		// simply calls setDraw(true);
                void hide();		// simply calls setDraw(false);
                bool isOn();

                
                // TABMANAGER:
                void nextPage();
                void prevPage();
                void setPage(int i);				// 1 based index of page
                void setPage(string name);

                int getNumPages();
                Page& getPage(int i);				// 1 based index of page
                Page& getPage(string name);			// returns page by name
                Page& getCurrentPage();				// returns current page
               
                
                
                
                //                // create and add a page with given name
                //                Page& addPage(string name = "");
                
                // create and add a page from the given parameter group
                Page& addParameters(ParameterGroup &parameters);
                
                // TABMANAGER:
                // add a page
                Page& addPage(Page* page);
                

                //--------------------------------------------------------------
                // ADVANCED FUNCTIONS
                
                // by default all gui events are managed automatically
                // by default these are called automatically so you don't need to call them
                // however if you've disabled AutoEvents, then you need to call them manually from your app. IMPORTANT!
//                void setup();
                void update();
                void draw();
                void mouseMoved(int x, int y);
                void mousePressed(int x, int y, int button);
                void mouseDragged(int x, int y, int button);
                void mouseReleased(int x, int y, int button);
                void keyPressed(int key);
                void keyReleased(int key);
                
                
            protected:
                bool    isSetup;
                bool    doDefaultKeys;
                int     currentPageIndex;
                bool    doDraw;
                vector<Page*> pages;
                GuiControls *guiControls;
                
                bool checkOkToRun();
                void setDraw(bool b);
            };
            
        }
    }
}
