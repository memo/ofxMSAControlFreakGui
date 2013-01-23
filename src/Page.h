#pragma once

#include "ofxMSAControlFreakGui/src/Panel.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            
            class Page : public Panel {
            public:
                friend class Gui;
                friend class LayoutManager;
                
                Page(Gui *parent, ParameterGroup* p, int index);
                ~Page();
                
                void onUpdate();
                
            protected:
                Gui *pgui;
                LayoutManager* layoutManager;
                int index;
                
                BoolBase *wrapButton;
                BoolBase *pagesButton;
                ScrollBar *scrollbar;

                List *pagesDropdown;
                
                void updatePagesList();
                

            };
            
            
        }
    }
}