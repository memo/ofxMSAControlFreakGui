#pragma once

#include "ofxMSAControlFreakGui/src/Panel.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
            
            class Page : public Panel {
            public:
                friend class Gui;
                friend class LayoutManager;
                
                Page(Container *parent, ParameterGroup *p, int index);
                
                void update();
                
            protected:
                int index;
                
                ScrollBar *scrollbar;
            };
            
            
        }
    }
}