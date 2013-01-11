

#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            Container::Container(Container *parent, string s):Control(parent, new ParameterGroup(s, NULL), true) {
                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            Container::Container(Container *parent, Parameter* p):Control(parent, p) {
                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            Container::~Container() {
                clear();
            }
            
            //--------------------------------------------------------------
            void Container::clear() {
                for(int i=0; i<_controls.size(); i++) delete _controls[i];
                _controls.clear();
            }
            
            
            //--------------------------------------------------------------
            int Container::getNumControls() const {
                return _controls.size();
            }
            
            //--------------------------------------------------------------
            Control* Container::getControl(int i) const {
                return _controls[i];
            }
            
            
            //--------------------------------------------------------------
            Control* Container::addControl(Control *control) {
                _controls.push_back(control);
                control->setParent(this);
                return control;
            }
            
            //--------------------------------------------------------------
            Control* Container::operator[](int index) {
                return getControl(index);
            }
            
            //--------------------------------------------------------------
            void Container::setActiveControl(Control* control) {
                ofLogVerbose() << "msa::ControlFreak::Gui::Container::setActiveControl: " << (control ? control->getParameter().getPath() : "NULL");
                // if old control exists, put it at the back
                if(_pactiveControl) _pactiveControl->popZ();
                
                _pactiveControl = control;
                
                // put new active control at the front
                if(_pactiveControl) {
                    _pactiveControl->setZ(1e100);
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
            //                bool b = pactiveControl == titleButton;//pactiveControl != NULL;
            //                return parent ? b | parent->isActive() : b;
            //            }
            
            
            
            
            //--------------------------------------------------------------
            Panel& Container::addPanel(ParameterGroup* p) {
                return (Panel&)*addControl(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Container::addButton(ParameterBool* p) {
                return (BoolButton&)*addControl(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Container::addColorPicker(Parameter* p) {
                //                return (ColorPicker&)*addControl(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            DropdownList& Container::addDropdownList(ParameterNamedIndex* p) {
                return (DropdownList&)*addControl(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            List& Container::addList(ParameterNamedIndex* p) {
                return (List&)*addControl(new List(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Container::addContent(Parameter* p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = getConfig().layout.columnWidth;
                return (Content&)*addControl(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Container::addFPSCounter() {
                return (FPSCounter&)*addControl(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Container::addQuadWarper(Parameter* p) {
                //                return (QuadWarp&)*addControl(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Container::addSliderInt(ParameterInt* p) {
                return (SliderInt&)*addControl(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Container::addSliderFloat(ParameterFloat* p) {
                return (SliderFloat&)*addControl(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Container::addSlider2d(Parameter* p) {
                //                return (Slider2d&)*addControl(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            //            BoolTitle& Container::addTitle(Parameter* p) {
            //                return (BoolTitle&)*addControl(new BoolTitle(this, p));
            //            }
            
            //--------------------------------------------------------------
            BoolToggle& Container::addToggle(ParameterBool* p) {
                return (BoolToggle&)*addControl(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Container::addParameter(Parameter* p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Container::addParameter: " << getPath() << ": " << p->getPath();
                // if parameter already exists, remove it first
                
                if(typeid(*p) == typeid(ParameterGroup)) {
                    addPanel(dynamic_cast<ParameterGroup*>(p));
                    return;
                }
                if(typeid(*p) == typeid(ParameterFloat)) {
                    addSliderFloat(dynamic_cast<ParameterFloat*>(p));
                    return;
                }
                if(typeid(*p) == typeid(ParameterInt)) {
                    addSliderInt(dynamic_cast<ParameterInt*>(p));
                    return;
                }
                if(typeid(*p) == typeid(ParameterBool)) {
                    ParameterBool *pp(dynamic_cast<ParameterBool*>(p));
                    if(pp) {
                        if(pp->getMode() == ParameterBool::kToggle) addToggle(pp);
                        else addButton(pp);
                        return;
                    }
                }
                if(typeid(*p) == typeid(ParameterNamedIndex)) {
                    ParameterNamedIndex *pp(dynamic_cast<ParameterNamedIndex*>(p));
                    if(pp) {
                        if(pp->getMode() == ParameterNamedIndex::kDropdown) addDropdownList(pp);
                        else addList(pp);
                        return;
                    }
                }
                
                
                ofLogWarning() << "msa::ControlFreak::gui::Container::addParameter: unknown type adding parameter " << p->getPath() << " " << p->getTypeName();
            }
            
            //--------------------------------------------------------------
            void Container::addParameters(ParameterGroup* parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Container::addParameters: " << getPath() << ": " << parameters->getPath();
                
                int np = parameters->getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(parameters->getPtr(i));
                }
            }
            
            
            //--------------------------------------------------------------
            void Container::mouseMoved(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseMoved(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        getControl(i)->_mouseMoved(e);
                        //                        if(getControl(i)->isMouseOver()) return;    // don't propogate event if this control processed it
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::update() {
                Control::update();
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) getControl(i)->update();
            }
            
            
            //--------------------------------------------------------------
            void Container::mousePressed(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mousePressed(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        getControl(i)->_mousePressed(e);
                        if(getControl(i)->isMouseOver()) {
                            getRoot()->setActiveControl(getControl(i));
                            return;    // don't propogate event if this control processed it
                        }
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseDragged(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseDragged(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        getControl(i)->_mouseDragged(e);
                        //                        if(getControl(i)->isMouseOver()) return;    // don't propogate event if this control processed it
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseReleased(ofMouseEventArgs &e) {
                if(_pactiveControl)
                    _pactiveControl->_mouseReleased(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) getControl(i)->_mouseReleased(e);
                }
                
                if(getRoot()) getRoot()->releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Container::keyPressed(ofKeyEventArgs &e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
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
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) if(getControl(i)->isMouseOver()) getControl(i)->_keyReleased(e);
            }
            
            
        }
    }
}