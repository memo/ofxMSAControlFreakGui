#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Content  : public Control {
            public:
                float			fixwidth;
                float			fixheight;
                ofBaseDraws		*content;
                
                Content(Container *parent, ParameterPtr p, ofBaseDraws& content, float fixwidth=250.0);
                void setup();
                void onDraw();
            };
            
        }
    }
}