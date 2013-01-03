
#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            LayoutManager::LayoutManager() {
                doWrap = true;  // TODO: finish wrapping and scrolling
                scrollY = 0;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::prepareForDraw(Panel &panel) {

                // how open is this panel
                float openSpeed = 0.1f;
//                if(panel.ptitleButton->getParameter().getValue() != panel.isOpen) panel.showPanel(panel.ptitleButton->getParameter().getValue(), panel.ptitleButton->bRecursive); // TODO
                if(panel.isOpen) {
                    //                    if(scale.y<0.95) scale.y += (1-scale.y) * openSpeed;
                    if(panel.scale.y < 1) panel.scale.y += openSpeed;
                    else panel.scale.y = 1.0f;
                } else {
                    //                    if(scale.y > 0.05) scale.y += (0-scale.y) * openSpeed;
                    if(panel.scale.y > 0) panel.scale.y -= openSpeed;
                    else panel.scale.y = 0.0f;
                }
                
                // if we are drawing this Panel inside another Panel, use auto-layout parameters of that
//                if(panel.getParent()) layoutManager = panel.getParent()->layoutManager;
                
                panel.ptitleButton->z = -10000;
                Config &config      = panel.getConfig();
                ofVec2f maxPos      = getMaxPos();
                curPos              = clampPoint(curPos);
                panel.position      = curPos;
                panel.width         = 0;
                panel.height        = 0;
                int panelDepth      = panel.getDepth();// * config.layout.indent;
                int numControls     = panel.children.size();//panel.getInheritedScale().y ? panel.children.size() : 1;
                ofVec2f scale       = panel.getInheritedScale();//i ? getInheritedScale().y : getParentHeightScale();
                
                for(int i=0; i<numControls; i++) {
                    Control& control = *panel.children[i];
                    
                    control.setConfig(&config);
                    
                    int indent = i==0 ? panelDepth * config.layout.indent : (panelDepth+1) * config.layout.indent;
                    
                    // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
                    if(control.newColumn || (doWrap && curPos.y + (control.height + config.layout.padding.y) * scale.y > maxPos.y)) {
                        curPos.x = rect.x + rect.width + config.layout.padding.x;
                        curPos.y = maxRect.y;
                    }
                    
                    control.setWidth(config.layout.columnWidth - indent);
                    control.setPosition(curPos.x + indent, curPos.y - scrollY);
                    Renderer::instance().addControl(&control);

                    ofLogVerbose() << "layout " << curPos << " " << control.getPath() << " " << control.x << " " << control.y << " " << control.width  << " " << control.height;
                    
                    
                    rect.growToInclude((ofRectangle&)control);
                    
                    Panel *p = dynamic_cast<Panel*>(&control);
                    if(p) prepareForDraw(*p);
                    
                    curPos.y += (control.height + config.layout.padding.y) * scale.y;
                    
                }
                
                // add some padding at end of group
//                curPos.y += config.layout.buttonHeight;// * getParentHeightScale();
                
                panel.set(*panel.ptitleButton);
            }
            
            //--------------------------------------------------------------
            void LayoutManager::draw(Config &config) {
                return;
                
                ofPushStyle();
                
                ofSetLineWidth(1);
                
                ofFill();
                ofSetColor(config.colors.slider.full[0]);
                int by = ofMap(scrollY, rect.y, rect.y + rect.height, 2, ofGetHeight()-4);
                int bh = ofMap(ofGetHeight(), 0, rect.height, 2, ofGetHeight()-4);
                ofRect(2, by, config.layout.padding.x-4, bh);
                
                ofNoFill();
                ofSetColor(config.colors.border[0]);
                ofRect(2, 2, config.layout.padding.x-4, ofGetHeight()-4);
                
                ofPopStyle();
            }

            
            //--------------------------------------------------------------
            ofVec2f LayoutManager::getMaxPos() {
                return ofVec2f(maxRect.width ? maxRect.x + maxRect.width : ofGetWidth(), maxRect.height ? maxRect.y + maxRect.height : ofGetHeight());
            }
            
            //--------------------------------------------------------------
            ofVec2f LayoutManager::clampPoint(ofVec2f p) {
                ofVec2f maxPos(getMaxPos());
                return ofVec2f(ofClamp(p.x, maxRect.getLeft(), maxPos.x), ofClamp(p.y, maxRect.getTop(), maxPos.y));
            }
            
            
        }
    }
}