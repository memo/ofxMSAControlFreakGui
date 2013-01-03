#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            class Gui;
            class Panel;
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

            
            class Container : public Control {
            public:
                Container(Container *parent, string s);
                Container(Container *parent, ParameterPtr p);
                
                void clear();
                int getNumControls() const;
                Control* addControl(Control *control);
                Control* getControl(int i) const;
//                Control* operator[](int index);
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                Control* getActiveControl();
                
                
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

                
                
                // events from ofxMSAInteractiveObject
                void update();
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);

                
            private:
                vector<ControlPtr> _controls;
                Control *_pactiveControl; // currently active control (only this control receives events)
            };
            
        }
    }
}

