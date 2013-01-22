#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"
//#include "ofxMSAControlFreakGui/src/PanelPresetManager.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            class BoolBase;
//            class BoolTitle;
//            class BoolSimpleBox;
//            class BoolSimpleCircle;
//            class BoolToggle;
            class ColorPicker;
            class DropdownList;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class ScrollBar;
            class Slider2d;
            class SliderInt;
            class SliderFloat;
            
            class PanelPresetManager;

//            class Panel;
//            typedef std::tr1::shared_ptr<Panel> PanelPtr;

            class Panel : public Container {
            public:
                
                friend class BoolTitle;
                friend class Gui;
                friend class LayoutManager;
                friend class PanelPresetManager;
                
                Container *children;

                //                Panel(Container *parent, string s);
                Panel(Container *parent, ParameterGroup* p);
                Panel(Gui *parent, ParameterGroup* p);
                ~Panel();
                
                void onUpdate();
                
                void showPanel(bool bOpen, bool bRecursive = false);

            protected:
                Gui *pgui;
                ParameterGroup  *paramT;
                LayoutManager* layoutManager;
                
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