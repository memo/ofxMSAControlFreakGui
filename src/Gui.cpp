
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"



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
            Gui::~Gui() {
                for(int i=0; i<pages.size(); i++) delete pages[i];
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
            //            void Gui::nextPageWithBlank() {
            //                if(doDraw) {
            //                    setPage(currentPageIndex + 1);
            //                    if(currentPageIndex == 0) setDraw(false);
            //                } else {
            //                    setDraw(true);
            //                    setPage(1);
            //                }
            //            }
            
            //--------------------------------------------------------------
            void Gui::setPage(int i) {
                if(pages.size()) currentPageIndex = i % pages.size();
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(string name) {
                for(int i=0; i<pages.size(); i++) {
                    Page &page = *pages[i];
                    if(page.getName() == name) {
                        currentPageIndex = i;
                        return;
                    }
                };
                setPage(currentPageIndex);
            }
            
            //--------------------------------------------------------------
            int Gui::getNumPages() {
                return pages.size();
            }
            
            //--------------------------------------------------------------
            Page& Gui::getPage(int i) {
                if(!isSetup) setup();
                return *pages.at(i);
            }
            
            //--------------------------------------------------------------
            Page& Gui::getPage(string name) {
                if(!isSetup) setup();
                for(int i=1; i<pages.size(); i++) if(name.compare(pages[i]->getName()) == 0) return *pages[i];
            }
            
            //--------------------------------------------------------------
            Page& Gui::getCurrentPage() {
                return getPage(currentPageIndex);
            }
            
            //--------------------------------------------------------------
            //            Page& Gui::addPage(string name) {
            //                Page* page(new Page(NULL, name));
            //                return addPage(page);
            //            }
            
            //--------------------------------------------------------------
            Page& Gui::addPage(ParameterGroup &parameters) {
                Page* page(new Page(this, &parameters));
                return addPage(page);
            }
            
            //--------------------------------------------------------------
            Page& Gui::addPage(Page* page) {
                if(!isSetup) setup();
                
                pages.push_back(page);
                page->setConfig(&config);
                //                setPage(pages.size() - 1);
                return *page;
            }
            
            //--------------------------------------------------------------
            //            Page& Gui::addParameters(ParameterGroup* parameters) {
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
                
                pages[currentPageIndex]->update();
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
                
                Page &page = *pages[currentPageIndex];
                
                // create layout manager for the page if one doesn't exist
                if(!page.layoutManager) page.layoutManager = new LayoutManager;
                
                // configure layout manager
                page.layoutManager->boundRect.set(config.layout.scrollbarWidth + config.layout.padding.x, config.layout.padding.y, 0, 0);  // use full width and height of window
                
                // iterate all controls on page, set position and add to render queue
                page.layoutManager->update(page);
                
                // sort and draw
                //                Renderer::instance().update();
                Renderer::instance().draw(config);
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(ofMouseEventArgs& e) {
                if(!pages.size()) return;
                //                headerPage->_mouseMoved(e);
                pages[currentPageIndex]->mouseMoved(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(ofMouseEventArgs& e) {
                if(!pages.size()) return;
                //                headerPage->_mousePressed(e);
                pages[currentPageIndex]->mousePressed(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(ofMouseEventArgs& e) {
                if(!pages.size()) return;
                //                headerPage->_mouseDragged(e);
                pages[currentPageIndex]->mouseDragged(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(ofMouseEventArgs& e) {
                if(!pages.size()) return;
                //                headerPage->_mouseReleased(e);
                pages[currentPageIndex]->mouseReleased(e);
                //	if(doAutoSave) doSave = true;
                //                if(doAutoSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::keyPressed(ofKeyEventArgs& e) {
                if(!pages.size()) return;
                if(doDefaultKeys) {
                    if(e.key == ' ') {
                        toggleDraw();
                    } else if(e.key>='1' && e.key<='9') {
                        setPage((int)(e.key - '1'));
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
                    pages[currentPageIndex]->keyPressed(e);
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(ofKeyEventArgs& e) {
                if(!pages.size()) return;
                //                headerPage->_keyReleased(e);
                pages[currentPageIndex]->keyReleased(e);
            }
            
            
        }
    }
}
