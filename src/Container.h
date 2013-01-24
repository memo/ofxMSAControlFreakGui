#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAOrderedPointerMap/src/ofxMSAOrderedPointerMap.h"
#include "ofxMSAControlFreakGui/src/LayoutManager.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            class Gui;
            class Panel;
            class Page;
            class BoolButton;
            class BoolTitle;
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
            class Renderer;

            
            class Container : public Control {
            public:
                
                friend class Control;
                friend class Renderer;
                
                Container(Container *parent, string s);
                Container(Container *parent, Parameter* p, bool bOwnsParameter = false);
                ~Container();
                
                void clear();

                // adding
                Panel           &addPanel(ParameterGroup* p);
                BoolButton		&addButton(ParameterBool* p);
                ColorPicker		&addColorPicker(Parameter* p);
                DropdownList&   addDropdownList(ParameterNamedIndex* p);
                List&           addList(ParameterNamedIndex* p);
                Options&        addOptions(ParameterNamedIndex* p);
                Content			&addContent(Parameter* p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(Parameter* p);
                Slider2d		&addSlider2d(Parameter* p);
                SliderInt		&addSliderInt(ParameterInt* p);
                SliderFloat		&addSliderFloat(ParameterFloat* p);
                BoolToggle		&addToggle(ParameterBool* p);

                void addParameters(ParameterGroup* parameters);
                
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

                
                Control* getActiveControl();
                

            protected:
                LayoutManagerPtr layoutManager;

            private:
                OrderedPointerMap<string, Control> _controls;
                
                Control *_pactiveControl; // currently active control (only this control receives events)
                void setActiveControl(Control *control);
                void releaseActiveControl();
            
                
                
                void addParameter(Parameter* p);
            };
            
        }
    }
}

