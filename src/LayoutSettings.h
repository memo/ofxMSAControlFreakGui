#pragma once 

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class LayoutSettings : public ofRectangle {
            public:

                enum Mode {
                    kRelative,  // normal (controls are placed in a free flowing manner, like html, layout.position is offset off calculated)
                    kAbsolute,  // layout.position is relative to container
                    kFixed      // layout.position is relative to screen
                };
                
                Mode     positionMode;
                bool    doAffectFlow;
                bool    doIncludeInContainerRect;
                bool	newColumn;
                ofVec2f paddingPre;
                ofVec2f paddingPost;
                
                LayoutSettings() {
                    positionMode = kRelative;
                    doAffectFlow = true;
                    doIncludeInContainerRect = true;
                    newColumn = false;
                }
            };

        }
    }
}