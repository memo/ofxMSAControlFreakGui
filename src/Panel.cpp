
#include "ofxMSAControlFreakGui/src/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Panel::Panel(Panel *parent, string s) : ControlParameterT<ParameterGroup>(parent, s) {
                init();
            }

            //--------------------------------------------------------------
            Panel::Panel(Panel *parent, Parameter *p) : ControlParameterT<ParameterGroup>(parent, p) {
                init();
                addParameters(dynamic_cast<ParameterGroup&>(*p));
            }
            
            //--------------------------------------------------------------
            Panel::~Panel() {
                // delete all controls NOT NEEDED, using smart pointers
            }
            
            //--------------------------------------------------------------
            void Panel::init() {
                disableAllEvents();
                width = 0;
                height = 0;
                pactiveControl = NULL;
                isOpen = false;
                heightScale = 1.0;
            }
            
            //--------------------------------------------------------------
            float Panel::getParentHeightScale() {
                return getParent() ? getParent()->getHeightScale() : heightScale;
            }
            
            //--------------------------------------------------------------
            float Panel::getHeightScale() {
                return heightScale * getParentHeightScale();
            }

            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                isOpen = bOpen;
                ptitleButton->getParameter().setValue(bOpen);
                if(bRecursive) {
                    for(int i=0; i<controls.size(); i++) {
                        Panel *p = dynamic_cast<Panel*>(controls[i].get());
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            Control& Panel::addControl(Control *control) {
                controls.push_back(ControlPtr(control));
                return *control;
            }
            
            //--------------------------------------------------------------
            Panel& Panel::addPanel(Parameter *p) {
                return (Panel&)addControl(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Panel::addButton(Parameter *p) {
                return (BoolButton&)addControl(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Panel::addColorPicker(Parameter *p) {
//                return (ColorPicker&)addControl(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            DropdownList& Panel::addDropdownList(Parameter *p) {
                return (DropdownList&)addControl(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(Parameter *p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = getConfig().layout.columnWidth;
                return (Content&)addControl(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)addControl(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Panel::addQuadWarper(Parameter *p) {
//                return (QuadWarp&)addControl(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Panel::addSliderInt(Parameter *p) {
                return (SliderInt&)addControl(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Panel::addSliderFloat(Parameter *p) {
                return (SliderFloat&)addControl(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Panel::addSlider2d(Parameter *p) {
//                return (Slider2d&)addControl(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            BoolTitle& Panel::addTitle(Parameter *p) {
                return (BoolTitle&)addControl(new BoolTitle(this, p));
            }
            
            //--------------------------------------------------------------
            BoolToggle& Panel::addToggle(Parameter *p) {
                return (BoolToggle&)addControl(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Panel::addParameter(Parameter *p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameter - " << parameter->getPath() << ": " << p->getPath();
                // if parameter already exists, remove it first
                
                ParameterGroup *pc = dynamic_cast<ParameterGroup*>(p);
                if(pc) addPanel(pc);
                
                switch(p->getType()) {
                    case Type::kFloat: addSliderFloat(p); break;
                    case Type::kInt: addSliderInt(p); break;
                    case Type::kBool: {
                        ParameterBool &pb = *(ParameterBool*)p;
                        if(pb.getMode() == ParameterBool::kToggle) addToggle(p);
                        else addButton(p);
                    }
                        break;
                        
                    case Type::kNamedIndex: addDropdownList(p);

                    case Type::kGroup:
                        break;
                        
                    default:
                        ofLogWarning() << "msa::ControlFreak::Gui::addParameter - unknown type adding parameter " << p->getPath() << " " << p->getTypeName();
                        break;
                }
            }
            
            //--------------------------------------------------------------
            void Panel::addParameters(ParameterGroup& parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameters - " << parameter->getPath() << ": " << parameters.getPath();
                
//                if(!_config) setup();
                
                ptitleButton = new BoolTitle(this, parameter->getName());
                ptitleButton->getParameter().setValue(true);
                addControl(ptitleButton);
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(&parameters.getParameter(i));
                }
            }
            
            //--------------------------------------------------------------
            void Panel::setActiveControl(Control* control) {
                // if old control exists, put it at the back
                if(pactiveControl) pactiveControl->z = 0;
                
                pactiveControl = control;
                
                // put new active control at the front
                if(pactiveControl) {
                    pactiveControl->z = -1000;
//                    ofLogNotice() << "setting active control [" << pactiveControl->name << "] for panel [" << name;
//                } else {
//                    ofLogNotice() << "setting active control NULL for panel [" << name;
                }
            }
            
            //--------------------------------------------------------------
            Control* Panel::getActiveControl() {
                return pactiveControl;
            }
            
            //--------------------------------------------------------------
            void Panel::releaseActiveControl() {
                setActiveControl(NULL);
            }
            
            //--------------------------------------------------------------
//            bool Panel::getActive() {
//                bool b = pactiveControl == ptitleButton;//pactiveControl != NULL;
//                return parent ? b | parent->getActive() : b;
//            }

            
            //--------------------------------------------------------------
            void Panel::update() {
                if(controls.size()>0 && controls[0]) controls[0]->update();
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->update();
            }
            
            //--------------------------------------------------------------
            void Panel::mouseMoved(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseMoved(e);
                else {
                    if(controls.size()>0 && controls[0]) controls[0]->_mouseMoved(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseMoved(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mousePressed(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mousePressed(e);
                else {
                    if(controls.size()>0 && controls[0]) {
                        controls[0]->_mousePressed(e);
                        if(controls[0]->hitTest(e.x, e.y)) getRoot()->setActiveControl(controls[0].get());
                    }
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                        controls[i]->_mousePressed(e);
                        if(controls[i]->hitTest(e.x, e.y)) getRoot()->setActiveControl(controls[i].get());
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseDragged(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseDragged(e);
                else {
                    if(controls.size()>0 && controls[0]) controls[0]->_mouseDragged(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseDragged(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseReleased(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseReleased(e);
                else {
                    if(controls.size()>0 && controls[0]) controls[0]->_mouseReleased(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseReleased(e);
                }
                
                getRoot()->releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Panel::keyPressed(ofKeyEventArgs &e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                Control *c = controls[0].get();
                if(c->isMouseOver()) {
                    if(keyUp)		c->onKeyUp();
                    if(keyDown)		c->onKeyDown();
                    if(keyLeft)		c->onKeyLeft();
                    if(keyRight)	c->onKeyRight();
                    if(keyEnter)	c->onKeyEnter();
                    c->_keyPressed(e);
                }
                
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                    Control *c = controls[i].get();
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
            void Panel::keyReleased(ofKeyEventArgs &e) {
                if(controls[0]->isMouseOver()) controls[0]->_keyReleased(e);
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
            }
            
            //--------------------------------------------------------------
//            vector <ControlPtr>&	Panel::getControls() {
//                return controls;
//            }
            
        }
    }
}
