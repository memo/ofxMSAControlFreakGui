#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/controls/BoolSimpleBox.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public Container {
            public:
                
                //--------------------------------------------------------------
                SliderT(Container *parent, Parameter* p) : Container(parent, p) {
                    button = new BoolSimpleCircle(this, ">");
                    button->doAutoLayout = false;
                    button->setMode(ParameterBool::kBang);
                    button->getParameter().setTooltip("More options");
                    addControl(button);
                }
                
                //--------------------------------------------------------------
                void inc(T amount) {
                    getParameter().inc(amount);
                }
                
                //--------------------------------------------------------------
                void dec(T amount) {
                    getParameter().dec(amount);
                }
                
                
                //--------------------------------------------------------------
                void updateSlider() {
                    if(!enabled) return;
                    if(isMousePressed()) {
                        getParameter().setMappedFrom(ofGetMouseX(), x, x + width);
                    }
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    printf("on");
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
                    
                    float barwidth = ofClamp(getParameter().getMappedTo(0, width), 0, width);
                    
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setSliderColor(false);
                    ofRect(0, 0, width, c.layout.sliderHeight);
                    
                    setSliderColor(true);
                    ofRect(0, 0, barwidth, c.layout.sliderHeight);
                    
                    string s = getParameter().getName() + ": " + ofToString((T)getParameter().value());
                    drawText(c.layout.textPos.x, c.layout.sliderHeight/2 + c.layout.textPos.y, s);
                    
                    
                    if(getParameter().getSnap()) {
                        float xinc = ofMap(getParameter().getIncrement(), getParameter().getMin(), getParameter().getMax(), 0, width);
                        if(xinc >=2) {
                            setColor(c.colors.bg[0]);
                            ofSetLineWidth(1);
                            for(float f=0; f<=width; f+=xinc) {
                                ofLine(f, 0, f, c.layout.sliderHeight);
                            }
                        }
                    }
                    
                    if(getParameter().getClamp()) {
                        setColor(ofColor(c.colors.text[1].r, c.colors.text[1].g, c.colors.text[1].b, 128));
                        int w = 2;
                        int h = c.layout.sliderHeight;
                        ofRect(0, 0, w, h);
                        ofRect(width-w-1, 0, w, h);
                    }
                    
                    drawBorder();
                    
                    
                    // extra buttons
                    {
                        int p = 3;
                        int s = height * 0.5;
                        int y = (height - s)-p;
                        button->localRect.set(width - (s + p), y, s, s);
                        if(button->getParameter().value()) {
                            ofSystemAlertDialog("Hello");
                        }
//                        button->set(button->localRect);
//                        button->onDraw();
                    }
                    
                    
                }
                
                
            protected:
                BoolSimpleCircle* button;
                
            };
        }
    }
}
