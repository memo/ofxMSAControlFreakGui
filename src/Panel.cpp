
#include "ofxMSAControlFreakGui/src/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Panel::Panel(Container *parent, string s) : Container(parent, s) {
                init();
            }

            //--------------------------------------------------------------
            Panel::Panel(Container *parent, ParameterGroupPtr p) : Container(parent, p) {
                init();
                
                // create and add Title button
                titleButton = new BoolTitle(this, getName());
                static_cast<ParameterBool*>(titleButton->getParameter().get())->setValue(true);
                addControl(titleButton);
                //                titleButton->doAutoLayout = false;
//                titleButton->localRect.set(0, 0, 250, 50);
                
                
                children = new Container(this, getName() + "_controls");
//                children->doAutoLayout = true;
                children->localRect.set(0, 0, 1, 1);
                addControl(children);
                
                children->addParameters(p);
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
                static_cast<ParameterBool*>(titleButton->getParameter().get())->setValue(bOpen);
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

            
        }
    }
}
