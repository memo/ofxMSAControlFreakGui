#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Container : public Control {
            public:
                
                friend class Control;
                
                Container();
                
                void clear();
                int size() const;
                Control* add(Control *control);
                Control* get(int i) const;
                Control* operator[](int index);
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                Control* getActiveControl();
                
            private:
                vector<ControlPtr> _controls;
                Control *_pactiveControl; // currently active control (only this control receives events)
            };
            
        }
    }
}

