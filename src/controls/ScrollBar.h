#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class ScrollBar : public Control {
            public:
                
                float barThickness;
                
                //--------------------------------------------------------------
                ScrollBar(Container *parent) : Control(parent, new ParameterFloat("ScrollBar", NULL), true) {
                    getParameter().setClamp(true);
                    barThickness = 0.2; // default value
                }
                
                //--------------------------------------------------------------
                ScrollBar(Container *parent, Parameter* p) : Control(parent, p) {
                    barThickness = 0.2; // default value
                }
                
                //--------------------------------------------------------------
                void inc(float amount) {
                    getParameter().inc(amount);
                }
                
                //--------------------------------------------------------------
                void dec(float amount) {
                    getParameter().dec(amount);
                }
                
                
                //--------------------------------------------------------------
                void updateSlider() {
                    if(!enabled) return;
                    if(isMousePressed()) {
                        getParameter().setMappedFrom(ofGetMouseY(), y, y + height);
                    }
                    if(getParameter().value() > 1 - barThickness) getParameter() = 1 - barThickness;
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onKeyRight() {
                    inc(1);
                }
                
                //--------------------------------------------------------------
                void onKeyLeft() {
                    dec(1);
                }
                
                //--------------------------------------------------------------
                void onKeyUp() {
                    inc(10);
                }
                
                //--------------------------------------------------------------
                void onKeyDown() {
                    dec(10);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    
                    ofFill();
                    
                    Config &c = getConfig();
                    
                    
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setSliderColor(false);
                    ofRect(0, 0, width, height);
                    
                    setSliderColor(true);
                    int dbary = getParameter().value() * height;
                    int dbart = barThickness * height;
                    ofRect(0, dbary, width, dbart);
                    
//                    string s = getParameter().getName() + ": " + ofToString((float)getParameter().value());
//                    drawText(c.layout.textPos.x + 10, c.layout.sliderHeight/2 + c.layout.textPos.y, s);
                    
                    drawBorder();
                    
                }
                
                
            };
        }
    }
}
