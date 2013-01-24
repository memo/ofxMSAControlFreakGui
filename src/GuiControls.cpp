//
//  _pGuiControls.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 24/01/2013.
//
//

#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            GuiControls::GuiControls(Container *parent) : Container(parent, parent->getName() + "_controls") {
                wrapButton = new BoolSimpleCircle(this, "w");
                wrapButton->layout.positionMode = LayoutSettings::kAbsolute;
                wrapButton->setZ(2);
                wrapButton->setMode(ParameterBool::kToggle);
                wrapButton->getParameter().setTooltip("Wrap");
                addControl(wrapButton);
                
                pagesButton = new BoolSimpleBox(this, ">");
                pagesButton->layout.positionMode = LayoutSettings::kAbsolute;
                pagesButton->setZ(2);
                pagesButton->setMode(ParameterBool::kToggle);
                pagesButton->getParameter().setTooltip("more pages...");
                addControl(pagesButton);
                
                pagesDropdown = new List(this, "pages");
                pagesDropdown->layout.positionMode = LayoutSettings::kAbsolute;
                pagesDropdown->layout.doIncludeInContainerRect = false;
                pagesDropdown->setZ(1e100);
                pagesDropdown->setMode(ParameterNamedIndex::kList);
                pagesButton->getParameter().setTooltip("Show pages");
                addControl(pagesDropdown);
                
                scrollbar = new ScrollBar(this);
                scrollbar->layout.positionMode = LayoutSettings::kFixed;
                scrollbar->setZ(-1);
                scrollbar->doIsolateOnActive = false;
                scrollbar->layout.doIncludeInContainerRect = false;
                scrollbar->getParameter().setTooltip("Scroll " + getPath());
                addControl(scrollbar);
                
                _pgui = dynamic_cast<Gui*>(getRoot());
            }
            
            //--------------------------------------------------------------
            void GuiControls::updatePagesList() {
                ofLogNotice() << "updatePagesList";
                ParameterNamedIndex *p = dynamic_cast<ParameterNamedIndex*>(&pagesDropdown->getParameter());
                if(p && _pgui) {
                    p->clearLabels();
                    for(int i=0; i<_pgui->getNumPages(); i++) p->addLabel(ofToString(i+1) + ": " + _pgui->getPage(i).getName());
                }
            }
            
            
            //--------------------------------------------------------------
            void GuiControls::update() {
                Container::update();
                
                LayoutManager* pLayoutManager = _pgui->pLayoutManager.get();
                
                if(pLayoutManager == NULL) return;
                
                // set positions and layout
                int s = pconfig->layout.buttonHeight * 0.7;
                int y = (pconfig->layout.buttonHeight - s)/2;
                int p = 3;
                
                // check buttons and stuff
                wrapButton->layout.set(pconfig->layout.columnWidth - (s + p) * 3, y, s, s);
                wrapButton->getParameter().trackVariable(&pLayoutManager->doWrap);
                
                pagesButton->layout.set(pconfig->layout.columnWidth + p, y, s, s);
                
                pagesDropdown->layout.set(pagesButton->layout.getRight(), pagesButton->layout.getBottom(), pconfig->layout.columnWidth*1.5, pconfig->layout.buttonHeight);
                pagesDropdown->visible = pagesDropdown->enabled = pagesButton->getParameter().value();
                
                
                if(pagesButton->getParameter().hasChanged()) {
                    if(pagesButton->getParameter().value()) {
                        updatePagesList();
                    }
                }
                
                if(pagesDropdown->getParameter().hasChanged()) {
                    if(_pgui) {
                        _pgui->setPage((int)pagesDropdown->getParameter());
                    }
                }
                
                // TODO: custom scrollbar layout
                scrollbar->visible = true;
                scrollbar->layout.set(0, 0, pconfig->layout.scrollbarWidth, ofGetHeight());
                float sbheight = scrollbar->layout.height;
                scrollbar->barThickness = sbheight / pLayoutManager->getCurRect().height;
                pLayoutManager->scrollY = ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, pLayoutManager->getCurRect().height - sbheight * 0.5);
                
            }
            
            
            //
            //                if(_pgui && prevPageButton && prevPageButton->getParameter().value()) {
            ////                    _pgui->prevPage();
            //                }
            
        }
        
        
    }
    
}
