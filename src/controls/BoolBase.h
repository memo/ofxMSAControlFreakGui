#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase : public Control {
            public:
                
                //--------------------------------------------------------------
                BoolBase(Container *parent, string s) : Control(parent, ParameterPtr(new ParameterBool(s, NULL))) {
                    init();
                }
                
                //--------------------------------------------------------------
                BoolBase(Container *parent, ParameterPtr p) : Control(parent, p) {
                    init();
                }
                
                //--------------------------------------------------------------
                void init() {
                    paramT = dynamic_cast<ParameterBool*>(getParameter().get());
                }
                
                //--------------------------------------------------------------
                void setMode(ParameterBool::Mode mode) {
                    paramT->setMode(mode);
                }
                
                //--------------------------------------------------------------
                void toggle() {
                    paramT->setValue(!paramT->getValue());
                }
                
                //--------------------------------------------------------------
                void keyPressed( int key ) {
                    if(key==keyboardShortcut) toggle();
                }
                
                //--------------------------------------------------------------
                void onKeyEnter() {
                    toggle();
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    if(button == 0) {
                        if(paramT->getMode() == ParameterBool::kBang || paramT->getMode() == ParameterBool::kPush) paramT->setValue(true);
                        else toggle();
                    }
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    if(paramT->getMode() == ParameterBool::kPush) paramT->setValue(false);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(paramT->getMode() == ParameterBool::kBang && paramT->getValue()) paramT->setValue(false);
                }
                
            protected:
                ParameterBool *paramT;
            };
            
        }
    }
}