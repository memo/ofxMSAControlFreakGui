#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            
            class GuiControls : public Container {
            private:
                friend class Gui;
                
                GuiControls(Container *parent);
                
                void update();

                BoolBase *wrapButton;
                BoolBase *pagesButton;
                List *pagesDropdown;
                
                void updatePagesList();
            };
            
        }
    }
}

