
#include "ofxMSAControlFreakGui/src/Gui.h"
#include "ofxMSAControlFreakGui/src/Includes.h"



namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //            Gui gui;
            
            //--------------------------------------------------------------
            Gui::Gui() {
                isSetup = false;
                doAutoEvents = false;
                eventsAreRegistered = false;
                doDefaultKeys = false;
                currentPageIndex = false;
                doDraw = false;
            }
            
            //--------------------------------------------------------------
            void Gui::setup() {
                isSetup = true;
                ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
            }
            
            //--------------------------------------------------------------
            void Gui::addListeners() {
                if(!eventsAreRegistered) {
                    eventsAreRegistered = true;
                    //	ofAddListener(ofEvents().setup, this, &Gui::setup);
                    ofAddListener(ofEvents().update, this, &Gui::update);
                    ofAddListener(ofEvents().draw, this, &Gui::draw);
                    //	ofAddListener(ofEvents().exit, this, &Gui::exit);
                    
                    ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
                    ofAddListener(ofEvents().mouseMoved, this, &Gui::mouseMoved);
                    ofAddListener(ofEvents().mouseDragged, this, &Gui::mouseDragged);
                    ofAddListener(ofEvents().mouseReleased, this, &Gui::mouseReleased);
                    
                    //	ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
                    ofAddListener(ofEvents().keyReleased, this, &Gui::keyReleased);
                }
            }
            
            
            //--------------------------------------------------------------
            void Gui::removeListeners() {
                if(eventsAreRegistered) {
                    eventsAreRegistered = false;
                    //	ofRemoveListener(ofEvents().setup, this, &Gui::setup);
                    ofRemoveListener(ofEvents().update, this, &Gui::update);
                    ofRemoveListener(ofEvents().draw, this, &Gui::draw);
                    //	ofRemoveListener(ofEvents().exit, this, &Gui::exit);
                    
                    ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
                    ofRemoveListener(ofEvents().mouseMoved, this, &Gui::mouseMoved);
                    ofRemoveListener(ofEvents().mouseDragged, this, &Gui::mouseDragged);
                    ofRemoveListener(ofEvents().mouseReleased, this, &Gui::mouseReleased);
                    
                    //	ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
                    ofRemoveListener(ofEvents().keyReleased, this, &Gui::keyReleased);
                }
            }
            
            //--------------------------------------------------------------
            void Gui::setDraw(bool b) {
                doDraw = b;
                if(doDraw) addListeners();
                else removeListeners();
            }
            
            //--------------------------------------------------------------
            void Gui::show() {
                setDraw(true);
            }
            
            //--------------------------------------------------------------
            void Gui::hide() {
                setDraw(false);
            }
            
            //--------------------------------------------------------------
            void Gui::toggleDraw() {
                setDraw(!doDraw);
            }
            
            //--------------------------------------------------------------
            bool Gui::isOn() {
                return doDraw;
            }

            //--------------------------------------------------------------
            void Gui::setDefaultKeys(bool b) {
                doDefaultKeys = b;
            }
            
            //--------------------------------------------------------------
            void Gui::nextPage() {
                setPage(currentPageIndex + 1);
            }
            
            //--------------------------------------------------------------
            void Gui::prevPage() {
                setPage(currentPageIndex - 1);
            }
            
            //--------------------------------------------------------------
            void Gui::nextPageWithBlank() {
                if(doDraw) {
                    setPage(currentPageIndex + 1);
                    if(currentPageIndex == 1) setDraw(false);
                } else {
                    setDraw(true);
                    setPage(1);
                }
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(int i) {
                currentPageIndex = i;
                if(currentPageIndex >= pages.size()) currentPageIndex = 1;
                else if(currentPageIndex < 1) currentPageIndex = pages.size()-1;
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(string name) {
                // TODO
            }
            
            //--------------------------------------------------------------
            int Gui::getNumPages() {
                return pages.size();
            }
            
            //--------------------------------------------------------------
            Panel& Gui::getPage(int i) {
                if(!isSetup) setup();
                return *pages.at(i);
            }
            
            //--------------------------------------------------------------
            Panel& Gui::getPage(string name) {
                if(!isSetup) setup();
                for(int i=1; i<pages.size(); i++) if(name.compare(pages[i]->getName()) == 0) return *pages[i];
            }
            
            //--------------------------------------------------------------
            Panel& Gui::getCurrentPage() {
                return getPage(currentPageIndex);
            }
            
            //--------------------------------------------------------------
//            Panel& Gui::addPage(string name) {
//                PanelPtr panel(new Panel(NULL, name));
//                return addPanel(panel);
//            }

            //--------------------------------------------------------------
            Panel& Gui::addPage(ParameterGroupPtr parameters) {
                PanelPtr panel(new Panel(NULL, parameters));
                return addPanel(panel);
            }

            //--------------------------------------------------------------
            Panel& Gui::addPanel(PanelPtr page) {
                if(!isSetup) setup();
                
                pages.push_back(page);
                page->setConfig(&config);
                setPage(pages.size() - 1);
                return *page;
            }

            //--------------------------------------------------------------
//            Panel& Gui::addParameters(ParameterGroupPtr parameters) {
//                if(!isSetup) setup();
//                if(getNumPages() == 0) addPage(parameters);
//                else getCurrentPage().addParameters(parameters);
//                return getCurrentPage();
//            }
            
            
            //--------------------------------------------------------------
            void Gui::enableAutoEvents() {
                doAutoEvents = true;
                setDraw(doDraw); // add or remove listeners
            }
            
            //--------------------------------------------------------------
            void Gui::disableAutoEvents() {
                doAutoEvents = false;
                removeListeners();
            }
            
            //--------------------------------------------------------------
            bool Gui::getAutoEvents() {
                return doAutoEvents;
            }
            
            
            //--------------------------------------------------------------
            //void Gui::setup(ofEventArgs& e) {
            void Gui::update(ofEventArgs& e) {
                if(!isSetup) setup();
                if(!pages.size()) return;

                pages[currentPageIndex]->_update(e);
            }
            
            //--------------------------------------------------------------
            void Gui::draw(ofEventArgs& e) {
                if(!doDraw) return;
                if(!pages.size()) return;
                
                ofPushStyle();
                ofEnableSmoothing();
                ofDisableNormalizedTexCoords();
                ofDisableLighting();
                glDisable(GL_DEPTH_TEST);
//                glDisableClientState(GL_COLOR_ARRAY);
                
                
                Renderer::instance().clearControls();
                
                Panel &panel = *pages[currentPageIndex];
                
                // create layout manager for the panel if one doesn't exist
                if(!panel.layoutManager) panel.layoutManager = LayoutManagerPtr(new LayoutManager);
               
                // configure layout manager
                panel.layoutManager->boundRect.set(config.layout.padding.x, config.layout.padding.y, 0, 0);  // use full width and height of window
                panel.layoutManager->curPos.set(0, 0); // start in top left
                panel.layoutManager->rect.set(0, 0, 0, 0);
                
                // iterate all controls on panel, set position and add to render queue
                panel.layoutManager->prepareForDraw(panel);
                
                // sort and draw
                Renderer::instance().draw(config);
                
                // draw extras (scroll bar etc)
                panel.layoutManager->draw(config);
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(ofMouseEventArgs& e) {
                if(!pages.size()) return;
//                headerPage->_mouseMoved(e);
                pages[currentPageIndex]->_mouseMoved(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(ofMouseEventArgs& e) {
                if(!pages.size()) return;
//                headerPage->_mousePressed(e);
                pages[currentPageIndex]->_mousePressed(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(ofMouseEventArgs& e) {
                if(!pages.size()) return;
//                headerPage->_mouseDragged(e);
                pages[currentPageIndex]->_mouseDragged(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(ofMouseEventArgs& e) {
                if(!pages.size()) return;
//                headerPage->_mouseReleased(e);
                pages[currentPageIndex]->_mouseReleased(e);
                //	if(doAutoSave) doSave = true;
                //                if(doAutoSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::keyPressed(ofKeyEventArgs& e) {
                if(!pages.size()) return;
                if(doDefaultKeys) {
                    if(e.key == ' ') {
                        toggleDraw();
                    } else if(e.key>='0' && e.key<='9') {
                        setPage((int)(e.key - '0'));
                        setDraw(true);
                    } else if(doDraw) {
                        switch(e.key) {
                            case '[': prevPage(); break;
                            case ']': nextPage(); break;
                        }
                    }
                }
                
                if(doDraw) {
//                    headerPage->_keyPressed(e);
                    pages[currentPageIndex]->_keyPressed(e);
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(ofKeyEventArgs& e) {
                if(!pages.size()) return;
//                headerPage->_keyReleased(e);
                pages[currentPageIndex]->_keyReleased(e);
            }
            
            
        }
    }
}
