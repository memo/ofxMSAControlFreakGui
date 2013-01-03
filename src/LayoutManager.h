#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class Panel;
            
            // for auto-layout
            class LayoutManager {
            public:
                bool doWrap;
                ofRectangle maxRect;
                ofVec2f     curPos;
                ofRectangle rect;
                
                LayoutManager();
                void prepareForDraw(Panel &panel);
                void draw(Config &config);
                
            protected:
                int scrollY;
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                
            };
            
            
            typedef std::tr1::shared_ptr<LayoutManager> LayoutManagerPtr;
            
        }
    }
}

