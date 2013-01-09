#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class Panel;
            
//            class LayoutManager;
//            typedef std::tr1::shared_ptr<LayoutManager> LayoutManagerPtr;

            
            // for auto-layout
            class LayoutManager {
            public:
                
//                friend class Panel;
                
                int scrollY;
                bool doWrap;
                ofRectangle boundRect;
                ofVec2f     curPos;
                ofRectangle rect;
                
                LayoutManager();
                void prepareForDraw(Container &container);
                void update();
                
            protected:
                int _scrollY;   // actual one, scrollY lerps to this
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                
            };
            
            
        }
    }
}

