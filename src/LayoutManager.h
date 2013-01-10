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
                int scrollY;
                bool doWrap;
                ofRectangle boundRect;
                ofVec2f     curHead;
                ofRectangle curRect;
                
                LayoutManager();
                void update(Container &root);
                
            protected:
                int _scrollY;   // actual one, scrollY lerps to this
                ofVec2f getMaxPos();
                ofVec2f clampPoint(ofVec2f p);
                void prepareControl(Control &control, Config &config, ofVec2f &containerScale, int panelDepth, ofVec2f &maxPos);
                void prepareContainer(Container &container);
            };
            
            
        }
    }
}

