

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/GuiControls.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui : public Container {
            public:
                
                friend class GuiControls;
                friend class Container;
                
                LayoutManagerPtr pLayoutManager;
                
                Gui();
                ~Gui();
                
                void setDefaultKeys(bool b);
                
                void toggleDraw();
                void show();		// simply calls setDraw(true);
                void hide();		// simply calls setDraw(false);
                bool isOn();
                

                Page& addPage(ParameterGroup &parameters);

                void nextPage();
                void prevPage();
                void setPage(int i);				// 1 based index of page
                void setPage(string name);
                
                int getNumPages();
                Page& getPage(int i);				// 1 based index of page
                Page& getPage(string name);			// returns page by name
                Page& getCurrentPage();				// returns current page

                
                //--------------------------------------------------------------
                // ADVANCED FUNCTIONS
                
                // by default all gui events are managed automatically
                // these are called automatically so you don't need to call them
                // however if you've disabled AutoEvents, then you need to call them manually from your app. IMPORTANT!
                void update();
                void draw();
                void mouseMoved(int x, int y);
                void mousePressed(int x, int y, int button);
                void mouseDragged(int x, int y, int button);
                void mouseReleased(int x, int y, int button);
                void keyPressed(int key);
                void keyReleased(int key);
                
                Control* getActiveControl();
                
                void showControlOptions(Control *targetControl);
                
            private:
                bool    doDefaultKeys;
                bool    doDraw;
                vector<Page*> pages;
                GuiControlsPtr _pGuiControls;
                

                bool checkOkToRun();
                void setDraw(bool b);
                
                Control *_pActiveControl; // currently active control (only this control receives events)
                void setActiveControl(Control *control);
                void releaseActiveControl();
                
                
                Page& addPage(Page* page);
                int getCurrentPageIndex();
                
            };
            
        }
    }
}
