#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase;
            class OptionsBase;
            
            class ControlOptions;
            typedef std::tr1::shared_ptr<ControlOptions> ControlOptionsPtr;

            class ControlOptions : public Container {
            public:
                friend class Gui;
                
                ControlOptions(Container *parent);
                
                void update();
                void show(Control *targetControl);
                
            protected:
                Control  *targetControl;
                
                BoolBase *titleButton;   // button which controls the title
                BoolBase *snapButton;
                BoolBase *clampButton;
                OptionsBase *listenersDropdown;
                OptionsBase *sendersDropdown;
            };
            
            
        }
    }
}