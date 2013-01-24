

#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            Container::Container(Container *parent, string s) : Control(parent, new ParameterGroup(s, NULL), true) {
                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            Container::Container(Container *parent, Parameter* p, bool bOwnsParameter):Control(parent, p, bOwnsParameter) {
                _pactiveControl = NULL;
            }
            
            //--------------------------------------------------------------
            Container::~Container() {
                clear();
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
            Control& Container::get(int i) const {
                return _controls[i];
            }
            
            //--------------------------------------------------------------
            Control& Container::get(string name) const {
                return _controls[name];
            }
            
            //--------------------------------------------------------------
            Control& Container::operator[](int index) const {
                return get(index);
            }
            
            //--------------------------------------------------------------
            Control& Container::operator[](string name) const {
                return get(name);
            }
            
            //--------------------------------------------------------------
            Control& Container::add(Control *control) {
                _controls.push_back(control->getParameter().getName(), control);
                control->setParent(this);
                return *control;
            }
            
            //--------------------------------------------------------------
            void Container::setActiveControl(Control *control) {
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
                return (Panel&)add(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Container::addButton(ParameterBool* p) {
                return (BoolButton&)add(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Container::addColorPicker(Parameter* p) {
                //                return (ColorPicker&)add(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            DropdownList& Container::addDropdownList(ParameterNamedIndex* p) {
                return (DropdownList&)add(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            List& Container::addList(ParameterNamedIndex* p) {
                return (List&)add(new List(this, p));
            }
            
            //--------------------------------------------------------------
            Options& Container::addOptions(ParameterNamedIndex* p) {
                return (Options&)add(new Options(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Container::addContent(Parameter* p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = pconfig->layout.columnWidth;
                return (Content&)add(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Container::addFPSCounter() {
                return (FPSCounter&)add(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Container::addQuadWarper(Parameter* p) {
                //                return (QuadWarp&)add(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Container::addSliderInt(ParameterInt* p) {
                return (SliderInt&)add(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Container::addSliderFloat(ParameterFloat* p) {
                return (SliderFloat&)add(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Container::addSlider2d(Parameter* p) {
                //                return (Slider2d&)add(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            //            BoolTitle& Container::addTitle(Parameter* p) {
            //                return (BoolTitle&)add(new BoolTitle(this, p));
            //            }
            
            //--------------------------------------------------------------
            BoolToggle& Container::addToggle(ParameterBool* p) {
                return (BoolToggle&)add(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Container::add(Parameter* p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Container::add: " << getPath() << ": " << p->getPath();
                // if parameter already exists, remove it first
                
                if(typeid(*p) == typeid(ParameterGroup)) {
                    ParameterGroup* pp = dynamic_cast<ParameterGroup*>(p);
                    if(pp) {
                        switch(pp->getMode()) {
                            case ParameterGroup::kPage: {
                                Gui* gui = dynamic_cast<Gui*>(getRoot());
                                if(gui) gui->addParameters(*pp);
                            }
                                break;
                                
                            case ParameterGroup::kGroup:
                                addPanel(pp);
                                break;
                        }
                    }
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
                    }
                    return;
                }
                if(typeid(*p) == typeid(ParameterNamedIndex)) {
                    ParameterNamedIndex *pp(dynamic_cast<ParameterNamedIndex*>(p));
                    if(pp) {
                        switch(pp->getMode()) {
                            case ParameterNamedIndex::kDropdown:
                                addDropdownList(pp);
                                break;
                                
                            case ParameterNamedIndex::kList:
                                addList(pp);
                                break;
                                
                            case ParameterNamedIndex::kOptions:
                                addOptions(pp);
                                break;
                        }
                    }
                    return;
                }
                
                
                ofLogWarning() << "msa::ControlFreak::gui::Container::add: unknown type adding parameter " << p->getPath() << " " << p->getTypeName();
            }
            
            //--------------------------------------------------------------
            void Container::addParameters(ParameterGroup* parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Container::addParameters: " << getPath() << ": " << parameters->getPath();
                
                int np = parameters->size();
                for(int i=0; i<np; i++) {
                    add(&parameters->get(i));
                }
            }
            
            
            //--------------------------------------------------------------
            void Container::update() {
                Control::update();
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) get(i)._update();
            }
            
            
            //--------------------------------------------------------------
            void Container::mouseMoved(int x, int y) {
                ofMouseEventArgs e;
                e.x = x;
                e.y = y;
                
                if(_pactiveControl)
                    _pactiveControl->_mouseMoved(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        get(i)._mouseMoved(e);
                        //                        if(get(i).isMouseOver()) return;    // don't propogate event if this control processed it
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mousePressed(int x, int y, int button) {
                ofMouseEventArgs e;
                e.x = x;
                e.y = y;
                e.button = button;
                
                if(_pactiveControl)
                    _pactiveControl->_mousePressed(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        get(i)._mousePressed(e);
                        if(get(i).isMouseOver()) {
                            getRoot()->setActiveControl(&get(i));
                            return;    // don't propogate event if this control processed it
                        }
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseDragged(int x, int y, int button) {
                ofMouseEventArgs e;
                e.x = x;
                e.y = y;
                e.button = button;
                
                if(_pactiveControl)
                    _pactiveControl->_mouseDragged(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                        get(i)._mouseDragged(e);
                        //                        if(get(i).isMouseOver()) return;    // don't propogate event if this control processed it
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::mouseReleased(int x, int y, int button) {
                ofMouseEventArgs e;
                e.x = x;
                e.y = y;
                e.button = button;
                
                if(_pactiveControl)
                    _pactiveControl->_mouseReleased(e);
                else {
                    if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) get(i)._mouseReleased(e);
                }
                
                if(getRoot()) getRoot()->releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Container::keyPressed(int key) {
                ofKeyEventArgs e;
                e.key = key;
                
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) {
                    Control &c = get(i);
                    if(c.isMouseOver()) {
                        if(keyUp)		c.onKeyUp();
                        if(keyDown)		c.onKeyDown();
                        if(keyLeft)		c.onKeyLeft();
                        if(keyRight)	c.onKeyRight();
                        if(keyEnter)	c.onKeyEnter();
                        c._keyPressed(e);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Container::keyReleased(int key) {
                ofKeyEventArgs e;
                e.key = key;
                
                if(getInheritedScale().y>0.9) for(int i=getNumControls()-1; i>=0; --i) if(get(i).isMouseOver()) get(i)._keyReleased(e);
            }
            
            
        }
    }
}