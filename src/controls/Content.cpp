
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Content::Content(Container *parent, Parameter* p, ofBaseDraws& content, float fixwidth) : Control(parent, p) {
                this->content = &content;
                this->fixwidth  = fixwidth;
                setup();
            }
            
            void Content::setup() {
                fixheight = fixwidth * content->getHeight()/content->getWidth();
                width = fixwidth;
                height = fixheight + pconfig->layout.buttonHeight;
            }
            
            void Content::draw() {
                if(content == NULL) return;
                
                if(content->getWidth() == 0 && content->getHeight() ==0) return;
                
                setup();
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                ofEnableAlphaBlending();
                ofFill();
                glColor4f(0, 0, 0, 0.8f);
                ofRect(0, 0, width, fixheight);
                
                ofSetHexColor(0xffffff);
                content->draw(0, 0, width, fixheight);
                
                ofFill();
                setBGColor();
                ofRect(0, fixheight, width, pconfig->layout.buttonHeight);
                
                setTextColor();
                pconfig->drawString(getName(), 3, fixheight + 15);
                ofDisableAlphaBlending();
                glPopMatrix();
            }
            
        }
    }
}