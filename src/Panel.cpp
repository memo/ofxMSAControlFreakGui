
#include "ofxMSAControlFreakGui/src/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
//            //--------------------------------------------------------------
//            Panel::Panel(Container *parent, string s) : Container(parent, s) {
//                init();
//            }
            
            //--------------------------------------------------------------
            Panel::Panel(Container *parent, ParameterGroup* p) : Container(parent, p) {
                init();
                
                doAutoLayout = true;
                localRect.set(0, 0, 1, 0); // TODO: hack?
                
                titleButton = new BoolTitle(this, getName());
                titleButton->doAutoLayout = false;
                titleButton->setZ(1);
                titleButton->getParameter().set(true);
                addControl(titleButton);
                
                collapseAllButton = new BoolSimpleCircle(this, "-");
                collapseAllButton->doAutoLayout = false;
                collapseAllButton->setZ(2);
                collapseAllButton->setMode(ParameterBool::kBang);
//                collapseAllButton->getParameter().setTooltip("Collapse all panels under '" + getPath() + "'");
                addControl(collapseAllButton);
//                expandAllButton = new BoolSimpleCircle(this, "+");
//                expandAllButton->doAutoLayout = false;
//                expandAllButton->setMode(ParameterBool::kBang);
//                expandAllButton->getParameter().setTooltip("Expand all panels under '" + getPath() + "'");
//                addControl(expandAllButton);
                
                saveButton = new BoolSimpleCircle(this, "s");
                saveButton->doAutoLayout = false;
                saveButton->setZ(2);
                saveButton->setMode(ParameterBool::kBang);
                saveButton->getParameter().setTooltip("Save preset for '" + getPath() + "'");
                addControl(saveButton);
                
                loadButton = new BoolSimpleCircle(this, "l");
                loadButton->doAutoLayout = false;
                loadButton->setZ(2);
                loadButton->setMode(ParameterBool::kBang);
                loadButton->getParameter().setTooltip("Load preset for '" + getPath() + "'");
                addControl(loadButton);
                
                children = new Container(this, getName() + "_children");
                children->doAutoLayout = true;
                children->localRect.set(0, 0, 1, 3);
                addControl(children);
                
                children->addParameters(p);
            }
            
            //--------------------------------------------------------------
            Panel::~Panel() {
                if(layoutManager) delete layoutManager;
            }
            
            //--------------------------------------------------------------
            void Panel::init() {
                disableAllEvents();
                layoutManager = NULL;
                width = 0;
                height = 0;
                isOpen = false;
                paramT = dynamic_cast<ParameterGroup*>(&getParameter());
                setZ(getInheritedZ()+100);
            }
            
            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                isOpen = bOpen;
                titleButton->getParameter().set(bOpen);
                if(bRecursive) {
                    for(int i=0; i<children->getNumControls(); i++) {
                        Panel *p = dynamic_cast<Panel*>(children->getControl(i));
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::onUpdate() {
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                
                collapseAllButton->localRect.set(p, y, s, s);
//                expandAllButton->localRect.set(p + s + p, y, s, s);
                loadButton->localRect.set(titleButton->width - (s + p), y, s, s);
                saveButton->localRect.set(titleButton->width - (s + p) * 2, y, s, s);
                
                if(isOpen) {
                    collapseAllButton->getParameter().setName("-");
                    collapseAllButton->getParameter().setTooltip("Collapse all panels under '" + getPath() + "'");
                } else {
                    collapseAllButton->getParameter().setName("+");
                    collapseAllButton->getParameter().setTooltip("Expand all panels under '" + getPath() + "'");
                }
                if(collapseAllButton->getParameter().value()) showPanel(!isOpen, true);
//                if(expandAllButton->getParameter().value()) showPanel(true, true);
                if(loadButton->getParameter().value()) {
                    ofFileDialogResult f = ofSystemLoadDialog("Load preset", false, ofToDataPath(""));
                    if(f.bSuccess) {
                        paramT->loadXmlValues(f.filePath);
                    }
                }
                
                if(saveButton->getParameter().value()) {
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
            }
            
            
        }
    }
}
