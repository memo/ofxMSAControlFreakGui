#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Options : public Control {
            public:
                
                //--------------------------------------------------------------
                Options(Container *parent, string s) : Control(parent, new ParameterNamedIndex(s, NULL), true) {
                    paramT = dynamic_cast<ParameterNamedIndex*>(&getParameter());
                    init();
                }
                
                //--------------------------------------------------------------
                Options(Container *parent, ParameterNamedIndex* p) : Control(parent, p) {
                    paramT = p;
                    init();
                }
                
                //--------------------------------------------------------------
                void init() {
                    mouseOverIndex = -1;
                }
                
                //--------------------------------------------------------------
                void setMode(ParameterNamedIndex::Mode mode) {
                    paramT->setMode(mode);
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    onMouseMove(x, y);
                    paramT->set(mouseOverIndex);
                }
                
                //--------------------------------------------------------------
                void onMouseMove(int x, int y) {
                    int a = this->y;
                    int b = this->y + getConfig().layout.buttonHeight * paramT->getNumLabels();
                    mouseOverIndex = floor(ofMap(y, a, b, 0, paramT->getNumLabels(), true));
                }
                
                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    onPress(x, y, button);
                }
                
                
                //--------------------------------------------------------------
                void onRollOut() {
                    mouseOverIndex = -1;
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    int numLabels = paramT->getNumLabels();
                    layout.height = height = getConfig().layout.buttonHeight * numLabels + 3;
                    
                    setBGColor();
                    ofFill();
                    ofRect(0, 0, width, height);
                    
                    drawBorder();
                    ofFill();
                    
                    for(int i=0; i < numLabels; i++) {
                        setTextColor();
                        float curY = i * getConfig().layout.buttonHeight;
                        if(i == mouseOverIndex) {
                            ofNoFill();
                            ofRect(0, curY+3, width, getConfig().layout.buttonHeight);
                        }
                        if(i == getParameter().value()) {
                            ofFill();
                            ofRect(0, curY+3, width, getConfig().layout.buttonHeight);
                            setBGColor();
                        }
                        
                        getConfig().drawString(paramT->getLabel(i), getConfig().layout.textPos.x, curY + getConfig().layout.textPos.y);
                    }
                }
                
            protected:
                ParameterNamedIndex *paramT;
                int mouseOverIndex;
            };
            
        }
    }
}