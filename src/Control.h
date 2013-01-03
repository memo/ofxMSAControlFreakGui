#pragma once

#include "ofxMSAInteractiveObject/src/ofxMSAInteractiveObject.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Config;
            class Container;
            
            class Control;
            typedef std::tr1::shared_ptr<Control> ControlPtr;
            

            class Control : public ofxMSAInteractiveObject {
            public:
                
                friend class Container;
                
                int         z;  // draw order (0 draw last, i.e. drawn on top)
                bool		newColumn;
                char		keyboardShortcut;
                ofVec2f     scale;
                bool        doAutoLayout;
                
                // if this is set (i.e. nonzero), override auto-layout and set position and size in relation to parent
                ofRectangle localRect;
                
                Control(Container *parent, ParameterPtr p);
                
                Control& setConfig(Config *config);
                Config &getConfig();
                
                Control& setNewColumn(bool b);
                
                Container *getParent();     // parent panel
                Container *getRoot(bool bUpdate = false);       // root panel
                
                int getDepth();         // how deep in the heirarchy it is (how many levels deep)
                bool isActive();       // whether the control is active or not
                bool getParentActive(); // whether any of the controls parents are active or not
                ofVec2f getInheritedScale();// inherited scale
                ofVec2f getParentScale();   // scale of parent
                
                
                string getName();
                string getPath();
                
                ParameterPtr getParameter();
                
                // 0: normal, 1:over, 2:active
                int getState();
                
                ofColor setColor(ofColor c);
                ofColor setColor(ofColor *c);
                ofColor setBGColor();
                ofColor setTextColor();
                ofColor setSliderColor(bool b);
                ofColor setToggleColor(bool b);
                ofColor setBorderColor();
                
                bool doTooltip(int millis = -1);
                void setTooltip(string s="");
                
                void drawBorder(ofColor *c = NULL);
                void drawText(int x, int y, string s = "", ofColor *c = NULL);
                void draw();
                
                
                Control& setKeyboardShortcut(char c);
                
                virtual void onDraw() {}
                
                virtual void onKeyUp() {}			// up key is pressed
                virtual void onKeyDown() {}			// down key is pressed
                virtual void onKeyLeft() {}			// left key is pressed
                virtual void onKeyRight() {}		// right key is pressed
                virtual void onKeyEnter() {}		// enter key is pressed
                
                
                // from ofxMSAInteractiveObject
                virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
                virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
                virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
                virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down
                virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
                virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
                virtual void onPressOutside(int x, int y, int button)	{}		// called when mouse presses while outside object
                virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
                virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object
                
                virtual void keyPressed( int key ){}
                virtual void keyReleased( int key ){}
                
            private:
                Container *_pparent;
                Container *_proot;
                Config *_pconfig;
                float _alpha;
                bool _active;
                
                ParameterPtr _parameter;
                bool parameterOwner;
                
                void setParent(Container *parent);
                void setParameter(ParameterPtr parameter);
            };
            
            
        }
    }
}