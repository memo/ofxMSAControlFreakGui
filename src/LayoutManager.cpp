
#include "ofxMSAControlFreakGui/src/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //--------------------------------------------------------------
            LayoutManager::LayoutManager() {
                doWrap = false;
                scrollY = 0;
            }
            
            //--------------------------------------------------------------
            void LayoutManager::update(Panel &panel) {

                // how open is this panel
                float openSpeed = 0.1f;
                if(panel.ptitleButton->getParameter().getValue() != panel.isOpen) panel.showPanel(panel.ptitleButton->getParameter().getValue(), panel.ptitleButton->bRecursive);
                if(panel.isOpen) {
                    //                    if(heightScale<0.95) heightScale += (1-heightScale) * openSpeed;
                    if(panel.heightScale < 1) panel.heightScale += openSpeed;
                    else panel.heightScale = 1.0f;
                } else {
                    //                    if(heightScale > 0.05) heightScale += (0-heightScale) * openSpeed;
                    if(panel.heightScale > 0) panel.heightScale -= openSpeed;
                    else panel.heightScale = 0.0f;
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
                int numControls     = panel.getHeightScale() ? panel.controls.size() : 1;
                float heightMult    = panel.getHeightScale();//i ? getHeightScale() : getParentHeightScale();
                
                for(int i=0; i<numControls; i++) {
                    Control& control = *panel.controls[i];
                    
                    control.setConfig(&config);
                    
                    int indent = i==0 ? panelDepth * config.layout.indent : (panelDepth+1) * config.layout.indent;
                    
                    // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
                    if(control.newColumn || (doWrap && curPos.y + (control.height + config.layout.padding.y) * heightMult > maxPos.y)) {
                        curPos.x = rect.x + rect.width + config.layout.padding.x;
                        curPos.y = maxRect.y;
                    }
                    
                    control.setWidth(config.layout.columnWidth - indent);
                    control.setPosition(curPos.x + indent, curPos.y - scrollY);
                    Renderer::instance().addControl(&control);
                    rect.growToInclude((ofRectangle&)control);
                    
                    Panel *p = dynamic_cast<Panel*>(&control);
                    if(p) update(*p);
                    
                    curPos.y += (control.height + config.layout.padding.y) * heightMult;
                }
                
                // add some padding at end of group
                curPos.y += config.layout.buttonHeight;// * getParentHeightScale();
                
                panel.set(*panel.ptitleButton);
            }
            
            //--------------------------------------------------------------
            void LayoutManager::draw(Config &config) {
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