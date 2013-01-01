#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            
            // for auto-layout
            class LayoutManager {
            public:
                ofRectangle maxRect;
                ofVec2f     curPos;
                ofRectangle rect;
                
                void update(Panel &panel);
                
            protected:
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                
            };
            
            
            typedef std::tr1::shared_ptr<LayoutManager> LayoutManagerPtr;
            
        }
    }
}

