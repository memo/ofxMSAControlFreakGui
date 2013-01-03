#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Container : public Control {
            public:
                
//                friend class Control;
                
                Container(Container *parent, ParameterPtr p);
                
                void clear();
                int getNumControls() const;
                Control* addControl(Control *control);
                Control* getControl(int i) const;
//                Control* operator[](int index);
                
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

                
            private:
                vector<ControlPtr> _controls;
                Control *_pactiveControl; // currently active control (only this control receives events)
            };
            
        }
    }
}

