#pragma once

#include "ofxMSAControlFreakGui/src/controls/OptionsBase.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class OptionsList : public OptionsBase {
            public:
                
                //--------------------------------------------------------------
                OptionsList(Container *parent, string s) : OptionsBase(parent, new ParameterNamedIndex(s, NULL)) {
                    lineHeight = pconfig->layout.dropdownListTextHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }
                
                //--------------------------------------------------------------
                OptionsList(Container *parent, ParameterNamedIndex* p) : OptionsBase(parent, p) {
                    lineHeight = pconfig->layout.dropdownListTextHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }
                
            };
            
        }
    }
}