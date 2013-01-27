
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"



namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //            Gui gui;
            
            //--------------------------------------------------------------
            Gui::Gui() : Container(NULL, "ofxMSAControlFreakGui") {
                doDefaultKeys = false;
//                currentPageIndex = false;
                doDraw = true;
                _pActiveControl = NULL;
                pconfig = ConfigPtr(new Config);
                pLayoutManager = LayoutManagerPtr(new LayoutManager);
                _pGuiControls = new GuiControls(this);
                addControl(_pGuiControls);
                enableAllEvents();
            }
            
            //--------------------------------------------------------------
            Gui::~Gui() {
                for(int i=0; i<pages.size(); i++) delete pages[i];
            }
            
            //--------------------------------------------------------------
            //            void Gui::setup() {
            //                isSetup = true;
            ////                show();
            ////                ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
            //            }
            
            
            //--------------------------------------------------------------
            bool Gui::checkOkToRun() {
                return pages.empty() == false && doDraw;
            }
            
            //--------------------------------------------------------------
            void Gui::setDraw(bool b) {
                doDraw = b;
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
                setPage(getCurrentPageIndex() + 1);
            }
            
            //--------------------------------------------------------------
            void Gui::prevPage() {
                setPage(getCurrentPageIndex() - 1);
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(int i) {
                if(pages.size()) {
                    _pGuiControls->pagesDropdown->getParameter() = (i-1 + pages.size()) % pages.size();
                }
            }
            
            int Gui::getCurrentPageIndex() {
                return (int)_pGuiControls->pagesDropdown->getParameter()+1;
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(string name) {
                for(int i=0; i<pages.size(); i++) {
                    Page &page = *pages[i];
                    if(page.getName() == name) {
                        setPage(i+1);
                        return;
                    }
                };
            }
            
            //--------------------------------------------------------------
            int Gui::getNumPages() {
                return pages.size();
            }
            
            //--------------------------------------------------------------
            Page& Gui::getPage(int i) {
                return *pages.at(i-1);
            }
            
            //--------------------------------------------------------------
            Page& Gui::getPage(string name) {
                for(int i=0; i<pages.size(); i++) if(name.compare(pages[i]->getName()) == 0) return *pages[i];
            }
            
            //--------------------------------------------------------------
            Page& Gui::getCurrentPage() {
                return getPage(getCurrentPageIndex());
            }
            
            //--------------------------------------------------------------
            //            Page& Gui::addPage(string name) {
            //                Page* page(new Page(NULL, name));
            //                return addPage(page);
            //            }
            
            //--------------------------------------------------------------
            Page& Gui::addPage(ParameterGroup &parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Gui::addPage(ParameterGroup): " << parameters.getPath();
                Page* page(new Page(this, &parameters));
                addPage(page);
                page->init();
                return *page;
            }
            
            //--------------------------------------------------------------
            Page& Gui::addPage(Page* page) {
                ofLogVerbose() << "msa::ControlFreak::gui::Gui::addPage(Page*): " << page->getParameter().getPath();
                pages.push_back(page);
                return *page;
            }
            
            
            //--------------------------------------------------------------
            void Gui::setActiveControl(Control *control) {
                ofLogVerbose() << "msa::ControlFreak::Gui::Gui::setActiveControl: " << (control ? control->getParameter().getPath() : "NULL");
                // if old control exists, put it at the back
                if(_pActiveControl) _pActiveControl->popZ();
                
                _pActiveControl = control;
                
                // put new active control at the front
                if(_pActiveControl) {
                    _pActiveControl->setZ(1e100);
                }
            }
            
            //--------------------------------------------------------------
            Control* Gui::getActiveControl() {
                return _pActiveControl;
            }
            
            //--------------------------------------------------------------
            void Gui::releaseActiveControl() {
                setActiveControl(NULL);
            }
            
            //--------------------------------------------------------------
            //            bool Container::isActive() {
            //                bool b = pactiveControl == titleButton;//pactiveControl != NULL;
            //                return parent ? b | parent->isActive() : b;
            //            }
            
            
            
            
            //--------------------------------------------------------------
            void Gui::update() {
                if(!checkOkToRun()) return;
                //                if(!isSetup) setup();
                
                Container::update();
                getCurrentPage()._update();
                Container::update();
            }
            
            //--------------------------------------------------------------
            void Gui::draw() {
                if(!checkOkToRun()) return;
                
                ofPushStyle();
                ofEnableSmoothing();
                ofDisableNormalizedTexCoords();
                ofDisableLighting();
                glDisable(GL_DEPTH_TEST);
                //                glDisableClientState(GL_COLOR_ARRAY);
                
                
                Renderer::instance().clearControls();
                
                Page &page = getCurrentPage();
                
                // create layout manager for the page if one doesn't exist
                if(!pLayoutManager) pLayoutManager = LayoutManagerPtr(new LayoutManager);
                
                // configure layout manager
                pLayoutManager->boundRect.set(pconfig->layout.scrollbarWidth + pconfig->layout.padding.x, pconfig->layout.padding.y, 0, 0);  // use full width and height of window
                
                // iterate all controls on page, set position and add to render queue
                pLayoutManager->begin();
                pLayoutManager->prepareContainer(page);
                pLayoutManager->prepareContainer(*_pGuiControls);
                pLayoutManager->update();
                
                // sort and draw
                Renderer::instance().draw();
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(int x, int y) {
                if(!checkOkToRun()) return;
                
//                if(getActiveControl()) {
//                    getActiveControl()->mouseMoved(x, y);
//                } else {
                    getCurrentPage().mouseMoved(x, y);
                    Container::mouseMoved(x, y);
//                }
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(int x, int y, int button) {
                if(!checkOkToRun()) return;
                
//                if(getActiveControl()) {
//                    getActiveControl()->mousePressed(x, y, button);
//                } else {
                    getCurrentPage().mousePressed(x, y, button);
                    Container::mousePressed(x, y, button);
//                }
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(int x, int y, int button) {
                if(!checkOkToRun()) return;
                
//                if(getActiveControl()) {
//                    getActiveControl()->mouseDragged(x, y, button);
//                } else {
                    getCurrentPage().mouseDragged(x, y, button);
                    Container::mouseDragged(x, y, button);
//                }
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(int x, int y, int button) {
                if(!checkOkToRun()) return;
                
//                if(getActiveControl()) {
//                    getActiveControl()->mouseReleased(x, y, button);
//                } else {
                    getCurrentPage().mouseReleased(x, y, button);
                    Container::mouseReleased(x, y, button);
//                }
                releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Gui::keyPressed(int key) {
                if(!pages.size()) return;
                if(doDefaultKeys) {
                    if(key == ' ') {
                        toggleDraw();
                    } else if(key>='1' && key<='9') {
                        setPage((int)(key - '1')+1);
                        setDraw(true);
                    } else if(doDraw) {
                        switch(key) {
                            case '[': prevPage(); break;
                            case ']': nextPage(); break;
                        }
                    }
                }
                
                if(doDraw) {
//                    if(getActiveControl()) {
//                        getActiveControl()->keyPressed(key);
//                    } else {
                        getCurrentPage().keyPressed(key);
                        Container::keyPressed(key);
//                    }
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(int key) {
                if(!checkOkToRun()) return;
//                if(getActiveControl()) {
//                    getActiveControl()->keyReleased(key);
//                } else {
                    getCurrentPage().keyReleased(key);
                    Container::keyReleased(key);
//                }
            }
            
            
        }
    }
}
