#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/controls/BoolSimpleBox.h"
#include "ofxMSAControlFreakGui/src/controls/SliderRawT.h"

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public Container {
            public:
                
                //--------------------------------------------------------------
                SliderT(Container *parent, Parameter* p) : Container(parent, p) {
                    setZ(-1);
//                    layout.positionMode = LayoutSettings::kAbsolute;
//                    layout.width = 1;
//                    layout.height = 1;
                    
                    slider = new SliderRawT<T>(parent, p);
                    slider->layout.positionMode = LayoutSettings::kAbsolute;
                    slider->setZ(0);
                    addControl(slider);
                    
                    decButton = new BoolSimpleBox(this, "<");
                    decButton->layout.positionMode = LayoutSettings::kAbsolute;
                    decButton->setZ(1);
                    decButton->setMode(ParameterBool::kBang);
                    decButton->getParameter().setTooltip("dec");
                    addControl(decButton);

                    incButton = new BoolSimpleBox(this, ">");
                    incButton->layout.positionMode = LayoutSettings::kAbsolute;
                    incButton->setZ(1);
                    incButton->setMode(ParameterBool::kBang);
                    incButton->getParameter().setTooltip("inc");
                    addControl(incButton);

                    clampButton = new BoolSimpleBox(this, "c");
                    clampButton->layout.positionMode = LayoutSettings::kAbsolute;
                    clampButton->setZ(1);
                    clampButton->setMode(ParameterBool::kToggle);
                    clampButton->getParameter().setTooltip("Clamp");
                    clampButton->getParameter().trackVariable(&p->getClamp());
                    addControl(clampButton);

                    snapButton = new BoolSimpleBox(this, "s");
                    snapButton->layout.positionMode = LayoutSettings::kAbsolute;
                    snapButton->setZ(1);
                    snapButton->setMode(ParameterBool::kToggle);
                    snapButton->getParameter().setTooltip("Snap");
                    snapButton->getParameter().trackVariable(&p->getSnap());
                    addControl(snapButton);

                    moreButton = new BoolSimpleBox(this, ".");
                    moreButton->layout.positionMode = LayoutSettings::kAbsolute;
                    moreButton->setZ(1);
                    moreButton->setMode(ParameterBool::kBang);
                    moreButton->getParameter().setTooltip("More... (coming soon)");
                    addControl(moreButton);
                }
                
                //--------------------------------------------------------------
                void update() {
//                    slider->layout.set(0, 0, width, height);
                    
                    int p = 3;
                    int h = slider->height / 2;
                    int w = slider->height / 2;
                    int y = slider->height - h - p;
                    
                    decButton->layout.set(0, y, w, h);
                    snapButton->layout.set(slider->width - (w + p)*4, y, w, h);
                    clampButton->layout.set(slider->width - (w + p)*3, y, w, h);
                    moreButton->layout.set(slider->width - (w + p)*2, y, w, h);
                    incButton->layout.set(slider->width - (w + p), y, w, h);
                    
                    if(decButton->getParameter().value()) slider->dec(1);
                    if(incButton->getParameter().value()) slider->inc(1);
//                    if(snapButton->getParameter().hasChanged()) slider->getParameter().update();
//                    if(clampButton->getParameter().hasChanged()) slider->getParameter().update();
                    if(moreButton->getParameter().value()) {
                        //                            ofSystemAlertDialog("Hello");
                    }
                }

                
            protected:
                BoolBase *moreButton;
                BoolBase *snapButton;
                BoolBase *clampButton;
                BoolBase *incButton;
                BoolBase *decButton;
                SliderRawT<T> *slider;
                
            };
        }
    }
}
