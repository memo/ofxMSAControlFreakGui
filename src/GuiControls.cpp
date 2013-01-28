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
                layout.positionMode = LayoutSettings::kFixed;
                layout.doIncludeInContainerRect = false;

//                wrapButton = new BoolSimpleCircle(this, "w");
//                wrapButton->layout.positionMode = LayoutSettings::kAbsolute;
//                wrapButton->setZ(2);
//                wrapButton->setMode(ParameterBool::kToggle);
//                wrapButton->getParameter().setTooltip("Wrap");
//                addControl(wrapButton);
                
                addControl(pagesButton = new BoolSimpleBox(this, ">"));
                pagesButton->layout.positionMode = LayoutSettings::kFixed;
                pagesButton->setMode(ParameterBool::kToggle);
                pagesButton->getParameter().setTooltip("more pages...");
                
                addControl(pagesDropdown = new OptionsBoxes(this, "pages"));
                pagesDropdown->layout.positionMode = LayoutSettings::kFixed;
                pagesDropdown->getParameter().setTooltip("Show pages");
                
                addControl(scrollbar = new ScrollBar(this));
                scrollbar->layout.positionMode = LayoutSettings::kFixed;
                scrollbar->doIsolateOnActive = false;
                scrollbar->getParameter().setTooltip("Scroll " + getPath());
                
                
                _pControlOptions = ControlOptionsPtr(new ControlOptions(this));
                addControl(_pControlOptions.get());
            }
            
            //--------------------------------------------------------------
            void GuiControls::updatePagesList() {
                ofLogNotice() << "updatePagesList";
                ParameterNamedIndex *p = dynamic_cast<ParameterNamedIndex*>(&pagesDropdown->getParameter());
                if(p) {
                    p->clearLabels();
                    for(int i=0; i<getRoot()->getNumPages(); i++) p->addLabel(ofToString(i+1) + ": " + getRoot()->getPage(i+1).getName());
                }
            }
            
            
            //--------------------------------------------------------------
            void GuiControls::update() {
                Container::update();
                
//                LayoutManager* pLayoutManager = getRoot()->pLayoutManager.get();
                
                if(pLayoutManager == NULL) return;
                
                // set positions and layout
                int s = getConfig()->layout.buttonHeight * 0.7;
                int y = (getConfig()->layout.buttonHeight - s)/2;
                int p = 3;
                
                // check buttons and stuff
//                wrapButton->layout.set(getConfig()->layout.columnWidth - (s + p) * 3, y, s, s);
//                wrapButton->getParameter().trackVariable(&pLayoutManager->doWrap);
                
                // TODO: custom scrollbar layout
                scrollbar->visible = true;
                scrollbar->layout.set(0, 0, getConfig()->layout.scrollbarWidth, ofGetHeight());
                float sbheight = scrollbar->layout.height;
                int contentHeight = getRoot()->getCurrentPage().height;
                scrollbar->barThickness = sbheight / contentHeight;
                pLayoutManager->targetScrollY = scrollbar->barThickness < 1 ? ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, contentHeight - sbheight * 0.5) : 1;
                
                
                pagesButton->layout.set(getRoot()->getCurrentPage().getRight(), 0, getConfig()->layout.buttonHeight, getConfig()->layout.buttonHeight);
                pagesDropdown->layout.set(pagesButton->layout.getRight(), pagesButton->layout.getTop(), getConfig()->layout.columnWidth, getConfig()->layout.buttonHeight);
                pagesDropdown->visible = pagesDropdown->enabled = pagesButton->getParameter().value();
                
                if(pagesButton->getParameter().hasChanged()) {
                    if(pagesButton->getParameter().value()) {
                        updatePagesList();
                    }
                }
                
                if(pagesDropdown->getParameter().hasChanged()) {
                    pagesButton->getParameter() = false;
                    getRoot()->setPage((int)pagesDropdown->getParameter()+1);
                }
            }
            
            //--------------------------------------------------------------
            void GuiControls::draw() {
//                ofSetColor(255, 0 ,0);
//                ofNoFill();
//                ofRect(x, y, width, height);
            }

        }
        
        
    }
    
}
