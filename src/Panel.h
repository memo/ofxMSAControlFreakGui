#pragma once

#include "ofxMSAControlFreakGui/src/Container.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"

namespace msa {
    namespace ControlFreak {
        
        namespace gui {
            
            class Gui;
            class BoolButton;
            class BoolTitle;
            class BoolTitle;
            class BoolToggle;
            class ColorPicker;
            class DropdownList;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;

            class Panel;
            typedef std::tr1::shared_ptr<Panel> PanelPtr;

            class Panel : public Container {
            public:
                
                friend class BoolTitle;
                friend class Gui;
                friend class LayoutManager;
                
                Panel(Container *parent, string s);
                Panel(Container *parent, ParameterGroupPtr p);
                ~Panel();
                
            protected:
                bool isOpen;
                ParameterGroup *paramT;
                LayoutManagerPtr layoutManager;
                BoolTitle       *ptitleButton;   // button which controls the title of the panel

                void init();
                
                void showPanel(bool bOpen, bool bRecursive = false);
                
                void buttonPressed(int i);
                
                
                Panel           &addPanel(ParameterGroupPtr p);
                BoolButton		&addButton(ParameterPtr p);
                ColorPicker		&addColorPicker(ParameterPtr p);
                DropdownList&   addDropdownList(ParameterPtr p);
                Content			&addContent(ParameterPtr p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(ParameterPtr p);
                Slider2d		&addSlider2d(ParameterPtr p);
                SliderInt		&addSliderInt(ParameterPtr p);
                SliderFloat		&addSliderFloat(ParameterPtr p);
                BoolTitle		&addTitle(ParameterPtr p);
                BoolToggle		&addToggle(ParameterPtr p);
                
                void addParameter(ParameterPtr p);
                void addParameters(ParameterGroupPtr parameters);
            };
            
            
        }
    }
}