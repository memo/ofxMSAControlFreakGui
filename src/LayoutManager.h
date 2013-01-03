#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class Panel;
            
            class LayoutManager;
            typedef std::tr1::shared_ptr<LayoutManager> LayoutManagerPtr;

            
            // for auto-layout
            class LayoutManager {
            public:
                bool doWrap;
                ofRectangle boundRect;
                ofVec2f     curPos;
                ofRectangle rect;
                
                LayoutManager();
                void prepareForDraw(Container &container);
                void draw(Config &config);
                
            protected:
                int scrollY;
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                
            };
            
            
        }
    }
}

