#pragma once

#include "ofxMSAControlFreakGui/src/ControlParameterT.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"

namespace msa {
    namespace ControlFreak {
        
        class Parameter;
        class ParameterGroup;
        
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
            
            class Panel : public ControlParameterT<ParameterGroup> {
            public:
                
                friend class BoolTitle;
                friend class Gui;
                friend class LayoutManager;
                
                Panel(Panel *parent, string s);
                Panel(Panel *parent, Parameter *p);
                ~Panel();
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                Control* getActiveControl();
                
                void update();
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);
//                vector<ControlPtr>&	getControls();
                
            protected:
                bool isOpen;
                float heightScale;              // height scale of this panel
                LayoutManagerPtr layoutManager;
                vector<ControlPtr> controls;    // all controls
                Control         *pactiveControl; // currently active control (only this control receives events)
                BoolTitle       *ptitleButton;   // button which controls the title of the panel

                void init();
                float getParentHeightScale();   // height scale of parent
                float getHeightScale();         // inherited height scale
                
                void showPanel(bool bOpen, bool bRecursive = false);
                
                void buttonPressed(int i);
                
                
                Control			&addControl(Control *control);
                
                Panel           &addPanel(Parameter *p);
                BoolButton		&addButton(Parameter *p);
                ColorPicker		&addColorPicker(Parameter *p);
                DropdownList&   addDropdownList(Parameter *p);
                Content			&addContent(Parameter *p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(Parameter *p);
                Slider2d		&addSlider2d(Parameter *p);
                SliderInt		&addSliderInt(Parameter *p);
                SliderFloat		&addSliderFloat(Parameter *p);
                BoolTitle		&addTitle(Parameter *p);
                BoolToggle		&addToggle(Parameter *p);
                
                void addParameter(Parameter *p);
                void addParameters(ParameterGroup &parameters);
            };
            
            typedef std::tr1::shared_ptr<Panel> PanelPtr;
            
        }
    }
}