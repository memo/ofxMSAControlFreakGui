
#include "ofxMSAControlFreakGui/src/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            Control::Control(Container *parent, ParameterPtr parameter) {
                setParameter(parameter);
                setParent(parent);
                
                z = 0;
                newColumn = false;
                keyboardShortcut = 0;
//                setKeyboardShortcut(0);
                scale.set(1, 1);
                doAutoLayout = true;
                localRect.set(0, 0, 0, 0);

                
                _alpha = 1;
                
                setup();
                
                // we don't want auto events (they will be controlled via the parent panels)
                disableAllEvents();
            }
            
            //--------------------------------------------------------------
            Control &Control::setConfig(Config *config) {
                _pconfig = config;
                setup();
                return *this;
            }
            
            //--------------------------------------------------------------
            Control &Control::setNewColumn(bool b) {
                newColumn = b;
                return *this;
            }
            
            
            //--------------------------------------------------------------
            Container* Control::getParent() {
                return _pparent;
            }
            
            //--------------------------------------------------------------
            Container* Control::getRoot(bool bUpdate) {
                if(bUpdate) return _proot = ( getParent() ? getParent()->getRoot(true) : dynamic_cast<Container*>(this) );
                else return _proot;
//                return getParent() ? getParent()->_proot : _proot;
            }
            
            //--------------------------------------------------------------
            Config &Control::getConfig() {
                return *_pconfig;
            }
//
            //--------------------------------------------------------------
            int Control::getDepth() {
                return getParent() ? getParent()->getDepth() + 1 : 0;
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
            string Control::getName() {
                return getParameter()->getName();
            }
            
            //--------------------------------------------------------------
            string Control::getPath() {
                return getParameter()->getPath();
            }
            
            //--------------------------------------------------------------
            ParameterPtr Control::getParameter() {
                return _parameter;
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
                return setColor(getConfig().colors.bg);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setTextColor() {
                return setColor(getConfig().colors.text);
            }
            
            
            //--------------------------------------------------------------
            ofColor Control::setSliderColor(bool b) {
                if(b) return setColor(getConfig().colors.slider.full);
                else return setColor(getConfig().colors.slider.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setToggleColor(bool b) {
                if(b) return setColor(getConfig().colors.toggle.full);
                else return setColor(getConfig().colors.toggle.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setBorderColor() {
                return setColor(getConfig().colors.border);
            }
            
            //--------------------------------------------------------------
            bool Control::doTooltip(int millis) {
                return isMouseOver() && getStateChangeMillis() > (millis < 0 ? 250 : millis);
            }
            
            //--------------------------------------------------------------
            void Control::setTooltip(string s) {
                // if s is empty, use string from parameter
                if(s.empty()) s = getParameter()->getTooltip();
                if(doTooltip() && !s.empty()) {
                    Renderer::instance().setToolTip(getParameter()->getTooltip());
                }
            }
            

            //--------------------------------------------------------------
            void Control::drawText(int x, int y, string s, ofColor *c) {
                s = s.empty() ? getName() : s;
                setColor(c ? c : getConfig().colors.text);
                getConfig().drawString(s, x, y);
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
                return getConfig().font.getStringBoundingBox(s, x, y);
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
                setColor(c ? c : getConfig().colors.border);
                glLineWidth(1.0);
                ofRect(0, 0, width, height);
            }

            //--------------------------------------------------------------
            void Control::update() {
                onUpdate();
            }
            
            //--------------------------------------------------------------
            void Control::draw() {
                setTooltip();

                ofPushStyle();
                ofPushMatrix();
                ofTranslate(x, y);
                ofEnableAlphaBlending();
                
                float targetAlpha = getStateChangeMillis() > getConfig().colors.fade.delayMillis && getRoot()->getActiveControl() && !getParentActive() ? getConfig().colors.fade.alpha : 1.0f;
                float diff = (targetAlpha - _alpha);
                _alpha += diff * getConfig().colors.fade.speed;
                if(fabsf(diff) < 0.05) _alpha = targetAlpha;
                
                ofPushMatrix();
                ofPushStyle();
                onDraw();
                ofPopStyle();
                ofPopMatrix();
                
//                if(isMouseOver()) {
//                    ofFill();
//                    setColor(ofColor(255, 128));
//                    int ts = height * 0.5;
//                    ofTriangle(width, height, width, height - ts, width - ts, height);
//                    if(getMouseX() > x + width - ts && getMouseY() > y + height - ts) Renderer::instance().setToolTip("Open config menu");
//                }

                ofPopMatrix();
                ofPopStyle();
            }
            
            
            //--------------------------------------------------------------
            void Control::setParent(Container *parent) {
                _pparent = parent;
                getRoot(true);
            }
            
            //--------------------------------------------------------------
            void Control::setParameter(ParameterPtr parameter) {
                _parameter = parameter;
            }

            
            
        }
    }
}