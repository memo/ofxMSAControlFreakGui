#pragma once

#include "ofxMSAControlFreakGui/src/Controls/OptionsBase.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class OptionsBoxes : public OptionsBase {
            public:
                
                //--------------------------------------------------------------
                OptionsBoxes(Container *parent, string s) : OptionsBase(parent, new ParameterNamedIndex(s, NULL)) {
                    lineHeight = pconfig->layout.buttonHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }
                
                //--------------------------------------------------------------
                OptionsBoxes(Container *parent, ParameterNamedIndex* p) : OptionsBase(parent, p) {
                    lineHeight = pconfig->layout.buttonHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }
                
            };
            
        }
    }
}