#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            class List;
            class Options;
            class Scrollbar;
            
            class GuiControls : public Container {
            private:
                friend class Gui;
                
                Gui *_pgui;
                
                GuiControls(Container *parent);
                
                void update();

//                BoolBase *wrapButton;
                BoolBase *pagesButton;
                Options *pagesDropdown;
                ScrollBar *scrollbar;
                
                void updatePagesList();
            };
            
        }
    }
}

