#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/ControlOptions.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            class Scrollbar;
            
            class GuiControls : public Container {
            private:
                friend class Gui;
                
                ControlOptions *_pControlOptions;
                
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

