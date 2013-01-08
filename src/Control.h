#pragma once

#include "ofxMSAInteractiveObject/src/ofxMSAInteractiveObject.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Config;
            class Container;
            
//            class Control;
//            typedef std::tr1::shared_ptr<Control> ControlPtr;
            

            class Control : public ofxMSAInteractiveObject {
            public:
                
                friend class Container;
                friend class Renderer;
                
                int         z;  // draw order (0 draw last, i.e. drawn on top)
                bool		newColumn;
                char		keyboardShortcut;
                ofVec2f     scale;

                // if this is true, do autoLayout, otherwise use localRect (in relation to parent)
                bool        doAutoLayout;
                ofRectangle localRect;
                
                Control(Container *parent, Parameter* p, bool bOwnsParameter = false);
                ~Control();
                
                Control& setConfig(Config *config);
                Config &getConfig();
                
                Control& setNewColumn(bool b);
                
                Container *getParent();     // parent panel
                Container *getRoot(bool bUpdate = false);       // root panel
                
                int getDepth();         // how deep in the heirarchy it is (how many levels deep)
                bool isActive();       // whether the control is active or not
                bool getParentActive(); // whether any of the controls parents are active or not
                ofVec2f getScale();
                ofVec2f getInheritedScale();// inherited scale
                ofVec2f getParentScale();   // inherited scale of parent
                
                
                string getName();
                string getPath();
                
                Parameter& getParameter();
//                Control& setKeyboardShortcut(char c);
                
                // overrider these
                
                virtual void onUpdate() {}
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

            protected:
                
                
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
                void drawTextCentered(string s="", ofColor *c = NULL);
                ofRectangle getTextRect(int x=0, int y=0, string s = "");
                
                void update();
                void draw();
                
                
            private:
                float _alpha;
                Container *_pparent;
                Container *_proot;
                Config *_pconfig;
                Parameter *_pparameter;
                bool _bOwnsParameter;    // whether the control owns the parameter or not. TODO: this is a bit hackish?
//                bool _active;
                
                
                void setParent(Container *parent);
                void setParameter(Parameter *parameter, bool bOwner = false);
            };
            
            
        }
    }
}