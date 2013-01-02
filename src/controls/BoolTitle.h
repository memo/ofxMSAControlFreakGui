#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolTitle : public BoolBase {
            public:
                
                bool bRecursive;
                bool bMouseOverRecursive;

                vector<bool>buttons;
                vector<bool>buttonsOver;
//                bool bMenu;
//                bool bMouseOverMenu;
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, string s) : BoolBase(parent, s) { }
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, Parameter *p) : BoolBase(parent, p) { }
                
                //--------------------------------------------------------------
                void setup() {
                    BoolBase::setup();
                    bRecursive = false;
                    
                    buttons.resize(3);
                    buttonsOver.resize(buttons.size());
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
//                    bMenu = bMouseOverMenu;
//                    if(bMouseOverMenu) return;
                    for(int i=0; i<buttons.size(); i++) {
                        buttons[i] = buttonsOver[i];
                        if(buttons[i]) {
                            getParent()->buttonPressed(i);
                            return;
                        }
                    }
                    
                    BoolBase::onPress(x, y, button);
                    bRecursive = bMouseOverRecursive;
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    BoolBase::onRelease(x, y, button);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!parameter) return;
                    
                    if(parameter->getName().empty()) return;
                    
                    
                    // draw bg
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, width, height);
                    
                    // circle buttons
                    int buttonWidth = height * 0.7;
                    for(int i=0; i<buttons.size(); i++) {
                        int bx = width - buttonWidth * (i+1);
                        buttonsOver[i] = isMouseOver() && ofInRange(getMouseX() - x, bx, bx + buttonWidth);
                        if(buttonsOver[i]) setColor(ofColor(255, 100));
                        else setColor(ofColor(0, 100));
                        ofCircle(bx + buttonWidth/2, height/2, height/4);
                    }
                    
                    // recursive button
                    bMouseOverRecursive = isMouseOver() && getMouseX() < x + buttonWidth;
                    if(bMouseOverRecursive) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
//                    ofCircle(height/2, height/2, height/4);
                    ofRect(0, 0, buttonWidth, height);

                    
                    drawText(buttonWidth/2-3, 15, (parameter->getValue() ? "-" : "+"));
                    drawText(buttonWidth + 5, 15);
                    ofSetLineWidth(2);
                    drawBorder(getConfig().colors.text);
                    
                    if(doTooltip()) {
                        if(buttonsOver[0]) {
                            Renderer::instance().setToolTip("Open preset menu");
                            
                        } else if(buttonsOver[1]) {
                            Renderer::instance().setToolTip("Load preset");
                            
                        } else if(buttonsOver[2]) {
                            Renderer::instance().setToolTip("Save preset");
                            
                        } else {
                            string sverb = parameter->getValue() ? "close" : "open";
                            string starget = bMouseOverRecursive ? "panel and all sub-panels" : "panel. Right-click to temporarily isolate";
    //                        if(parameter->getValue()) s = "Click to close panel [" + parameter->getName() + "]";
    //                        else s = "Click to open panel";
                            Renderer::instance().setToolTip("Click to " + sverb + " " + starget);
                        }
                    }
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}