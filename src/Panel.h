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
                
                friend class Gui;
                friend class LayoutManager;
                
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
                
                void addParameter(Parameter *p);
                void addParameters(ParameterGroup &parameters);
                
            protected:
                float heightScale;              // height scale of this panel
                float getParentHeightScale();   // height scale of parent
                float getHeightScale();         // inherited height scale
                
                bool isOpen;
                void showPanel(bool bOpen, bool bRecursive = false);
                
                LayoutManagerPtr layoutManager;
                
                vector<ControlPtr> controls;    // all controls
                Control         *activeControl; // currently active control (only this control receives events)
                BoolTitle       *titleButton;   // button which controls the title of the panel

                
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
            };
            
            typedef std::tr1::shared_ptr<Panel> PanelPtr;
            
        }
    }
}