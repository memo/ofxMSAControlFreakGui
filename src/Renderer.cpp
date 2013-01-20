
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Renderer *Renderer::renderer = NULL;
            
            //--------------------------------------------------------------
            Renderer::Renderer() {
                _pconfig = NULL;
//                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            Renderer& Renderer::instance() {
                if(renderer == NULL) renderer = new Renderer;
                return *renderer;
            }
            
            //--------------------------------------------------------------
            Renderer::~Renderer() {
                if(renderer) delete renderer;
            }

            
            //--------------------------------------------------------------
            void Renderer::add(Control *c) {
//                ofLogVerbose() << "Renderer::add: " << c->getPath() << " " << c->x << " " << c->y << " " << c->width  << " " << c->height;
                controls.push_back(c);
            }
            
            //--------------------------------------------------------------
            void Renderer::clearControls() {
                controls.clear();
            }

            //--------------------------------------------------------------
            struct PointerCompare {
                // TODO: cache this?
                bool operator()(const Control* l, const Control* r) {
                    return l->getInheritedZ() < r->getInheritedZ();
                }
            };
            
            //--------------------------------------------------------------
            void Renderer::draw(Config &config) {
                this->_pconfig = &config;

                // TODO: fix sorting, if z-order is same, undefined behaviour
                sort(controls.begin(), controls.end(), PointerCompare());
                
                ofPushStyle();
//                ofLogNotice() << "Renderer::draw :" << controls.size();
                for(int i=0; i<controls.size(); i++) {
                    Control& control = *controls[i];
                    if(control.intersects(ofGetWindowRect())) control.draw();
//                    ofLogNotice() << "   " << control.getParameter().getPath() << " " << control.getParameter().getTypeName();
                }
//                ofLogNotice() << "/Renderer::draw \n";
                
                drawToolTip();
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Renderer::setToolTip(string s, int x, int y) {
                tooltip.x = x < 0 ? ofGetMouseX() : x;
                tooltip.y = y < 0 ? ofGetMouseY() : y;
                tooltip.s = s;
            }
            
            //--------------------------------------------------------------
            void Renderer::drawToolTip() {
//                printf("drawTooltip: %s\n", tooltip.s.c_str());
                if(tooltip.s.empty() || !_pconfig) return;
                
                int x = tooltip.x + _pconfig->tooltip.offset.x;
                int y = tooltip.y + _pconfig->tooltip.offset.y;
                
                ofPushStyle();
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofRectangle r = _pconfig->font.getStringBoundingBox(tooltip.s, x, y);
                r.x -= _pconfig->tooltip.padding.x;
                r.y -= _pconfig->tooltip.padding.y;
                r.width += _pconfig->tooltip.padding.width;
                r.height += _pconfig->tooltip.padding.height;
                
                // make sure tooltip doesn't go offscreen
                ofVec2f diff;
                if(r.getLeft() < 0) { diff.x = -r.x; r.x = 0; }
                else if(r.getRight() > ofGetWidth()) { diff.x = ofGetWidth() - r.getRight(); r.x = ofGetWidth() - r.width; }
                
                if(r.getTop() < 0) { diff.y = - r.y; r.y = 0; }
                else if(r.getBottom() > ofGetHeight()) { diff.y = ofGetHeight() - r.y; r.y = ofGetHeight() - r.height; }
                
                x += diff.x;
                y += diff.y;
                
                
                ofSetLineWidth(1);
                ofSetColor(_pconfig->tooltip.bgColor);
                ofFill();
                ofRect(r);
                
                ofSetColor(_pconfig->tooltip.borderColor);
                ofNoFill();
                ofRect(r);
                
                ofSetColor(_pconfig->tooltip.textColor);
                _pconfig->drawString(tooltip.s, x, y);
                
                ofPopStyle();
                tooltip.s = "";
            }
            
            
//            //--------------------------------------------------------------
//            void Renderer::update() {
//                if(controls.empty()) {
//                    _pactiveControl = NULL;
//                    return;
//                }
//                
//                _pactiveControl = controls[0]->getRoot()->getActiveControl();
//                
//                for(int i=controls.size()-1; i>=0; --i) controls[i]->update();
//            }
//            
//            
//            //--------------------------------------------------------------
//            void Renderer::mouseMoved(ofMouseEventArgs &e) {
//                if(controls.empty()) return;
//                
//                if(_pactiveControl)
//                    _pactiveControl->_mouseMoved(e);
//                else {
//                    for(int i=controls.size()-1; i>=0; --i) {
//                        controls[i]->_mouseMoved(e);
//                        if(controls[i]->isMouseOver()) return;    // don't propogate event if this control processed it
//                    }
//                }
//            }
// 
//            
//            //--------------------------------------------------------------
//            void Renderer::mousePressed(ofMouseEventArgs &e) {
//                if(controls.empty()) return;
//
//                if(_pactiveControl)
//                    _pactiveControl->_mousePressed(e);
//                else {
//                   for(int i=controls.size()-1; i>=0; --i) {
//                        controls[i]->_mousePressed(e);
//                        if(controls[i]->isMouseOver()) {
//                            controls[i]->getRoot()->setActiveControl(controls[i]);
////                            return;    // don't propogate event if this control processed it
//                        }
//                    }
//                }
//            }
//            
//            //--------------------------------------------------------------
//            void Renderer::mouseDragged(ofMouseEventArgs &e) {
//                if(controls.empty()) return;
//
//                if(_pactiveControl)
//                    _pactiveControl->_mouseDragged(e);
//                else {
//                    for(int i=controls.size()-1; i>=0; --i) {
//                        controls[i]->_mouseDragged(e);
////                        if(controls[i]->isMouseOver()) return;    // don't propogate event if this control processed it
//                    }
//                }
//            }
//            
//            //--------------------------------------------------------------
//            void Renderer::mouseReleased(ofMouseEventArgs &e) {
//                if(controls.empty()) return;
//
//                if(_pactiveControl)
//                    _pactiveControl->_mouseReleased(e);
//                else {
//                    for(int i=controls.size()-1; i>=0; --i) controls[i]->_mouseReleased(e);
//                }
//                
//                controls[0]->getRoot()->releaseActiveControl();
//            }
//            
//            //--------------------------------------------------------------
//            void Renderer::keyPressed(ofKeyEventArgs &e) {
//                if(controls.empty()) return;
//
//                bool keyUp		= e.key == OF_KEY_UP;
//                bool keyDown	= e.key == OF_KEY_DOWN;
//                bool keyLeft	= e.key == OF_KEY_LEFT;
//                bool keyRight	= e.key == OF_KEY_RIGHT;
//                bool keyEnter	= e.key == OF_KEY_RETURN;
//                
//                for(int i=controls.size()-1; i>=0; --i) {
//                    Control *c = controls[i];
//                    if(c->isMouseOver()) {
//                        if(keyUp)		c->onKeyUp();
//                        if(keyDown)		c->onKeyDown();
//                        if(keyLeft)		c->onKeyLeft();
//                        if(keyRight)	c->onKeyRight();
//                        if(keyEnter)	c->onKeyEnter();
//                        c->_keyPressed(e);
//                    }
//                }
//            }
//            
//            //--------------------------------------------------------------
//            void Renderer::keyReleased(ofKeyEventArgs &e) {
//                if(controls.empty()) return;
//
//                for(int i=controls.size()-1; i>=0; --i) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
//            }
//            
//            


        }
    }
}