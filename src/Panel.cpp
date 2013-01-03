
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
                isOpen = false;
            }
            
            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                isOpen = bOpen;
                ptitleButton->getParameter().setValue(bOpen);
                if(bRecursive) {
                    for(int i=0; i<children.size(); i++) {
                        Panel *p = dynamic_cast<Panel*>(children[i]);
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::buttonPressed(int i) {
                switch(i) {
                    case 0:
                        break;
                        
                    case 1: // load
                    {
                        ofFileDialogResult f = ofSystemLoadDialog("Load preset", false, ofToDataPath(""));
                        if(f.bSuccess) {
                            parameter->loadXmlValues(f.filePath);
                        }
                    }
                        break;
                        
                    case 2: // save
                    {
                        ofFileDialogResult f = ofSystemSaveDialog(getPath() + "-defaults.xml", "Save preset");
                        if(f.bSuccess) {
                            parameter->saveXmlValues(f.getPath());
//                            string path = ofFilePath::getEnclosingDirectory(f.getPath(), false);//f.filePath.substr(0, f.filePath.rfind("/"));
//                            parameter->saveXml(false, path + "/" + getPath() + "-" + f.fileName + ".xml");
//                            ofDirectory dir(path + "/" + getPath());
//                            if(!dir.exists()) dir.create(true);
//                            parameter->saveXml(false, dir.getAbsolutePath() + "/" + f.fileName + ".xml");
                        }
                    }
                        break;
                }
            }

            //--------------------------------------------------------------
            Panel& Panel::addPanel(Parameter *p) {
                return (Panel&)*children.add(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Panel::addButton(Parameter *p) {
                return (BoolButton&)*children.add(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Panel::addColorPicker(Parameter *p) {
//                return (ColorPicker&)*children.add(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            DropdownList& Panel::addDropdownList(Parameter *p) {
                return (DropdownList&)*children.add(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(Parameter *p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = getConfig().layout.columnWidth;
                return (Content&)*children.add(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)*children.add(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Panel::addQuadWarper(Parameter *p) {
//                return (QuadWarp&)*children.add(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Panel::addSliderInt(Parameter *p) {
                return (SliderInt&)*children.add(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Panel::addSliderFloat(Parameter *p) {
                return (SliderFloat&)*children.add(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Panel::addSlider2d(Parameter *p) {
//                return (Slider2d&)*children.add(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            BoolTitle& Panel::addTitle(Parameter *p) {
                return (BoolTitle&)*children.add(new BoolTitle(this, p));
            }
            
            //--------------------------------------------------------------
            BoolToggle& Panel::addToggle(Parameter *p) {
                return (BoolToggle&)*children.add(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Panel::addParameter(Parameter *p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameter - " << getPath() << ": " << p->getPath();
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
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameters - " << getPath() << ": " << parameters.getPath();
                
//                if(!_config) setup();
                
                ptitleButton = new BoolTitle(this, getName());
                ptitleButton->getParameter().setValue(true);
                children.add(ptitleButton);
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(parameters.getParameter(i));
                }
            }
            
            //--------------------------------------------------------------
            void Panel::update() {
                if(children.size()>0 && children[0]) children[0]->update();
                if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) children[i]->update();
            }
            
            //--------------------------------------------------------------
            void Panel::mouseMoved(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseMoved(e);
                else {
                    if(children.size()>0 && children[0]) children[0]->_mouseMoved(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) children[i]->_mouseMoved(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mousePressed(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mousePressed(e);
                else {
                    if(children.size()>0 && children[0]) {
                        children[0]->_mousePressed(e);
                        if(children[0]->hitTest(e.x, e.y)) getRoot()->setActiveControl(children[0]);
                    }
                    if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) {
                        children[i]->_mousePressed(e);
                        if(children[i]->hitTest(e.x, e.y)) getRoot()->setActiveControl(children[i]);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseDragged(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseDragged(e);
                else {
                    if(children.size()>0 && children[0]) children[0]->_mouseDragged(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) children[i]->_mouseDragged(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseReleased(ofMouseEventArgs &e) {
                if(pactiveControl)
                    pactiveControl->_mouseReleased(e);
                else {
                    if(children.size()>0 && children[0]) children[0]->_mouseReleased(e);
                    if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) children[i]->_mouseReleased(e);
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
                
                Control *c = children[0];
                if(c->isMouseOver()) {
                    if(keyUp)		c->onKeyUp();
                    if(keyDown)		c->onKeyDown();
                    if(keyLeft)		c->onKeyLeft();
                    if(keyRight)	c->onKeyRight();
                    if(keyEnter)	c->onKeyEnter();
                    c->_keyPressed(e);
                }
                
                if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) {
                    Control *c = children[i];
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
                if(children[0]->isMouseOver()) children[0]->_keyReleased(e);
                if(getInheritedScale().y>0.9) for(int i=1; i<children.size(); i++) if(children[i]->isMouseOver()) children[i]->_keyReleased(e);
            }
            
            //--------------------------------------------------------------
//            vector <ControlPtr>&	Panel::getControls() {
//                return controls;
//            }
            
        }
    }
}
