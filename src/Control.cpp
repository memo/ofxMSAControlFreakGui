
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            Control::Control(Container *parent, Parameter* parameter, bool bOwnsParameter) {
                setParent(parent);
                setParameter(parameter, bOwnsParameter);

                // by default, use same pconfig as parent
                if(parent) pconfig = parent->pconfig;
                
                setZ(0);
                visible = true;
                doIsolateOnActive = true;
                keyboardShortcut = 0;
                //                setKeyboardShortcut(0);
                scale.set(1, 1);
                layout.set(0, 0, 0, 0);
                
                _alpha = 1;
                _depth = 0;
                
//                setup();
                
                // we don't want auto events (they will be controlled via the parent panels)
                disableAllEvents();
            }
            
            //--------------------------------------------------------------
            Control::~Control() {
                if(_bOwnsParameter && _pparameter) delete _pparameter;
            }
            
            
            //--------------------------------------------------------------
            Container* Control::getParent() const {
                return _pparent;
            }
            
            //--------------------------------------------------------------
            Container* Control::getRoot(bool bUpdate) {
                if(bUpdate) _proot = ( getParent() ? getParent()->getRoot(true) : dynamic_cast<Container*>(this) );
                return _proot;
                //                return getParent() ? getParent()->_proot : _proot;
            }
            
            //--------------------------------------------------------------
            int Control::getDepth(bool bUpdate) {
                if(bUpdate) {
                    if(getParent()) {
                        // TODO: hack?
                        // see if this is a panel children container, if so indent
                        _depth = getParent()->getDepth(true) + (getParent()->getParameter().getName().find("_children") != string::npos ? 0 : 1);
                    } else _depth = 0;
                }
                return _depth;
            }
            
            //--------------------------------------------------------------
            bool Control::isActive() {
                return getRoot()->getActiveControl() && getRoot()->getActiveControl() == this;
            }
            
            //--------------------------------------------------------------
            bool Control::getParentActive() {
                return getParent() ? isActive() || getParent()->isActive() || getParent()->getParentActive() : isActive();
            }
            
            //--------------------------------------------------------------
            ofVec2f Control::getScale() {
                return scale;
            }
            
            //--------------------------------------------------------------
            ofVec2f Control::getInheritedScale() {
                return getParent() ? scale * getParent()->getInheritedScale() : scale;
            }
            
            //--------------------------------------------------------------
            ofVec2f Control::getParentScale() {
                return getParent() ? getParent()->getInheritedScale() : ofVec2f(1, 1);
            }
            
            
            //--------------------------------------------------------------
            void Control::setZ(int z) {
                _z.push(z);
            }
            
            //--------------------------------------------------------------
            int Control::getZ() const {
                return _z.top();
            }
            
            //--------------------------------------------------------------
            int Control::popZ() {
                _z.pop();
                return getZ();
            }
            
            //--------------------------------------------------------------
            int Control::getInheritedZ() const {
                return getParent() ? getZ() + getParent()->getInheritedZ() * 1000 : getZ();
            }
            
            
            //--------------------------------------------------------------
            string Control::getName() {
                return getParameter().getName();
            }
            
            //--------------------------------------------------------------
            string Control::getPath() {
                return getParameter().getPath();
            }
            
            //--------------------------------------------------------------
            Parameter& Control::getParameter() {
                return *_pparameter;
            }
            
            //--------------------------------------------------------------
            int Control::getState() {
                if(isMousePressed()) return 2;
                else if(isMouseOver()) return 1;
                else return 0;
            }
            
            //--------------------------------------------------------------
            ofColor Control::setColor(ofColor c) {
                c.a *= _alpha;
                ofSetColor(c);
                return c;
            }
            
            //--------------------------------------------------------------
            ofColor Control::setColor(ofColor *c) {
                ofColor cc = c[getState()];
                return setColor(c[getState()]);
            }
            
            
            //--------------------------------------------------------------
            ofColor Control::setBGColor() {
                return setColor(pconfig->colors.bg);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setTextColor() {
                return setColor(pconfig->colors.text);
            }
            
            
            //--------------------------------------------------------------
            ofColor Control::setSliderColor(bool b) {
                if(b) return setColor(pconfig->colors.slider.full);
                else return setColor(pconfig->colors.slider.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setToggleColor(bool b) {
                if(b) return setColor(pconfig->colors.toggle.full);
                else return setColor(pconfig->colors.toggle.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setBorderColor() {
                return setColor(pconfig->colors.border);
            }
            
            //--------------------------------------------------------------
            bool Control::doTooltip(int millis) {
                return isMouseOver() && getStateChangeMillis() > (millis < 0 ? 250 : millis);
            }
            
            //--------------------------------------------------------------
            void Control::setTooltip(string s) {
                // if s is empty, use string from parameter
                if(s.empty()) s = getParameter().getTooltip();
                if(doTooltip() && !s.empty()) {
                    Renderer::instance().setToolTip(this, getParameter().getTooltip());
                }
            }
            
            
            //--------------------------------------------------------------
            void Control::drawText(int x, int y, string s, ofColor *c) {
                s = s.empty() ? getName() : s;
                setColor(c ? c : pconfig->colors.text);
                pconfig->drawString(s, x, y);
            }
            
            //--------------------------------------------------------------
            void Control::drawTextCentered(string s, ofColor *c) {
                s = s.empty() ? getName() : s;
                ofRectangle r = getTextRect(0, 0, s);
                drawText(-r.x + width/2 - r.width/2, -r.y + height/2 - r.height/2, s, c);
                
            }
            
            //--------------------------------------------------------------
            ofRectangle Control::getTextRect(int x, int y, string s) {
                s = s.empty() ? getName() : s;
                return pconfig->font.getStringBoundingBox(s, x, y);
            }
            
            
            //--------------------------------------------------------------
            //            Control &Control::setKeyboardShortcut(char c) {
            //                keyboardShortcut = c;
            //                if(c) {
            //                    //	printf("ofxMSAControlFreakGui/src/Control::setKeyboardShortcut %s %c\n", name.c_str(), c);
            //                    //                    name = origName + " (" + c + ")";
            //                } else {
            //                    //                    name = origName;
            //                }
            //                return *this;
            //            }
            
            //--------------------------------------------------------------
            void Control::drawBorder(ofColor *c) {
                ofNoFill();
                setColor(c ? c : pconfig->colors.border);
                glLineWidth(1.0);
                ofRect(0, 0, width, height);
            }
            
            //--------------------------------------------------------------
            void Control::update() {
                if(_bOwnsParameter) getParameter().update();
                onUpdate();
            }
            
            //--------------------------------------------------------------
            void Control::transformAndDraw() {
                if(!visible) return;
                
                bool bTimeToChange = getStateChangeMillis() > pconfig->colors.fade.delayMillis;
                bool bAControlIsActive = getRoot()->getActiveControl() && getRoot()->getActiveControl()->doIsolateOnActive;
                bool bThisIsActive = getParentActive();
                
                float targetAlpha = bTimeToChange && bAControlIsActive && !bThisIsActive ? pconfig->colors.fade.alpha : 1.0f;
                float diff = (targetAlpha - _alpha);
                _alpha += diff * pconfig->colors.fade.speed;
                if(fabsf(diff) < 0.05) _alpha = targetAlpha;
                
                if(_alpha < 0.001) return;
                
                
                setTooltip();
                
                // make sure all controls land on perfect pixels
                ofRectangle::set(floor(x), floor(y), floor(width), floor(height));
                
                
                ofPushStyle(); {
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    ofEnableAlphaBlending();
                    ofPushMatrix(); {
                        ofTranslate(x, y);
                        ofVec2f s(getInheritedScale());
                        ofScale(s.x, s.y, 1);
                        
                        ofPushMatrix(); {
                            draw();
                            //                drawBorder();
                            //                drawTextCentered(getParameter().getName() + " " + ofToString(getInheritedZ()));
                        } ofPopMatrix();
                        
                    } ofPopMatrix();
                } ofPopStyle();
            }
            
            
            //--------------------------------------------------------------
            void Control::setParent(Container *parent) {
                _pparent = parent;
                getRoot(true);
                getDepth(true);
            }
            
            //--------------------------------------------------------------
            void Control::setParameter(Parameter* parameter, bool bOwner) {
                _pparameter = parameter;
                _bOwnsParameter = bOwner;
            }
            
            
            
        }
    }
}