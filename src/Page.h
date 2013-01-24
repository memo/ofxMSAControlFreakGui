#pragma once

#include "ofxMSAControlFreakGui/src/Panel.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class Page : public Panel {
            public:
                friend class Gui;
                friend class LayoutManager;
                
                Page(Container *parent, ParameterGroup *p, int index);
                
            protected:
                int index;
                
            };
            
            
        }
    }
}