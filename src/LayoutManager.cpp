
#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            LayoutManager::LayoutManager() {
                doWrap = true;  // TODO: finish wrapping and scrolling
                scrollY = 0;
                _scrollY = 0;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareForDraw(Container &container) {

                Config &config      = container.getConfig();
                ofVec2f maxPos      = getMaxPos();
                
                Panel *panel = dynamic_cast<Panel*>(&container);
                
                if(container.doAutoLayout) {
                    curPos              = clampPoint(curPos);
                    //                    container.position  = curPos; // TODO, check this
                } else {
                    //                    curPos = container.position;
                }
                
                
                if(panel) {
                    // how open is this panel
                    float openSpeed = 0.1f;
                    //                    Parameter &titleBool = panel->titleButton->getParameter();
                    //                    if(titleBool.value() != panel->isOpen) panel->showPanel(titleBool.value(), false);
                    
                    if(panel->titleButton->getParameter().value()) {
                        //                    if(scale.y<0.95) scale.y += (1-scale.y) * openSpeed;
                        if(panel->children->scale.y < 1) panel->children->scale.y += openSpeed;
                        else panel->children->scale.y = 1.0f;
                    } else {
                        //                    if(scale.y > 0.05) scale.y += (0-scale.y) * openSpeed;
                        if(panel->children->scale.y > 0) panel->children->scale.y -= openSpeed;
                        else panel->children->scale.y = 0.0f;
                    }
                    
//                    curPos.y += config.layout.padding.y * 5;//config.layout.buttonHeight * containerScale.y/2;
                    
                    // if we are drawing this Panel inside another Panel, use auto-layout parameters of that
                    //                if(panel->getParent()) layoutManager = panel->getParent()->layoutManager;
                    
                    //                    panel->titleButton->z = -10000;
                }
                
                int panelDepth          = container.getDepth();// * config.layout.indent;
                ofVec2f containerScale  = container.getInheritedScale();//i ? getInheritedScale().y : getParentHeightScale();
                
                // TODO: parent isn't being processed, thats why root doesn't have it.
                if(containerScale.y > 0) {
                    for(int i=0; i<container.getNumControls(); i++) {
                        Control& control = *container.getControl(i);
                        Container *c = dynamic_cast<Container*>(&control);
                        
                        control.setConfig(&config);
                        
                        ofVec2f curScale = containerScale * control.scale;
                        
                        int indent = panelDepth * config.layout.indent * curScale.x;
                        
                        control.width = control.localRect.width ? control.localRect.width : config.layout.columnWidth - indent;
                        control.height = control.localRect.height ? control.localRect.height : config.layout.buttonHeight;
                        
                        control.width *= curScale.x;
                        control.height *= curScale.y;
                        
                        if(control.doAutoLayout) {
                            // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
                            if(control.newColumn || (doWrap && curPos.y + control.height > maxPos.y)) {
                                curPos.x = rect.x + rect.width + config.layout.padding.x;
                                curPos.y = boundRect.y;
                            }
                            
                            curPos += control.localRect.position * curScale;
                            
                            // add some padding at before group
                            control.setPosition(curPos.x + indent, curPos.y - _scrollY);
                            curPos.y += control.height + config.layout.padding.y * curScale.y;
                        } else {
                            control.setPosition(container.position + control.localRect.position);
                        }
                        
                        //                        printf("setting position: %s %f %f %s %f %f\n", control.getParameter().getPath().c_str(), control.x, control.y, container.getParameter().getPath().c_str(), container.x, container.y);
                        
                        Renderer::instance().addControl(&control);
                        if(control.doIncludeInContainerRect) rect.growToInclude((ofRectangle&)control);
                        
                        if(c) prepareForDraw(*c);
                    }
                    
                    // add some padding at end of group
//                    curPos.y += config.layout.buttonHeight * containerScale.y/2;
                }
                
            }
            
            
            //--------------------------------------------------------------
            void LayoutManager::update() {
                _scrollY += (scrollY - _scrollY) * 0.1;
            }
            
            //--------------------------------------------------------------
            ofVec2f LayoutManager::getMaxPos() {
                if(doWrap) {
                    return ofVec2f(boundRect.width ? boundRect.x + boundRect.width : ofGetWidth(), boundRect.height ? boundRect.y + boundRect.height : ofGetHeight());
                } else {
                    return ofVec2f(1e100, 1e100);
                }
            }
            
            //--------------------------------------------------------------
            ofVec2f LayoutManager::clampPoint(ofVec2f p) {
                ofVec2f maxPos(getMaxPos());
                return ofVec2f(ofClamp(p.x, boundRect.getLeft(), maxPos.x), ofClamp(p.y, boundRect.getTop(), maxPos.y));
            }
            
            
        }
    }
}