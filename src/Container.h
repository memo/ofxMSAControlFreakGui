#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAOrderedPointerMap/src/ofxMSAOrderedPointerMap.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            class Panel;
            class BoolButton;
            class BoolTitle;
            class BoolToggle;
            class ColorPicker;
            class Content;
            class DropdownList;
            class List;
            class Options;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;

            
            class Container : public Control {
            public:
                
                friend class Panel;
                
                Container(Container *parent, string s);
                Container(Container *parent, Parameter* p, bool bOwnsParameter = false);
                ~Container();
                
                void clear();

                // adding
                Panel           &addPanel(ParameterGroup& p);
                BoolButton		&addButton(ParameterBool& p);
                ColorPicker		&addColorPicker(Parameter& p);
                DropdownList&   addDropdownList(ParameterNamedIndex& p);
                List&           addList(ParameterNamedIndex& p);
                Options&        addOptions(ParameterNamedIndex& p);
                Content			&addContent(Parameter& p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(Parameter& p);
                Slider2d		&addSlider2d(Parameter& p);
                SliderInt		&addSliderInt(ParameterInt& p);
                SliderFloat		&addSliderFloat(ParameterFloat& p);
                BoolToggle		&addToggle(ParameterBool& p);

                
                Control& addControl(Control *control);

                
                // accessing
                int getNumControls() const;

                Control& get(int index) const;
                Control& get(string name) const;
                Control& operator[](int index) const;
                Control& operator[](string name) const;
 
                
                // events from ofxMSAInteractiveObject
                void update();
                void mouseMoved(int x, int y);
                void mousePressed(int x, int y, int button);
                void mouseDragged(int x, int y, int button);
                void mouseReleased(int x, int y, int button);
                void keyPressed(int key);
                void keyReleased(int key);

                
            private:
                OrderedPointerMap<string, Control> _controls;
                
                void addParameter(Parameter& p);
                void addParameterChildren(ParameterGroup& parameters);
            };
            
        }
    }
}

