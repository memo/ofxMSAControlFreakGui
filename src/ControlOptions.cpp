
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"
#include "ofxMSAControlFreakGui/src/PanelPresetManager.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            ControlOptions::ControlOptions(Container *parent) : Container(parent, new Parameter("Control Options")) {
                disableAllEvents();
                width = 0;
                height = 0;
                
                layout.positionMode = LayoutSettings::kFixed;
                layout.doIncludeInContainerRect = false;
                
                titleButton = new BoolTitle(this, getName());
                titleButton->layout.positionMode = LayoutSettings::kAbsolute;
                titleButton->setZ(1e100);
                addControl(titleButton);
                
                snapButton = new BoolToggle(this, "snap");
                snapButton->layout.positionMode = LayoutSettings::kAbsolute;
                snapButton->setZ(2);
                addControl(snapButton);
                
                clampButton = new BoolToggle(this, "clamp");
                clampButton->layout.positionMode = LayoutSettings::kAbsolute;
                clampButton->setZ(1e100);
                addControl(clampButton);

                listenersDropdown = new OptionsDropdownList(this, "listeners");
                listenersDropdown->layout.positionMode = LayoutSettings::kAbsolute;
                listenersDropdown->layout.doIncludeInContainerRect = false;
                listenersDropdown->setZ(1e100);
                listenersDropdown->setMode(ParameterNamedIndex::kDropdown);
                addControl(listenersDropdown);
                
                sendersDropdown = new OptionsDropdownList(this, "senders");
                sendersDropdown->layout.positionMode = LayoutSettings::kAbsolute;
                sendersDropdown->layout.doIncludeInContainerRect = false;
                sendersDropdown->setZ(1e100);
                sendersDropdown->setMode(ParameterNamedIndex::kDropdown);
                addControl(sendersDropdown);
                
                show(NULL);
            }
            
            //--------------------------------------------------------------
            void ControlOptions::show(Control *targetControl) {
                this->targetControl = targetControl;
                visible = targetControl != NULL;
            }
            
            //--------------------------------------------------------------
            void ControlOptions::update() {
                Container::update();
                
                if(targetControl == NULL) return;
                
                // set positions and layout
                int s = titleButton->height * 0.7;
                int y = (titleButton->height - s)/2;
                int p = 3;
                
                layout.setPosition(getRight(), getBottom());
                
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
            
            
        }
    }
}
