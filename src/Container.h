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
            class Renderer;

            
            class Container : public Control {
            public:
                
                friend class Control;
                friend class Renderer;
                
                Container(Container *parent, string s);
                Container(Container *parent, Parameter* p);
                ~Container();
                
                void clear();
                int getNumControls() const;
                Control* addControl(Control *control);
                Control* getControl(int i) const;
                Control* operator[](int index);
//                Control* operator[](string index);
                
                
                Panel           &addPanel(ParameterGroup* p);
                BoolButton		&addButton(Parameter* p);
                ColorPicker		&addColorPicker(Parameter* p);
                DropdownList&   addDropdownList(Parameter* p);
                Content			&addContent(Parameter* p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(Parameter* p);
                Slider2d		&addSlider2d(Parameter* p);
                SliderInt		&addSliderInt(Parameter* p);
                SliderFloat		&addSliderFloat(Parameter* p);
                BoolTitle		&addTitle(Parameter* p);
                BoolToggle		&addToggle(Parameter* p);
                
                void addParameter(Parameter* p);
                void addParameters(ParameterGroup* parameters);
                
                
                // events from ofxMSAInteractiveObject
                void update();
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);

                
                Control* getActiveControl();
                
            private:
                vector<Control*> _controls;
                Control *_pactiveControl; // currently active control (only this control receives events)

                void setActiveControl(Control *control);
                void releaseActiveControl();
            };
            
        }
    }
}

