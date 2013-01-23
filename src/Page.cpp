
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Page::Page(Gui *pgui, ParameterGroup* p, int index) : Panel(NULL, p) {
                layoutManager = NULL;
                this->pgui = pgui;
                this->index = index;
                
                titleButton->getParameter().setName(ofToString(index+1) + ": " + getName());
                
                wrapButton = new BoolSimpleCircle(this, "w");
                wrapButton->layout.positionMode = 1;
                wrapButton->setZ(2);
                wrapButton->setMode(ParameterBool::kToggle);
                wrapButton->getParameter().setTooltip("Wrap");
                add(wrapButton);
                
                scrollbar = new ScrollBar(this);
                scrollbar->layout.positionMode = 2;
                scrollbar->setZ(-1);
                scrollbar->doIsolateOnActive = false;
                scrollbar->layout.doIncludeInContainerRect = false;
                scrollbar->getParameter().setTooltip("Scroll " + getPath());
                add(scrollbar);
                
                pagesButton = new BoolSimpleBox(this, ">");
                pagesButton->layout.positionMode = 1;
                pagesButton->setZ(2);
                pagesButton->setMode(ParameterBool::kToggle);
                pagesButton->getParameter().setTooltip("more pages...");
                add(pagesButton);
                
                pagesDropdown = new List(this, "pages");
                pagesDropdown->layout.positionMode = 1;
                pagesDropdown->layout.doIncludeInContainerRect = false;
                pagesDropdown->setZ(1e100);
                pagesDropdown->setMode(ParameterNamedIndex::kList);
                pagesButton->getParameter().setTooltip("Show pages");
                add(pagesDropdown);
                
                updatePagesList();
            }
            
            //--------------------------------------------------------------
            Page::~Page() {
                if(layoutManager) delete layoutManager;
            }
            
            //--------------------------------------------------------------
            void Page::updatePagesList() {
                ofLogNotice() << "updatePagesList";
                ParameterNamedIndex *p = dynamic_cast<ParameterNamedIndex*>(&pagesDropdown->getParameter());
                if(p) {
                    p->clearLabels();
                    for(int i=0; i<pgui->getNumPages(); i++) p->addLabel(ofToString(i+1) + ": " + pgui->getPage(i).getName());
                }
            }
            
            
            //--------------------------------------------------------------
            void Page::onUpdate() {
                Panel::onUpdate();
                
                // set positions and layout
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                // check buttons and stuff
                wrapButton->layout.set(titleButton->width - (s + p) * 3, y, s, s);
                if(layoutManager) wrapButton->getParameter().trackVariable(&layoutManager->doWrap);
                
                pagesButton->layout.set(titleButton->width + p, y, s, s);
                
                pagesDropdown->layout.set(pagesButton->layout.getRight(), pagesButton->layout.getBottom(), titleButton->width*1.5, titleButton->height);
                pagesDropdown->visible = pagesDropdown->enabled = pagesButton->getParameter().value();
                
                
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
                
                
                if(pagesButton->getParameter().hasChanged()) {
                    if(pagesButton->getParameter().value()) {
                        updatePagesList();
                    }
                }
                
                if(pagesDropdown->getParameter().hasChanged()) {
                    pgui->setPage((int)pagesDropdown->getParameter());
                }
                
                
                //
                //                if(pgui && prevPageButton && prevPageButton->getParameter().value()) {
                ////                    pgui->prevPage();
                //                }
                
            }
            
        }
    }
}
