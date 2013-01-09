
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
            void LayoutManager::update(Container &root) {
                curHead.set(boundRect.position); // start in top left
                curRect.set(0, 0, 0, 0);
                
                prepareForDraw(root);
                _scrollY += (scrollY - _scrollY) * 0.1;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareForDraw(Container &container) {

                Config &config      = container.getConfig();
                ofVec2f maxPos      = getMaxPos();
                
                Panel *panel = dynamic_cast<Panel*>(&container);
                
                if(panel) {
                    // how open is this panel
                    float openSpeed = 0.1f;
                    if(panel->titleButton->getParameter().value()) {
                        //                    if(scale.y<0.95) scale.y += (1-scale.y) * openSpeed;
                        if(panel->children->scale.y < 1) panel->children->scale.y += openSpeed;
                        else panel->children->scale.y = 1.0f;
                    } else {
                        //                    if(scale.y > 0.05) scale.y += (0-scale.y) * openSpeed;
                        if(panel->children->scale.y > 0) panel->children->scale.y -= openSpeed;
                        else panel->children->scale.y = 0.0f;
                    }
                }
                
                int panelDepth          = container.getDepth();// * config.layout.indent;
                ofVec2f containerScale  = container.getInheritedScale();//i ? getInheritedScale().y : getParentHeightScale();
                
                // TODO: parent isn't being processed, thats why root doesn't have it.
                if(containerScale.y > 0) {
                    for(int i=0; i<container.getNumControls(); i++) {
                        Control& control = *container.getControl(i);
                        
                        Container *c = dynamic_cast<Container*>(&control);
                        
                        control.setConfig(&config);
                        
                        // calculate scale
                        ofVec2f curScale = containerScale * control.scale;
                        
                        int indent = panelDepth * config.layout.indent * curScale.x;
                        
                        // update dimensions
                        control.width = (control.layout.width ? control.layout.width : config.layout.columnWidth) * curScale.x;
                        control.height = (control.layout.height ? control.layout.height : config.layout.buttonHeight) * curScale.y;
                        control.width -= indent;
                        
                        // TODO: think about scales
                        switch(control.layout.positionMode) {
                            case 0: // relative (normal)
                            {
                                ofVec2f newHead(curHead);
                                ofVec2f controlOffset(control.layout.position + control.layout.paddingPre);
                                ofVec2f controlPos(newHead + controlOffset);
                                float postHeight = control.height + control.layout.paddingPost.y + config.layout.padding.y;
                                if(control.layout.newColumn || (doWrap && controlPos.y + postHeight > maxPos.y)) {
                                    newHead.x = curRect.getRight() + control.layout.paddingPost.x + config.layout.padding.x;
                                    newHead.y = boundRect.y;
                                    controlPos = newHead + controlOffset;
                                }
                                control.setPosition(controlPos);
                                control.x += indent;
                                control.y -= _scrollY;
                                
                                if(control.layout.doAffectFlow) {
                                    curHead = newHead;
                                    curHead.y += postHeight;
                                }
                                
                            }
                                break;
                                
                            case 1: // absolute (relative to container)
                                control.setPosition(container.position + control.layout.position);
                                break;
                                
                            case 2: // fixed (relative to screen)
                                control.setPosition(control.layout.position);
                                break;
                                
                        }
                        
//                        if(control.layout.positionMode) {
                            // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
//                            if(control.newColumn || (doWrap && curHead.y + control.height > maxPos.y)) {
//                                curHead.x = curRect.x + curRect.width + config.layout.padding.x;
//                                curHead.y = boundRect.y;
//                            }
                            
//                            curHead += control.layout.position * curScale;
                        
//                            control.setPosition(curHead.x + indent, curHead.y - _scrollY);
//                            curHead.y += control.height + config.layout.padding.y * curScale.y;
//                        } else {
//                            control.setPosition(container.position + control.layout.position);
//                        }
                        
                        //                        printf("setting position: %s %f %f %s %f %f\n", control.getParameter().getPath().c_str(), control.x, control.y, container.getParameter().getPath().c_str(), container.x, container.y);
                        
                        Renderer::instance().addControl(&control);
                        if(control.layout.doIncludeInContainerRect) {
                            curRect.growToInclude((ofRectangle&)control);
                        }
                        
                        if(c) prepareForDraw(*c);
                    }
                    
                }
                
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