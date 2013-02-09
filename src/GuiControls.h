#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/ControlProperties.h"

namespace msa {
    namespace controlfreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            class Scrollbar;
            
            class GuiControls : public Container {
            private:
                friend class Gui;
                
                ControlProperties *_pControlProperties;
                
                GuiControls(Container *parent);
                
                void update();
                void draw();

//                BoolBase *wrapButton;
                BoolBase *pagesButton;
                OptionsBase *pagesDropdown;
                ScrollBar *scrollbar;
                
                void updatePagesList();
            };
            
        }
    }
}

