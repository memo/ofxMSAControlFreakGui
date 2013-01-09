#pragma once 

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class LayoutSettings : public ofRectangle {
            public:
                int     positionMode;   // 0: relative (normal), 1: absolute (relative to container), 2: fixed (relative to screen)
                bool    doAffectFlow;
                bool    doIncludeInContainerRect;
                bool	newColumn;
                ofVec2f paddingPre;
                ofVec2f paddingPost;
                
                LayoutSettings() {
                    positionMode = 0;
                    doAffectFlow = true;
                    doIncludeInContainerRect = true;
                    newColumn = false;
                }
            };

        }
    }
}