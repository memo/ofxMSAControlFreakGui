#pragma once

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            
            class PanelPresetManager {
            private:
                friend class Panel;

                ParameterNamedIndex *presetsNamedIndex;
                
                //--------------------------------------------------------------
                PanelPresetManager() {}
                
                //--------------------------------------------------------------
                void setup(Parameter &parameter) {
                    presetsNamedIndex = static_cast<ParameterNamedIndex*>(&parameter);
                }
                
                //--------------------------------------------------------------
                void fill() {
                    presetsNamedIndex->clearLabels();
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
                string getCurrentPreset() {
                    return "presets/" + presetsNamedIndex->getSelectedLabel();
                }
                
            };
            
        }
    }
}