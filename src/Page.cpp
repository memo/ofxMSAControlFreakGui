
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Page::Page(Container *parent, ParameterGroup* p, int index) : Panel(parent, p) {
                this->index = index;
//                this->pgui = gui;
                
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
            void Page::updatePagesList() {
                ofLogNotice() << "updatePagesList";
                ParameterNamedIndex *p = dynamic_cast<ParameterNamedIndex*>(&pagesDropdown->getParameter());
                if(p) {
//                TODO: move this to gui
//                    TabContainer *tabs = dynamic_cast<TabContainer*>(getParent());
//                    if(tabs) {
//                       p->clearLabels();
//                        for(int i=0; i<tabs->getNumTabs(); i++) p->addLabel(ofToString(i+1) + ": " + tabs->getTab(i).getName());
//                    }
                }
            }
            
            
            //--------------------------------------------------------------
            void Page::update() {
                Panel::update();
                
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
                    scrollbar->layout.set(0, 0, pconfig->layout.scrollbarWidth, ofGetHeight());
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
//                TODO: move this to gui
//                    TabContainer *tabs = dynamic_cast<TabContainer*>(getParent());
//                    if(tabs) {
//                        tabs->setTab((int)pagesDropdown->getParameter());
//                    }
                }
                
                
                //
                //                if(pgui && prevPageButton && prevPageButton->getParameter().value()) {
                ////                    pgui->prevPage();
                //                }
                
            }
            
        }
    }
}
