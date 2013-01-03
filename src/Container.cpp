

#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Container::Container() {
                _pactiveControl = NULL;
                _pparent = NULL;
            }
            
            //--------------------------------------------------------------
            void Container::clear() {
                _controls.clear();
            }

            
            //--------------------------------------------------------------
            int Container::size() const {
                return _controls.size();
            }
            
            //--------------------------------------------------------------
            Control* Container::get(int i) const {
                return _controls[i].get();
            }
            
            
            //--------------------------------------------------------------
            Control* Container::add(Control *control) {
                _controls.push_back(ControlPtr(control));
                control->setParent(_pparent);
                return control;
            }
            
            //--------------------------------------------------------------
            Control* Container::operator[](int index) {
                return get(index);
            }

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
            //            bool Panel::isActive() {
            //                bool b = pactiveControl == ptitleButton;//pactiveControl != NULL;
            //                return parent ? b | parent->isActive() : b;
            //            }
            



        }
    }
}