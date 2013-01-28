
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"
#include "ofxMSAControlFreakGui/src/PanelPresetManager.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            ControlOptions::ControlOptions(Container *parent) : Container(parent, new Parameter("Control Options")) {
                layout.positionMode = LayoutSettings::kFixed;
                layout.doIncludeInContainerRect = false;
                
                addControl(titleButton = new BoolTitle(this, getName()));
                titleButton->enabled = false;
                
                addControl(snapButton = new BoolToggle(this, "snap"));
                addControl(clampButton = new BoolToggle(this, "clamp"));
                
                string controllerNames[] = {"<add MIDI>", "<add OSC>", "<add DMX>" };
                listenersParam = new ParameterNamedIndex("listeners");
                listenersParam->setLabels(3, controllerNames);
                listenersParam->setClamp(false);
                listenersParam->set(-1);
                addControl(listenersDropdown = new OptionsDropdownList(this, listenersParam));
                
                sendersParam = new ParameterNamedIndex("senders");
                sendersParam->setLabels(3, controllerNames);
                sendersParam->setClamp(false);
                sendersParam->set(-1);
                addControl(sendersDropdown = new OptionsDropdownList(this, sendersParam));
                
                show(NULL);
            }
            
            //--------------------------------------------------------------
            void ControlOptions::onPressOutside(int x, int y, int button) {
//                show(NULL);
            }
            
            //--------------------------------------------------------------
            void ControlOptions::show(Control *targetControl) {
                this->_pTargetControl = this->_pTargetControl == targetControl ? NULL : targetControl;  // if sending the same one, set to NULL to close
                visible = _pTargetControl != NULL;
                if(_pTargetControl) {
                    titleButton->getParameter().setName(_pTargetControl->getName());
                    snapButton->getParameter() = _pTargetControl->getParameter().getSnap();
                    clampButton->getParameter() = _pTargetControl->getParameter().getClamp();
                }
            }
            
            //--------------------------------------------------------------
            void ControlOptions::update() {
                Container::update();
                
                if(_pTargetControl == NULL) return;
                
                // set positions and layout
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                layout.setPosition(_pTargetControl->getRight() + 10, min(_pTargetControl->getCenter().y, ofGetHeight() - height));
                
                if(snapButton->getParameter().hasChanged()) _pTargetControl->getParameter().setSnap(snapButton->getParameter());
                if(clampButton->getParameter().hasChanged()) _pTargetControl->getParameter().setClamp(clampButton->getParameter());
                
                if(listenersParam->hasChanged()) {
                    // if 'add' is selected, bring up appropiate dialog
                    // if another one is selected, bring up edit dialog
                    listenersParam->set(-1);
                }
                
                if(sendersParam->hasChanged()) {
                    sendersParam->set(-1);
                }

                
//                collapseAllButton->layout.set(p, y, s, s);
//                saveButton->layout.set(titleButton->width - (s + p) * 2, y, s, s);
//                loadButton->layout.set(titleButton->width - (s + p), y, s, s);
//                presetDropdown->layout.set(0, loadButton->layout.getBottom(), titleButton->width*1.5, titleButton->height);
//                
//                
//                if(titleButton->getParameter().value()) {
//                    titleButton->getParameter().setTooltip("Collapse panel");
//                    collapseAllButton->getParameter().setName("-");
//                    collapseAllButton->getParameter().setTooltip("Collapse all panels");
//                } else {
//                    titleButton->getParameter().setTooltip("Expand panel");
//                    collapseAllButton->getParameter().setName("+");
//                    collapseAllButton->getParameter().setTooltip("Expand all panel");
//                }
//                
//                if(collapseAllButton->getParameter().value()) showPanel(!titleButton->getParameter(), true);
//                
//                
//                // Preset save load
//                presetDropdown->visible = presetDropdown->enabled = presetManager->isOpen();
//                
//                // TODO: on mousemove, hilight the controls which would be affected
//                
//                // load preset
//                if(loadButton->getParameter().value()) {
//                    if(loadButton->getParameter().hasChanged()) {
//                        presetManager->openLoad();
//                    }
//                    presetDropdown->layout.x = loadButton->layout.getRight();
//                    if(presetDropdown->getParameter().hasChanged() || presetDropdown->isMousePressed()) targetParam->loadXmlSchema(presetManager->getPresetName());
//                }
//                
//                // save preset
//                if(saveButton->getParameter().value()) {
//                    if(saveButton->getParameter().hasChanged()) {
//                        presetManager->openSave();
//                    }
//                    presetDropdown->layout.x = saveButton->layout.getRight();
//                    if(presetDropdown->getParameter().hasChanged() || presetDropdown->isMousePressed()) {
//                        targetParam->saveXmlSchema(presetManager->getPresetName());
//                        presetManager->close();
//                    }
//                }
                
            }
            
            //--------------------------------------------------------------
            void ControlOptions::draw() {
                if(_pTargetControl) {
                    ofSetLineWidth(1);
                    ofSetColor(255, 0, 0);
                    ofLine(0, 0, _pTargetControl->getRight() - x, _pTargetControl->getCenter().y - y);
                }
                
            }
            
            
        }
    }
}
