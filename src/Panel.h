//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreakGui
//

#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"

namespace msa {
    namespace controlfreak {
        namespace gui {
            
            class BoolBase;
            class LayoutManager;
            class PanelPresetManager;
            class OptionsBase;

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
                OptionsBase *presetDropdown;
                
                PanelPresetManager *presetManager;
                
                void init();
            };
            
            
        }
    }
}