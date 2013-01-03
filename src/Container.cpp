

#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Container::Container(Container *parent, ParameterPtr p):Control(parent, p) {
                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            void Container::clear() {
                _controls.clear();
            }

            
            //--------------------------------------------------------------
            int Container::getNumControls() const {
                return _controls.size();
            }
            
            //--------------------------------------------------------------
            Control* Container::getControl(int i) const {
                return _controls[i].get();
            }
            
            
            //--------------------------------------------------------------
            Control* Container::addControl(Control *control) {
                _controls.push_back(ControlPtr(control));
                control->setParent(_pparent);
                return control;
            }
            
            //--------------------------------------------------------------
//            Control* Container::operator[](int index) {
//                return get(index);
//            }

            //--------------------------------------------------------------
            void Container::setActiveControl(Control* control) {
                // if old control exists, put it at the back
                if(_pactiveControl) _pactiveControl->z = 0;
                
                _pactiveControl = control;
                
                // put new active control at the front
                if(_pactiveControl) {
                    _pactiveControl->z = -1000;
                    //                    ofLogNotice() << "setting active control [" << pactiveControl->name << "] for panel [" << name;
                    //                } else {
                    //                    ofLogNotice() << "setting active control NULL for panel [" << name;
                }
            }
            
            //--------------------------------------------------------------
            Control* Container::getActiveControl() {
                return _pactiveControl;
            }
            
            //--------------------------------------------------------------
            void Container::releaseActiveControl() {
                setActiveControl(NULL);
            }
            
            //--------------------------------------------------------------
            //            bool Container::isActive() {
            //                bool b = pactiveControl == ptitleButton;//pactiveControl != NULL;
            //                return parent ? b | parent->isActive() : b;
            //            }
            

            //--------------------------------------------------------------
            void Container::mouseMoved(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseMoved(e);
                else {
                    if(getNumControls()>0 && getControl(0)) getControl(0)->_mouseMoved(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) getControl(i)->_mouseMoved(e);
                }
            }
            
            //--------------------------------------------------------------
            void Container::update() {
                if(getNumControls()>0 && getControl(0)) getControl(0)->update();
                if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) getControl(i)->update();
            }
            
            
            //--------------------------------------------------------------
            void Container::mousePressed(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mousePressed(e);
                else {
                    if(getNumControls()>0 && getControl(0)) {
                        getControl(0)->_mousePressed(e);
                        if(getControl(0)->hitTest(e.x, e.y)) getRoot()->setActiveControl(getControl(0));
                    }
                    if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) {
                        getControl(i)->_mousePressed(e);
                        if(getControl(i)->hitTest(e.x, e.y)) getRoot()->setActiveControl(getControl(i));
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseDragged(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseDragged(e);
                else {
                    if(getNumControls()>0 && getControl(0)) getControl(0)->_mouseDragged(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) getControl(i)->_mouseDragged(e);
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseReleased(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseReleased(e);
                else {
                    if(getNumControls()>0 && getControl(0)) getControl(0)->_mouseReleased(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) getControl(i)->_mouseReleased(e);
                }
                
                getRoot()->releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Container::keyPressed(ofKeyEventArgs &e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                Control *c = getControl(0);
                if(c->isMouseOver()) {
                    if(keyUp)		c->onKeyUp();
                    if(keyDown)		c->onKeyDown();
                    if(keyLeft)		c->onKeyLeft();
                    if(keyRight)	c->onKeyRight();
                    if(keyEnter)	c->onKeyEnter();
                    c->_keyPressed(e);
                }
                
                if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) {
                    Control *c = getControl(i);
                    if(c->isMouseOver()) {
                        if(keyUp)		c->onKeyUp();
                        if(keyDown)		c->onKeyDown();
                        if(keyLeft)		c->onKeyLeft();
                        if(keyRight)	c->onKeyRight();
                        if(keyEnter)	c->onKeyEnter();
                        c->_keyPressed(e);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::keyReleased(ofKeyEventArgs &e) {
                if(getControl(0)->isMouseOver()) getControl(0)->_keyReleased(e);
                if(getInheritedScale().y>0.9) for(int i=1; i<getNumControls(); i++) if(getControl(i)->isMouseOver()) getControl(i)->_keyReleased(e);
            }


        }
    }
}