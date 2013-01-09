#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/controls/BoolSimpleBox.h"
#include "ofxMSAControlFreakGui/src/controls/SliderRawT.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public Container {
            public:
                
                //--------------------------------------------------------------
                SliderT(Container *parent, Parameter* p) : Container(parent, p) {
                    slider = new SliderRawT<T>(parent, p);
                    slider->doAutoLayout = false;
                    addControl(slider);
                    
                    clampButton = new BoolSimpleBox(this, "c");
                    clampButton->doAutoLayout = false;
                    clampButton->setZ(1);
                    clampButton->setMode(ParameterBool::kToggle);
                    clampButton->getParameter().setTooltip("Clamp");
                    clampButton->getParameter().trackVariable(&p->getClamp());
                    addControl(clampButton);

                    snapButton = new BoolSimpleBox(this, "s");
                    snapButton->doAutoLayout = false;
                    snapButton->setZ(1);
                    snapButton->setMode(ParameterBool::kToggle);
                    snapButton->getParameter().setTooltip("Snap");
                    snapButton->getParameter().trackVariable(&p->getSnap());
                    addControl(snapButton);

                    moreButton = new BoolSimpleBox(this, ">");
                    moreButton->doAutoLayout = false;
                    moreButton->setZ(1);
                    moreButton->setMode(ParameterBool::kBang);
                    moreButton->getParameter().setTooltip("More... (coming soon)");
                    addControl(moreButton);
                }
                
//                //--------------------------------------------------------------
//                void inc(T amount) {
//                    getParameter().inc(amount);
//                }
//                
//                //--------------------------------------------------------------
//                void dec(T amount) {
//                    getParameter().dec(amount);
//                }
//                
//                
//                //--------------------------------------------------------------
//                void updateSlider() {
//                    if(!enabled) return;
//                    if(isMousePressed()) {
//                        getParameter().setMappedFrom(ofGetMouseX(), x, x + width);
//                    }
//                }
//                
//                //--------------------------------------------------------------
//                void onPress(int x, int y, int button) {
//                    updateSlider();
//                }
//                
//                //--------------------------------------------------------------
//                void onDragOver(int x, int y, int button) {
//                    updateSlider();
//                }
//                
//                //--------------------------------------------------------------
//                void onDragOutside(int x, int y, int button) {
//                    updateSlider();
//                }
//                
//                //--------------------------------------------------------------
//                void onKeyRight() {
//                    inc(1);
//                }
//                
//                //--------------------------------------------------------------
//                void onKeyLeft() {
//                    dec(1);
//                }
//                
//                //--------------------------------------------------------------
//                void onKeyUp() {
//                    inc(10);
//                }
//                
//                //--------------------------------------------------------------
//                void onKeyDown() {
//                    dec(10);
//                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    slider->localRect.set(0, 0, width, height);

                    int p = 3;
                    int h = height / 2;
                    int w = height / 2;
                    int y = height - h - p;
                    
                    snapButton->localRect.set(width - (w + p)*3, y, w, h);
                    clampButton->localRect.set(width - (w + p)*2, y, w, h);
                    moreButton->localRect.set(width - (w + p), y, w, h);
                    
                    if(snapButton->getParameter().hasChanged()) slider->getParameter().update();
                    if(clampButton->getParameter().hasChanged()) slider->getParameter().update();
                    if(moreButton->getParameter().value()) {
//                            ofSystemAlertDialog("Hello");
                    }
                }
                
                
            protected:
                BoolBase *moreButton;
                BoolBase *snapButton;
                BoolBase *clampButton;
                SliderRawT<T> *slider;
                
            };
        }
    }
}
