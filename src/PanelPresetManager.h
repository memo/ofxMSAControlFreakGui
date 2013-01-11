#pragma once

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            
            class PanelPresetManager {
            private:
                friend class Panel;
                
                bool bLoadOpen;
                bool bSaveOpen;

                ParameterNamedIndex *presetsNamedIndex;
                
                //--------------------------------------------------------------
                PanelPresetManager() { presetsNamedIndex = NULL; bLoadOpen = false; bSaveOpen = false; }
                
                //--------------------------------------------------------------
                void setup(Parameter &parameter) {
                    presetsNamedIndex = static_cast<ParameterNamedIndex*>(&parameter);
                }
                
                //--------------------------------------------------------------
                bool isOpen() {
                    return bLoadOpen || bSaveOpen;
                }
                
                //--------------------------------------------------------------
                void openLoad() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::openLoad";
                    bLoadOpen = true;
                    bSaveOpen = false;
                    presetsNamedIndex->clearLabels();
                    readDir();
                }
                
                //--------------------------------------------------------------
                void openSave() {
                    ofLogNotice() << "msa::ControlFreak::gui::PanelPresetManager::openSave";
                    bSaveOpen = true;
                    bLoadOpen = false;
                    presetsNamedIndex->clearLabels();
                    presetsNamedIndex->addLabel("*** new ***");
                    readDir();
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
                    
                    ofDirectory dir;
                    dir.listDir("presets");
//                    printf("size = %i\n", dir.size());
                    for(int i=0; i<dir.size(); i++) {
                        //                        printf("%i %s\n", i, dir.getName(i).c_str());
                        // TODO: do format check here?
                        // TODO: only load presets which are relevant to that section?
                        presetsNamedIndex->addLabel(dir.getName(i));
                    }
                }
                
                //--------------------------------------------------------------
                string getPresetName() {
                    return "presets/" + presetsNamedIndex->getSelectedLabel();
                }
                
            };
            
        }
    }
}