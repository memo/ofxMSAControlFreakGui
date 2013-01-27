#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            class Scrollbar;
            
            class GuiControls : public Container {
            private:
                friend class Gui;
                
                Gui *_pgui;
                
                GuiControls(Container *parent);
                
                void update();

//                BoolBase *wrapButton;
                BoolBase *pagesButton;
                OptionsBase *pagesDropdown;
                ScrollBar *scrollbar;
                
                void updatePagesList();
            };
            
        }
    }
}

