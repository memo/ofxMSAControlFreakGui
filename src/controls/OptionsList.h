#pragma once

#include "ofxMSAControlFreakGui/src/controls/OptionsBase.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace controlfreak {
        namespace gui {
            
            class OptionsList : public OptionsBase {
            public:
                
                //--------------------------------------------------------------
                OptionsList(Container *parent, string s) : OptionsBase(parent, new ParameterNamedIndex(s)) {
                    lineHeight = getConfig()->layout.dropdownListTextHeight;
                    titleHeight = getConfig()->layout.buttonHeight;
                }
                
                //--------------------------------------------------------------
                OptionsList(Container *parent, ParameterNamedIndex* p) : OptionsBase(parent, p) {
                    lineHeight = getConfig()->layout.dropdownListTextHeight;
                    titleHeight = getConfig()->layout.buttonHeight;
                }
                
            };
            
        }
    }
}