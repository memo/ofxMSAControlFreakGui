#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"

namespace msa {
    namespace ControlFreak {
        
        namespace gui {
            
            class Gui;
            class BoolButton;
            class BoolTitle;
            class BoolSimpleBox;
            class BoolSimpleCircle;
            class BoolToggle;
            class ColorPicker;
            class DropdownList;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;

//            class Panel;
//            typedef std::tr1::shared_ptr<Panel> PanelPtr;

            class Panel : public Container {
            public:
                
                friend class BoolTitle;
                friend class Gui;
                friend class LayoutManager;
                
//                Panel(Container *parent, string s);
                Panel(Container *parent, ParameterGroup* p);
                ~Panel();
                
                void onUpdate();
                
            protected:
                bool isOpen;
                ParameterGroup  *paramT;
                LayoutManager* layoutManager;
                
                BoolTitle       *titleButton;   // button which controls the title of the panel
//                BoolSimpleCircle *expandAllButton;
                BoolSimpleCircle *collapseAllButton;
                BoolSimpleCircle *loadButton;
                BoolSimpleCircle *saveButton;
                Container       *children;
                
                void init();
                
                void showPanel(bool bOpen, bool bRecursive = false);
            };
            
            
        }
    }
}