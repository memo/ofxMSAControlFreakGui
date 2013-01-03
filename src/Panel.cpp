
#include "ofxMSAControlFreakGui/src/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Panel::Panel(Container *parent, string s) : Container(parent, ParameterPtr(new ParameterGroup(NULL, s))) {
                init();
            }

            //--------------------------------------------------------------
            Panel::Panel(Container *parent, ParameterGroupPtr p) : Container(parent, p) {
                init();
                addParameters(p);
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
                paramT = dynamic_cast<ParameterGroup*>(getParameter().get());
            }
            
            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                isOpen = bOpen;
                static_cast<ParameterBool*>(ptitleButton->getParameter().get())->setValue(bOpen);
                if(bRecursive) {
                    for(int i=0; i<getNumControls(); i++) {
                        Panel *p = dynamic_cast<Panel*>(getControl(i));
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
                            paramT->loadXmlValues(f.filePath);
                        }
                    }
                        break;
                        
                    case 2: // save
                    {
                        ofFileDialogResult f = ofSystemSaveDialog(getPath() + "-defaults.xml", "Save preset");
                        if(f.bSuccess) {
                            paramT->saveXmlValues(f.getPath());
//                            string path = ofFilePath::getEnclosingDirectory(f.getPath(), false);//f.filePath.substr(0, f.filePath.rfind("/"));
//                            paramT->saveXml(false, path + "/" + getPath() + "-" + f.fileName + ".xml");
//                            ofDirectory dir(path + "/" + getPath());
//                            if(!dir.exists()) dir.create(true);
//                            paramT->saveXml(false, dir.getAbsolutePath() + "/" + f.fileName + ".xml");
                        }
                    }
                        break;
                }
            }

            //--------------------------------------------------------------
            Panel& Panel::addPanel(ParameterGroupPtr p) {
                return (Panel&)*addControl(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Panel::addButton(ParameterPtr p) {
                return (BoolButton&)*addControl(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Panel::addColorPicker(ParameterPtr p) {
//                return (ColorPicker&)*addControl(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            DropdownList& Panel::addDropdownList(ParameterPtr p) {
                return (DropdownList&)*addControl(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(ParameterPtr p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = getConfig().layout.columnWidth;
                return (Content&)*addControl(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)*addControl(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Panel::addQuadWarper(ParameterPtr p) {
//                return (QuadWarp&)*addControl(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Panel::addSliderInt(ParameterPtr p) {
                return (SliderInt&)*addControl(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Panel::addSliderFloat(ParameterPtr p) {
                return (SliderFloat&)*addControl(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Panel::addSlider2d(ParameterPtr p) {
//                return (Slider2d&)*addControl(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            BoolTitle& Panel::addTitle(ParameterPtr p) {
                return (BoolTitle&)*addControl(new BoolTitle(this, p));
            }
            
            //--------------------------------------------------------------
            BoolToggle& Panel::addToggle(ParameterPtr p) {
                return (BoolToggle&)*addControl(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Panel::addParameter(ParameterPtr p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameter: " << getPath() << ": " << p->getPath();
                // if parameter already exists, remove it first
                
                ParameterGroupPtr pg(std::tr1::dynamic_pointer_cast<ParameterGroup>(p));
                if(pg) addPanel(pg);
                
                switch(p->getType()) {
                    case Type::kFloat: addSliderFloat(p); break;
                    case Type::kInt: addSliderInt(p); break;
                    case Type::kBool: {
                        ParameterBool &pb = *(ParameterBool*)p.get();
                        if(pb.getMode() == ParameterBool::kToggle) addToggle(p);
                        else addButton(p);
                    }
                        break;
                        
                    case Type::kNamedIndex: addDropdownList(p);

                    case Type::kGroup:
                        break;
                        
                    default:
                        ofLogWarning() << "msa::ControlFreak::Gui::addParameter: unknown type adding parameter " << p->getPath() << " " << p->getTypeName();
                        break;
                }
            }
            
            //--------------------------------------------------------------
            void Panel::addParameters(ParameterGroupPtr parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameters: " << getPath() << ": " << parameters->getPath();
                
//                if(!_config) setup();
                
                ptitleButton = new BoolTitle(this, getName());
                static_cast<ParameterBool*>(ptitleButton->getParameter().get())->setValue(true);
                addControl(ptitleButton);
                int np = parameters->getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(parameters->getParameter(i));
                }
            }
            
        }
    }
}
