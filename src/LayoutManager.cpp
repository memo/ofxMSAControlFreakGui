
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            LayoutManager::LayoutManager() {
                doWrap = false;  // TODO: finish wrapping and scrolling
                targetScrollY = 0;
                scrollY = 0;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::clearParentRect(Container &parent) {
                parent.set(0, 0, 0, 0);
            }
            
            //--------------------------------------------------------------
            void LayoutManager::update() {
                scrollY += (targetScrollY - scrollY) * 0.1;
            }
            
            
            //--------------------------------------------------------------
            void LayoutManager::positionControl(Control &control, ofVec2f &parentScale, int panelDepth) {
                // calculate scale
                ofVec2f curScale = parentScale * control.scale;
                
                int indent = panelDepth * control.getConfig()->layout.indent;
                
                // update dimensions
                control.width = control.layout.width * curScale.x;// ? control.layout.width : control.getConfig()->layout.columnWidth - indent) * curScale.x;
                control.height = control.layout.height * curScale.y;// ? control.layout.height : control.getConfig()->layout.buttonHeight) * curScale.y;
                
                // TODO: think about scales
                switch(control.layout.positionMode) {
                    case LayoutSettings::kRelative: // normal (controls are placed in a free flowing manner, like html, layout.position is offset off calculated)
                    {
                        ofVec2f newHead(_curHead);
                        ofVec2f controlOffset((control.layout.position + control.layout.paddingPre) * curScale);
                        ofVec2f controlPos(newHead + controlOffset);
                        float postHeight = (control.height + control.layout.paddingPost.y + control.getConfig()->layout.padding.y) * curScale.y;
                        //                        if(control.layout.newColumn || (doWrap && controlPos.y + postHeight > maxPos.y)) {
                        //                            newHead.x = control.getParent()->getRight() + control.layout.paddingPost.x + control.getConfig()->layout.padding.x;
                        //                            newHead.y = boundRect.y;
                        //                            controlPos = newHead + controlOffset;
                        //                        }
                        control.setPosition(controlPos);
                        control.x += indent * curScale.x;
                        
                        if(control.layout.doAffectFlow) {
                            _curHead = newHead;
                            _curHead.y += postHeight;
                        }
                        
                    }
                        break;
                        
                    case LayoutSettings::kAbsolute: // layout.position is relative to container
                        control.setPosition(control.getParent() ? (control.getParent()->position + control.layout.position) : control.layout.position);
                        break;
                        
                    case LayoutSettings::kFixed: // layout.position is relative to screen
                        control.setPosition(control.layout.position);
                        break;
                        
                }
            }
            
            //--------------------------------------------------------------
            void LayoutManager::addToRenderer(Control &control) {
                Renderer::instance().add(&control);
            }
            
            //--------------------------------------------------------------
            void LayoutManager::growParent(Control &control) {
                if(control.layout.doIncludeInContainerRect && control.getParent()) {
                    control.getParent()->growToInclude((ofRectangle&)control);
                }
            }
            
            //--------------------------------------------------------------
            void LayoutManager::arrangeControls(Container &container, bool bResetHead) {

                switch(container.layout.positionMode) {
                    case LayoutSettings::kRelative: // normal (controls are placed in a free flowing manner, like html, layout.position is offset off calculated)
////                        if(container.getParent())
////                            _curHead += ofVec2f(container.getParent()->getLeft(), container.getParent()->getBottom());
//                        if(container.getParent())
//                            _curHead += container.getParent()->pLayoutManager->_curHead;
                        if(bResetHead) _curHead.set(container.layout.x, container.layout.y - scrollY);
                        
                        break;
                        
                    case LayoutSettings::kAbsolute: // layout.position is relative to container
                        if(container.getParent())
                            _curHead += ofVec2f(container.getParent()->getLeft(), container.getParent()->getTop());
                        break;

                        
                    case LayoutSettings::kFixed: // layout.position is relative to screen
                        _curHead.set(container.layout.x, container.layout.y);
                        break;
                        
                }

                prepareContainerRecursively(container);
                update();
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareContainerRecursively(Container &container) {
//                ofVec2f maxPos      = getMaxPos();
                
                if(!container.isVisible()) return;
                
                Panel *panel = dynamic_cast<Panel*>(&container);
                
                if(panel) {
                    // how open is this panel
                    float openSpeed = 0.1f;
                    if(panel->titleButton->getParameter().value()) {
                        //                    if(scale.y<0.95) scale.y += (1-scale.y) * openSpeed;
                        if(panel->children->scale.y < 1 - FLT_EPSILON) panel->children->scale.y += openSpeed;
                        else panel->children->scale.y = 1.0f;
                    } else {
                        //                    if(scale.y > 0.05) scale.y += (0-scale.y) * openSpeed;
                        if(panel->children->scale.y > FLT_EPSILON) panel->children->scale.y -= openSpeed;
                        else panel->children->scale.y = 0.0f;
                    }
                }
                
                int panelDepth          = container.getDepth();
                ofVec2f containerScale  = container.getInheritedScale();

                
                positionControl(container, containerScale, panelDepth);
                
                for(int i=0; i<container.getNumControls(); i++) {
                    Control& control = container.get(i);
                    if(control.isVisible()) {
                        Container *c = dynamic_cast<Container*>(&control);
                        if(c) c->arrangeControls(false);//prepareContainerRecursively(*c);
                        else {
                            positionControl(control, containerScale, panelDepth);
                            addToRenderer(control);
                            growParent(control);
                        }
                    }
                }
                addToRenderer(container);
                growParent(container);
                
//                if(container.getRoot()) container.getRoot()->pLayoutManager->_curHead = _curHead;
            }
            
            
            //--------------------------------------------------------------
//            ofVec2f LayoutManager::getMaxPos() {
//                if(doWrap) {
//                    return ofVec2f(boundRect.width ? boundRect.x + boundRect.width : ofGetWidth(), boundRect.height ? boundRect.y + boundRect.height : ofGetHeight());
//                } else {
//                    return ofVec2f(1e100, 1e100);
//                }
//            }
            
            //--------------------------------------------------------------
//            ofVec2f LayoutManager::clampPoint(ofVec2f p) {
//                ofVec2f maxPos(getMaxPos());
//                return ofVec2f(ofClamp(p.x, boundRect.getLeft(), maxPos.x), ofClamp(p.y, boundRect.getTop(), maxPos.y));
//            }
            
            
        }
    }
}