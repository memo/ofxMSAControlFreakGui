#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class OptionsBase : public Control {
            public:
                
                //--------------------------------------------------------------
                OptionsBase(Container *parent, string s) : Control(parent, new ParameterNamedIndex(s)) {
                    paramT = dynamic_cast<ParameterNamedIndex*>(&getParameter());
                    init();
                }
                
                //--------------------------------------------------------------
                OptionsBase(Container *parent, ParameterNamedIndex* p) : Control(parent, p) {
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
                    int a = this->y + titleHeight;
                    int b = a + listHeight();
                    mouseOverIndex = floor(ofMap(y, a, b, 0, paramT->size(), true));
                }
                
                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    if(isMousePressed()) onPress(x, y, button);
                }
                
                
                //--------------------------------------------------------------
                void onRollOut() {
                    mouseOverIndex = -1;
                }
                
                //--------------------------------------------------------------
                int listHeight() {
                    return lineHeight * paramT->size();
                }

                
                //--------------------------------------------------------------
                void drawTitle() {
                    height = titleHeight;
//                    drawBg(pconfig->colors.toggle.full);
//                    drawBorder();
//                    drawTextCentered();
                    height = titleHeight;
                    
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    drawText(pconfig->layout.textPos.x, pconfig->layout.textPos.y, getName() + ": " + paramT->getSelectedLabel());
                    drawBorder();
                }
                
                //--------------------------------------------------------------
                void drawList() {
                    ofTranslate(0, titleHeight);
                    
                    height = listHeight();
                    drawBg();
                    drawBorder();
                    ofFill();
                    
                    int numLabels = paramT->size();
                    for(int i=0; i < numLabels; i++) {
                        setTextColor();
                        float curY = i * lineHeight;
                        if(i == mouseOverIndex) {
                            ofNoFill();
                            ofRect(0, curY+3, width, lineHeight);
                        }
                        if(i == getParameter().value()) {
                            ofFill();
                            ofRect(0, curY+3, width, lineHeight);
                            setBGColor();
                        }
                        
                        pconfig->drawString(paramT->getLabel(i), pconfig->layout.textPos.x, curY + pconfig->layout.textPos.y);
                    }
                }
                
                //--------------------------------------------------------------
                void draw() {
                    
                    drawTitle();
                    
                    drawList();
                    
                    layout.height = height = titleHeight + listHeight();
                }
                
            protected:
                ParameterNamedIndex *paramT;
                int mouseOverIndex;
                float lineHeight;
                float titleHeight;
            };
            
        }
    }
}