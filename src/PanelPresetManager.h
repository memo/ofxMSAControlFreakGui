#pragma once

#include "ofxMSAControlFreakGui/src/Panel.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            
            class PanelPresetManager {
            private:
                friend class Panel;
                
                bool bLoadOpen;
                bool bSaveOpen;

                Panel *panel;
                ParameterNamedIndex *presetsNamedIndex;
                
                //--------------------------------------------------------------
                PanelPresetManager(Panel *panel) {
//                { panel = NULL; presetsNamedIndex = NULL; bLoadOpen = false; bSaveOpen = false; }
                //--------------------------------------------------------------
//                void setup() {
                    this->panel = panel;
                    presetsNamedIndex = NULL;//static_cast<ParameterNamedIndex*>(&panel->presetDropdown->getParameter());
                    bLoadOpen = false;
                    bSaveOpen = false;
                }
                
                //--------------------------------------------------------------
                bool isOpen() {
                    return bLoadOpen || bSaveOpen;
                }
                
                //--------------------------------------------------------------
                bool checkPresetsControl() {
                    if(!presetsNamedIndex && panel->presetDropdown) {
                        presetsNamedIndex = dynamic_cast<ParameterNamedIndex*>(&panel->presetDropdown->getParameter());
                    }
                    return presetsNamedIndex != NULL;
                    
                }
                
                //--------------------------------------------------------------
                void openLoad() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::openLoad";
                    checkPresetsControl();
                    bLoadOpen = true;
                    bSaveOpen = false;
                    presetsNamedIndex->clearLabels();
                    readDir();
                }
                
                //--------------------------------------------------------------
                void openSave() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::openSave";
                    checkPresetsControl();
                    bSaveOpen = true;
                    bLoadOpen = false;
                    presetsNamedIndex->clearLabels();
                    readDir();
                    presetsNamedIndex->addLabel("*** NEW ***");
                }

                //--------------------------------------------------------------
                void close() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::close";
                    bSaveOpen = false;
                    bLoadOpen = false;
                }

                //--------------------------------------------------------------
                void readDir() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::readDir";
                    checkPresetsControl();
                    
                    ofDirectory dir;
                    ParameterGroup *panelParams = dynamic_cast<ParameterGroup*>(&panel->getParameter());
                    if(panelParams) {
                        dir.listDir(panelParams->getPresetsDir());
                        for(int i=0; i<dir.size(); i++) {
                            // TODO: do format check here?
                            // TODO: only load presets which are relevant to that section?
                            presetsNamedIndex->addLabel(dir.getName(i));
                        }
                    } else {
                        ofLogError() << "msa::ControlFreak::gui::PanelPresetManager::readDir - no PanelParams";
                    }
                        
                }
                
                //--------------------------------------------------------------
                string getPresetName() {
                    checkPresetsControl();
                    string s;
                    if(bLoadOpen || (bSaveOpen && presetsNamedIndex->value() < presetsNamedIndex->getNumLabels()-1))
                        s = presetsNamedIndex->getSelectedLabel();
                    else s = ofSystemTextBoxDialog("enter preset name");
                    return s;
                }
                
            };
            
        }
    }
}