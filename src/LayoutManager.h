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
                int scrollY;
                bool doWrap;
                ofRectangle boundRect;

                LayoutManager();
                void update(Container &root);
                
                ofRectangle getCurRect() { return _curRect; }
                
            protected:
                int _scrollY;   // actual one, scrollY lerps to this
//                int panelDepth;
                ofVec2f     _curHead;
                ofRectangle _curRect;
                
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                void prepareControl(Control &control, ofVec2f &containerScale, int panelDepth, ofVec2f &maxPos);
                void prepareContainer(Container &container);
            };
            
            
        }
    }
}

