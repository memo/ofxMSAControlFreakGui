
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Page::Page(Gui *pgui, ParameterGroup* p) : Panel(NULL, p) {
                layoutManager = NULL;
                this->pgui = pgui;
                wrapButton = new BoolSimpleCircle(this, "w");
                wrapButton->layout.positionMode = 1;
                wrapButton->setZ(2);
                wrapButton->setMode(ParameterBool::kToggle);
                wrapButton->getParameter().setTooltip("Wrap");
                add(wrapButton);
                
                prevPageButton = new BoolSimpleCircle(this, "<");
                prevPageButton->layout.positionMode = 1;
                prevPageButton->setZ(2);
                prevPageButton->setMode(ParameterBool::kBang);
                prevPageButton->getParameter().setTooltip("Previous page");
                add(prevPageButton);
                
                nextPageButton = new BoolSimpleCircle(this, ">");
                nextPageButton->layout.positionMode = 1;
                nextPageButton->setZ(2);
                nextPageButton->setMode(ParameterBool::kBang);
                nextPageButton->getParameter().setTooltip("Next page");
                add(nextPageButton);
                
                
                scrollbar = new ScrollBar(this);
                scrollbar->layout.positionMode = 2;
                scrollbar->setZ(-1);
                scrollbar->doIsolateOnActive = false;
                scrollbar->layout.doIncludeInContainerRect = false;
                scrollbar->getParameter().setTooltip("Scroll " + getPath());
                add(scrollbar);
            }
            
            //--------------------------------------------------------------
            Page::~Page() {
                if(layoutManager) delete layoutManager;
            }
            
            //--------------------------------------------------------------
            void Page::onUpdate() {
                Panel::onUpdate();
                
                // set positions and layout
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                // check buttons and stuff
                if(wrapButton) {
                    wrapButton->layout.set(titleButton->width - (s + p) * 3, y, s, s);
                    if(layoutManager) wrapButton->getParameter().trackVariable(&layoutManager->doWrap);
                }
                
                if(prevPageButton) {
                    prevPageButton->layout.set(titleButton->width + p, y, s, s);
                }
                
                if(nextPageButton) {
                    nextPageButton->layout.set(titleButton->width + s + p * 2, y, s, s);
                }
                
                
                if(scrollbar) {
                    if(layoutManager) {// && !layoutManager->doWrap) {
                        // TODO: custom scrollbar layout
                        scrollbar->visible = true;
                        scrollbar->layout.set(0, 0, getConfig().layout.scrollbarWidth, ofGetHeight());
                        float sbheight = scrollbar->layout.height;
                        scrollbar->barThickness = sbheight / layoutManager->getCurRect().height;
                        layoutManager->scrollY = ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, layoutManager->getCurRect().height - sbheight * 0.5);
                    } else {
                        scrollbar->visible = false;
                    }
                }
                
                if(pgui && nextPageButton && nextPageButton->getParameter().value()) {
                    pgui->nextPage();
                }
                
                if(pgui && prevPageButton && prevPageButton->getParameter().value()) {
                    pgui->prevPage();
                }
                
            }
            
        }
    }
}
