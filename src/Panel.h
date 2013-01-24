#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase;
            class LayoutManager;
            class PanelPresetManager;

            class Panel : public Container {
            public:
                
                friend class LayoutManager;
                friend class PanelPresetManager;
                friend class Gui;
                
                Container *children;

                Panel(Container *parent, ParameterGroup* p, bool bInitOnCreation);
                
                void update();
                void showPanel(bool bOpen, bool bRecursive = false);

            protected:
                ParameterGroup  *paramT;
                
                BoolBase *titleButton;   // button which controls the title of the panel
                BoolBase *collapseAllButton;
                BoolBase *loadButton;
                BoolBase *saveButton;
                List *presetDropdown;
                
                PanelPresetManager *presetManager;
                
                void init();
            };
            
            
        }
    }
}