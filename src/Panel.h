#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
//#include "ofxMSAControlFreakGui/src/PanelPresetManager.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolBase;
            class ColorPicker;
            class DropdownList;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class ScrollBar;
            class Slider2d;
            class SliderInt;
            class SliderFloat;

            class LayoutManager;
            
            class PanelPresetManager;

            class Panel : public Container {
            public:
                
                friend class BoolTitle;
                friend class LayoutManager;
                friend class PanelPresetManager;
                
                Container *children;

                Panel(Container *parent, ParameterGroup* p);
                
                void onUpdate();
                void showPanel(bool bOpen, bool bRecursive = false);

            protected:
                ParameterGroup  *paramT;
                
                BoolBase *titleButton;   // button which controls the title of the panel
                BoolBase *collapseAllButton;
                BoolBase *loadButton;
                BoolBase *saveButton;
                BoolBase *wrapButton;
                BoolBase *prevPageButton;
                BoolBase *nextPageButton;
                ScrollBar *scrollbar;
                List *presetDropdown;
                
                PanelPresetManager *presetManager;
                
                void init();
            };
            
            
        }
    }
}