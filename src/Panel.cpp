
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

//                layout.doAutoLayout = true;
//                layout.width = 1;
//                layout.height = 1;
                
                titleButton = new BoolTitle(this, getName());
                titleButton->layout.positionMode = 1;
                titleButton->setZ(1);
                titleButton->getParameter().set(true);
                add(titleButton);
                
                collapseAllButton = new BoolSimpleCircle(this, "-");
                collapseAllButton->layout.positionMode = 1;
                collapseAllButton->setZ(2);
                collapseAllButton->setMode(ParameterBool::kBang);
                add(collapseAllButton);
                
                saveButton = new BoolSimpleCircle(this, "s");
                saveButton->layout.positionMode = 1;
                saveButton->setZ(2);
                saveButton->setMode(ParameterBool::kToggle);
                saveButton->getParameter().setTooltip("Save preset for '" + getPath() + "'");
                saveButton->getParameter().trackVariable(&presetManager.bSaveOpen);
                add(saveButton);
                
                loadButton = new BoolSimpleCircle(this, "l");
                loadButton->layout.positionMode = 1;
                loadButton->setZ(2);
                loadButton->setMode(ParameterBool::kToggle);
                loadButton->getParameter().setTooltip("Load preset for '" + getPath() + "'");
                loadButton->getParameter().trackVariable(&presetManager.bLoadOpen);
                add(loadButton);
                
                presetDropdown = new List(this, "presets");
                presetDropdown->layout.positionMode = 1;
                presetDropdown->layout.doIncludeInContainerRect = false;
                presetDropdown->setZ(1e100);
                presetDropdown->setMode(ParameterNamedIndex::kList);
                add(presetDropdown);
                presetManager.setup(presetDropdown->getParameter());
                
                // add wrap button only if we are the root
                if(getParent() == NULL) {
                    wrapButton = new BoolSimpleCircle(this, "w");
                    wrapButton->layout.positionMode = 1;
                    wrapButton->setZ(2);
                    wrapButton->setMode(ParameterBool::kToggle);
                    wrapButton->getParameter().setTooltip("Wrap");
                    add(wrapButton);
                    
                    scrollbar = new ScrollBar(this);
                    scrollbar->layout.positionMode = 2;
                    scrollbar->setZ(-1);
                    scrollbar->doIsolateOnActive = false;
                    scrollbar->layout.doIncludeInContainerRect = false;
                    scrollbar->getParameter().setTooltip("Scroll " + getPath());
                    add(scrollbar);
                } else {
                    wrapButton = NULL;
                    scrollbar = NULL;
                }

                
                children = new Container(this, getName() + "_children");
                children->layout.doAffectFlow = false;
//                children->layout.set(0, 0, 1, 3);
                add(children);
                
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
                paramT = dynamic_cast<ParameterGroup*>(&getParameter());
            }
            
            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                titleButton->getParameter().set(bOpen);
                if(bRecursive) {
                    for(int i=0; i<children->size(); i++) {
                        Panel *p = dynamic_cast<Panel*>(&children->get(i));
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::onUpdate() {

                // set positions and layout
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
//                layout.setPosition(0, titleButton->height);
//                layout.paddingPre.y = titleButton->height;
//                layout.paddingPost.y = titleButton->height/2;

                collapseAllButton->layout.set(p, y, s, s);
                saveButton->layout.set(titleButton->width - (s + p) * 2, y, s, s);
                loadButton->layout.set(titleButton->width - (s + p), y, s, s);
                presetDropdown->layout.set(0, loadButton->layout.getBottom(), titleButton->width*1.5, titleButton->height);

                
                // check buttons and stuff
                if(wrapButton) {
                    wrapButton->layout.set(titleButton->width - (s + p) * 3, y, s, s);
                    if(layoutManager) wrapButton->getParameter().trackVariable(&layoutManager->doWrap);
                }
                
                if(scrollbar) {
                    if(layoutManager) {// && !layoutManager->doWrap) {
                        // TODO: custom scrollbar layout
                        scrollbar->visible = true;
                        scrollbar->layout.set(0, 0, getConfig().layout.scrollbarWidth, ofGetHeight());
                        float sbheight = scrollbar->layout.height;
                        scrollbar->barThickness = sbheight / layoutManager->getCurRect().height;
                        layoutManager->scrollY = ofMap(scrollbar->getParameter().value(), 0, 1 - scrollbar->barThickness, 0, layoutManager->getCurRect().height - sbheight * 0.5);
                    } else {
                        scrollbar->visible = false;
                    }
                }
                


                if(titleButton->getParameter().value()) {
                    titleButton->getParameter().setTooltip("Collapse panel");
                    collapseAllButton->getParameter().setName("-");
                    collapseAllButton->getParameter().setTooltip("Collapse all panels");
                } else {
                    titleButton->getParameter().setTooltip("Expand panel");
                    collapseAllButton->getParameter().setName("+");
                    collapseAllButton->getParameter().setTooltip("Expand all panel");
                }
                
                if(collapseAllButton->getParameter().value()) showPanel(!titleButton->getParameter(), true);
                
                
                // Preset save load
                presetDropdown->visible = presetDropdown->enabled = presetManager.isOpen();

                // TODO: on mousemove, hilight the controls which would be affected
                
                // load preset
                if(loadButton->getParameter().value()) {
                    if(loadButton->getParameter().hasChanged()) {
                        presetManager.openLoad();
                    }
                    presetDropdown->layout.x = loadButton->layout.getRight();
                    if(presetDropdown->getParameter().hasChanged() || presetDropdown->isMousePressed()) paramT->loadXmlSchema(presetManager.getPresetName());
                }
                
                // save preset
                if(saveButton->getParameter().value()) {
                    if(saveButton->getParameter().hasChanged()) {
                        presetManager.openSave();
                    }
                    presetDropdown->layout.x = saveButton->layout.getRight();
                    if(presetDropdown->getParameter().hasChanged() || presetDropdown->isMousePressed()) {
                        paramT->saveXmlSchema(presetManager.getPresetName());
                        presetManager.close();
                    }
                }

                

//                if(loadButton->getParameter().value()) {
//                    ofFileDialogResult f = ofSystemLoadDialog("Load preset", false, ofToDataPath(""));
//                    if(f.bSuccess) {
//                        paramT->loadXmlValues(f.filePath);
//                    }
//                }
                
//                if(saveButton->getParameter().value()) {
//                    ofFileDialogResult f = ofSystemSaveDialog(getPath(), "Save preset");
//                    if(f.bSuccess) {
//                        paramT->saveXmlValues(f.getPath());
//                        //                            string path = ofFilePath::getEnclosingDirectory(f.getPath(), false);//f.filePath.substr(0, f.filePath.rfind("/"));
//                        //                            paramT->saveXml(false, path + "/" + getPath() + "-" + f.fileName + ".xml");
//                        //                            ofDirectory dir(path + "/" + getPath());
//                        //                            if(!dir.exists()) dir.create(true);
//                        //                            paramT->saveXml(false, dir.getAbsolutePath() + "/" + f.fileName + ".xml");
//                    }
//                }
            }
            
            
        }
    }
}
