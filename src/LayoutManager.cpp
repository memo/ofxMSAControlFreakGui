
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            LayoutManager::LayoutManager() {
                doWrap = false;  // TODO: finish wrapping and scrolling
                scrollY = 0;
                _scrollY = 0;
            }
            
            
            
            //--------------------------------------------------------------
            void LayoutManager::update(Container &root) {
                _curHead.set(boundRect.position); // start in top left
                _curRect.set(0, 0, 0, 0);
//                panelDepth = 0;
                
                prepareContainer(root);
                _scrollY += (scrollY - _scrollY) * 0.1;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareControl(Control &control, Config &config, ofVec2f &containerScale, int panelDepth, ofVec2f &maxPos) {
                
                control.setConfig(&config);
                
                // calculate scale
                ofVec2f curScale = containerScale * control.scale;
                
                int indent = panelDepth * config.layout.indent;
                
                // update dimensions
                control.width = (control.layout.width ? control.layout.width : config.layout.columnWidth - indent) * curScale.x;
                control.height = (control.layout.height ? control.layout.height : config.layout.buttonHeight) * curScale.y;
                
                // TODO: think about scales
                switch(control.layout.positionMode) {
                    case 0: // relative (normal)
                    {
                        ofVec2f newHead(_curHead);
                        ofVec2f controlOffset((control.layout.position + control.layout.paddingPre) * curScale);
                        ofVec2f controlPos(newHead + controlOffset);
                        float postHeight = (control.height + control.layout.paddingPost.y + config.layout.padding.y) * curScale.y;
                        if(control.layout.newColumn || (doWrap && controlPos.y + postHeight > maxPos.y)) {
                            newHead.x = _curRect.getRight() + control.layout.paddingPost.x + config.layout.padding.x;
                            newHead.y = boundRect.y;
                            controlPos = newHead + controlOffset;
                        }
                        control.setPosition(controlPos);
                        control.x += indent * curScale.x;
                        control.y -= _scrollY;
                        
                        if(control.layout.doAffectFlow) {
                            _curHead = newHead;
                            _curHead.y += postHeight;
                        }
                        
                    }
                        break;
                        
                    case 1: // absolute (relative to container)
                        control.setPosition(control.getParent() ? (control.getParent()->position + control.layout.position) : control.layout.position);
                        break;
                        
                    case 2: // fixed (relative to screen)
                        control.setPosition(control.layout.position);
                        break;
                        
                }
                
                //                        if(control.layout.positionMode) {
                // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
                //                            if(control.newColumn || (doWrap && _curHead.y + control.height > maxPos.y)) {
                //                                _curHead.x = _curRect.x + _curRect.width + config.layout.padding.x;
                //                                _curHead.y = boundRect.y;
                //                            }
                
                //                            _curHead += control.layout.position * curScale;
                
                //                            control.setPosition(_curHead.x + indent, _curHead.y - _scrollY);
                //                            _curHead.y += control.height + config.layout.padding.y * curScale.y;
                //                        } else {
                //                            control.setPosition(container.position + control.layout.position);
                //                        }
                
                //                        printf("setting position: %s %f %f %s %f %f\n", control.getParameter().getPath().c_str(), control.x, control.y, container.getParameter().getPath().c_str(), container.x, container.y);
                
                Renderer::instance().add(&control);
                if(control.layout.doIncludeInContainerRect) {
                    _curRect.growToInclude((ofRectangle&)control);
                }
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareContainer(Container &container) {
                Config &config      = container.getRoot()->getConfig();
                ofVec2f maxPos      = getMaxPos();
                
//                // TODO: hack?
//                // see if this is a panel children container, if so indent
//                if(container.getParameter().getName().find("_children") != string::npos) {
//                    panelDepth++;
//                }
                
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
                    prepareControl(container, config, containerScale, panelDepth, maxPos);
                    for(int i=0; i<container.size(); i++) {
                        Control& control = container.get(i);
                        
                        
                        Container *c = dynamic_cast<Container*>(&control);
                        if(c) prepareContainer(*c);
                        else prepareControl(control, config, containerScale, panelDepth, maxPos);

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