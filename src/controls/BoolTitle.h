#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"
#include "ofxMSAControlFreakGui/src/Renderer.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolTitle : public BoolBase {
            public:
                
                struct ButtonState {
                    ButtonState():over(false), value(false) {}
                    bool over;
                    bool value;
                };
                
                ButtonState collapseAll;
                ButtonState expandAll;
                vector<ButtonState> buttons;
                
                //--------------------------------------------------------------
                BoolTitle(Container *parent, string s) : BoolBase(parent, s) { }
                
                //--------------------------------------------------------------
                BoolTitle(Container *parent, ParameterPtr p) : BoolBase(parent, p) { }
                
                //--------------------------------------------------------------
                void setup() {
                    BoolBase::setup();
                    buttons.resize(3);
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
//                    bMenu = bMouseOverMenu;
//                    if(bMouseOverMenu) return;
                    for(int i=0; i<buttons.size(); i++) {
                        buttons[i].value = buttons[i].over;;
                        if(buttons[i].value) {
                            Panel *panel = dynamic_cast<Panel*>(getParent());
                            if(panel) {
                                panel->buttonPressed(i);  // TODO call separate functions?
                                return;
                            }
                        }
                    }
                    
                    collapseAll.value = collapseAll.over;
                    expandAll.value = expandAll.over;
                    BoolBase::onPress(x, y, button);
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    BoolBase::onRelease(x, y, button);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                                        
                    if(getName().empty()) return;
                    
                    
                    // draw bg
                    ofFill();
                    setToggleColor(paramT->getValue());
                    ofRect(0, 0, width, height);
                    
                    // circle buttons
                    int buttonWidth = height * 0.7;
                    for(int i=0; i<buttons.size(); i++) {
                        int bx = width - buttonWidth * (i+1);
                        buttons[i].over = isMouseOver() && ofInRange(getMouseX() - x, bx, bx + buttonWidth);
                        if(buttons[i].over) setColor(ofColor(255, 100));
                        else setColor(ofColor(0, 100));
                        ofCircle(bx + buttonWidth/2, height/2, height/4);
                    }
                    
                    // recursive button
//                    bMouseOverRecursive = isMouseOver() && getMouseX() < x + buttonWidth;
//                    if(bMouseOverRecursive) setColor(ofColor(255, 100));
//                    else setColor(ofColor(0, 100));
//                    ofCircle(height/2, height/2, height/4);
                    ofRect(0, 0, buttonWidth, height);

                    
                    drawText(buttonWidth/2-3, 15, (paramT->getValue() ? "-": "+"));
                    drawText(buttonWidth + 5, 15);
                    ofSetLineWidth(2);
                    drawBorder(getConfig().colors.text);
                    
                    if(doTooltip()) {
//                        if(buttonsOver[0]) {
                            Renderer::instance().setToolTip("Open preset menu");
                            
//                        } else if(buttonsOver[1]) {
                            Renderer::instance().setToolTip("Load preset");
                            
//                        } else if(buttonsOver[2]) {
                            Renderer::instance().setToolTip("Save preset");
                            
//                        } else {
                            string sverb = paramT->getValue() ? "close": "open";
//                            string starget = bMouseOverRecursive ? "panel and all sub-panels": "panel. Right-click to temporarily isolate";
    //                        if(getParameter().getValue()) s = "Click to close panel [" + getName() + "]";
    //                        else s = "Click to open panel";
//                            Renderer::instance().setToolTip("Click to " + sverb + " " + starget);
//                        }
                    }
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}