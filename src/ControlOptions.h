#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase;
            class OptionsBase;
            
            class ControlProperties : public Container {
            public:
                friend class Gui;
                
                ControlProperties(Container *parent);
                
                void update();
                void draw();
                
                void show(Control *_pTargetControl);
                
                void onPressOutside(int x, int y, int button);

                
            protected:
                Control  *_pTargetControl;
                
                BoolBase *titleButton;   // button which controls the title
                BoolBase *snapButton;
                BoolBase *clampButton;
                OptionsBase *listenersDropdown;
                OptionsBase *sendersDropdown;
                
                ParameterNamedIndex *listenersParam;
                ParameterNamedIndex *sendersParam;
            };
            
            
        }
    }
}