#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public Control {
            public:

                //--------------------------------------------------------------
                SliderT(Container *parent, string s) : Control(parent, ParameterPtr(new ParameterSingleValueT<T>(NULL, s))) {
                    init();
                }
                
                //--------------------------------------------------------------
                SliderT(Container *parent, ParameterPtr p) : Control(parent, p) {
                    init();
                }

                //--------------------------------------------------------------
                void init() {
                    paramT = dynamic_cast<ParameterSingleValueT<T>*>(getParameter().get());
                }
                
                //--------------------------------------------------------------
                void setup() {
                    width   = getConfig().layout.columnWidth;
                    height  = getConfig().layout.buttonHeight;
                }

                //--------------------------------------------------------------
                void inc(T amount) {
                    paramT->inc(amount);
                }
                
                //--------------------------------------------------------------
                void dec(T amount) {
                    paramT->dec(amount);
                }
                
                
                //--------------------------------------------------------------
                void updateSlider() {
                    if(!enabled) return;
                    if(isMousePressed()) {
                        paramT->setMappedFrom(ofGetMouseX(), x, x + width);
                    }
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
                    
                    float barwidth = ofClamp(paramT->getMappedTo(0, width), 0, width);
                    
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setSliderColor(false);
                    ofRect(0, 0, width, c.layout.sliderHeight);
                    
                    setSliderColor(true);
                    ofRect(0, 0, barwidth, c.layout.sliderHeight);
                    
                    string s = paramT->getName() + ": " + ofToString(paramT->getValue());
                    drawText(c.layout.textPos.x, c.layout.sliderHeight/2 + c.layout.textPos.y, s);
                    
                    
                    if(paramT->getSnap()) {
                        float xinc = ofMap(paramT->getIncrement(), paramT->getMin(), paramT->getMax(), 0, width);
                        if(xinc >=2) {
                            setColor(c.colors.bg[0]);
                            ofSetLineWidth(1);
                            for(float f=0; f<=width; f+=xinc) {
                                ofLine(f, 0, f, c.layout.sliderHeight);
                            }
                        }
                    }
                    
                    if(paramT->getClamp()) {
                        setColor(ofColor(c.colors.text[1].r, c.colors.text[1].g, c.colors.text[1].b, 128));
                        int w = 2;
                        int h = c.layout.sliderHeight;
                        ofRect(0, 0, w, h);
                        ofRect(width-w-1, 0, w, h);
                    }
                }
                
                
            protected:
                ParameterSingleValueT<T> *paramT;
                
            };
        }
    }
}
