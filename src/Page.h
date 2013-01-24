#pragma once

#include "ofxMSAControlFreakGui/src/Panel.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
//            typedef Panel Page;
            
//            class Gui;
            class Container;
            
            class Page : public Panel {
            public:
                Page(Container *parent, ParameterGroup *p) : Panel(parent, p, false) {}
                
            protected:
//                int index;
                
            };
            
            
        }
    }
}