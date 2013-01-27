
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
            void LayoutManager::begin(Container &root) {
                _curHead.set(boundRect.position); // start in top left
                //                proot = &root;
                root.set(0, 0, 0, 0);
            }
            
            //--------------------------------------------------------------
            void LayoutManager::end() {
                _scrollY += (scrollY - _scrollY) * 0.1;
            }
            
            
            //--------------------------------------------------------------
            void LayoutManager::prepareControl(Control &control, ofVec2f &containerScale, int panelDepth, ofVec2f &maxPos) {
                
                // calculate scale
                ofVec2f curScale = containerScale * control.scale;
                
                int indent = panelDepth * control.pconfig->layout.indent;
                
                // update dimensions
                control.width = (control.layout.width ? control.layout.width : control.pconfig->layout.columnWidth - indent) * curScale.x;
                control.height = (control.layout.height ? control.layout.height : control.pconfig->layout.buttonHeight) * curScale.y;
                
                // TODO: think about scales
                switch(control.layout.positionMode) {
                    case 0: // relative (normal)
                    {
                        ofVec2f newHead(_curHead);
                        ofVec2f controlOffset((control.layout.position + control.layout.paddingPre) * curScale);
                        ofVec2f controlPos(newHead + controlOffset);
                        float postHeight = (control.height + control.layout.paddingPost.y + control.pconfig->layout.padding.y) * curScale.y;
                        if(control.layout.newColumn || (doWrap && controlPos.y + postHeight > maxPos.y)) {
                            newHead.x = control.getParent()->getRight() + control.layout.paddingPost.x + control.pconfig->layout.padding.x;
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
                
                Renderer::instance().add(&control);
                if(control.layout.doIncludeInContainerRect && control.getParent()) {
                    control.getParent()->growToInclude((ofRectangle&)control);
                }
            }
            
            //--------------------------------------------------------------
            void LayoutManager::growParent(Control &control) {
                //                if(control.visible && control.layout.doIncludeInContainerRect && control.getParent()) {
                //                    control.getParent()->growToInclude((ofRectangle&)control);
                //                    Container *c = dynamic_cast<Container*>(&control);
                //
                //                }
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareContainer(Container &container) {
                ofVec2f maxPos      = getMaxPos();
                
                //                // TODO: hack?
                //                // see if this is a panel children container, if so indent
                //                if(container.getParameter().getName().find("_children") != string::npos) {
                //                    panelDepth++;
                //                }
                
                if(container.visible == false || container.scale.x < FLT_EPSILON || container.scale.y < FLT_EPSILON) return;
                
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
                
                int panelDepth          = container.getDepth();
                ofVec2f containerScale  = container.getInheritedScale();
                
                //                    if(container.getParent()) {
                //                        container.getParent()->width = 0;
                //                        container.getParent()->height = 0;
                //                    }
                
                prepareControl(container, containerScale, panelDepth, maxPos);
                
                container.width = 0;
                container.height = 0;
                
                for(int i=0; i<container.getNumControls(); i++) {
                    Control& control = container.get(i);
                    if(control.visible) {
                        Container *c = dynamic_cast<Container*>(&control);
                        if(c) prepareContainer(*c);
                        else prepareControl(control, containerScale, panelDepth, maxPos);
                    }
                }
                
                if(container.getParent()) container.getParent()->growToInclude(container.getRight(), container.getBottom());
                
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