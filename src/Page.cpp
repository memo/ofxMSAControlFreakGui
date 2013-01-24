
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Page::Page(Container *parent, ParameterGroup* p, int index) : Panel(parent, p) {
                this->index = index;
//                this->pgui = gui;
                
                titleButton->getParameter().setName(ofToString(index+1) + ": " + getName());
                
                scrollbar = new ScrollBar(this);
                scrollbar->layout.positionMode = LayoutSettings::kFixed;
                scrollbar->setZ(-1);
                scrollbar->doIsolateOnActive = false;
                scrollbar->layout.doIncludeInContainerRect = false;
                scrollbar->getParameter().setTooltip("Scroll " + getPath());
                addControl(scrollbar);
            }
            
                  //--------------------------------------------------------------
            void Page::update() {
                Panel::update();
                
                // set positions and layout
                int s = pconfig->layout.buttonHeight * 0.7;
                int y = (pconfig->layout.buttonHeight - s)/2;
                int p = 3;
                
                if(layoutManager) {// && !layoutManager->doWrap) {
                    // TODO: custom scrollbar layout
                    scrollbar->visible = true;
                    scrollbar->layout.set(0, 0, pconfig->layout.scrollbarWidth, ofGetHeight());
                    float sbheight = scrollbar->layout.height;
                    scrollbar->barThickness = sbheight / layoutManager->getCurRect().height;
                    layoutManager->scrollY = ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, layoutManager->getCurRect().height - sbheight * 0.5);
                } else {
                    scrollbar->visible = false;
                }
                
            }
            
        }
    }
}
