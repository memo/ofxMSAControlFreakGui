#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreakGui/src/Config.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"
#include "ofxMSAControlFreakGui/src/Renderer.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
//            template <typename T>
//            class Control : public Control {
//            public:
//                //--------------------------------------------------------------
//                Control(Container *parent, string s) : Control(parent) {
//                    parameterOwner = true;
////                    ParameterGroup *parentParam = parent ? &(parent->getParameter()) : NULL;
//                    parameter = new T(NULL, s);
////                    name = getPath();
//                }
//
//                //--------------------------------------------------------------
//                Control(Container *parent, ParameterPtr p) : Control(parent) {
//                    if(p) {
//                        parameter = dynamic_cast<T*>(p);
//                        if(!parameter) ofLogError() << "msa::ControlFreak::gui::Control - type-casting parameter " << p->getPath();
//                        //                    if(parameter) name = getPath();
//                    }
//                    parameterOwner = false;
//                }
//
//                //--------------------------------------------------------------
//                ~Control() {
//                    if(parameterOwner && parameter) delete parameter;
//                }
//                
//
//                //--------------------------------------------------------------
//                T &getParameter() {
//                    return *parameter;
//                }
//                
//                //--------------------------------------------------------------
//                void drawText(int x, int y, string s = "", ofColor *c = NULL) {
//                    setColor(c ? c : getConfig().colors.text);
//                    getConfig().drawString(s.empty() ? getName() : s, x, y);
//                }
//                
//                //--------------------------------------------------------------
//                void setTooltip(string s="") {
//                    // if s is empty, use string from parameter
//                    if(s.empty()) s = parameter->getTooltip();
//                    if(doTooltip() && !s.empty()) {
//                        Renderer::instance().setToolTip(parameter->getTooltip());
//                    }
//                }
//
//                //--------------------------------------------------------------
//                virtual void draw() {
//                    setTooltip();
////                    ofLogVerbose() << "draw " << getPath();
//                    Control::draw();
//                }
//                
//                //--------------------------------------------------------------
//                virtual string getName() {
//                    return parameter->getName();
//                }
//                
//                //--------------------------------------------------------------
//                virtual string getPath() {
//                    return parameter->getPath();
//                }
//
//            protected:
//                T *parameter;
//            };

        }
    }
}