
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"



namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //            Gui gui;
            
            //--------------------------------------------------------------
            Gui::Gui() : Container(NULL, "ofxMSAControlFreakGui") {
                isSetup = false;
                doDefaultKeys = false;
                currentPageIndex = false;
                doDraw = true;
                pconfig = ConfigPtr(new Config);
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
                setPage(currentPageIndex + 1);
            }
            
            //--------------------------------------------------------------
            void Gui::prevPage() {
                setPage(currentPageIndex - 1);
            }
            
            //--------------------------------------------------------------
            void Gui::setPage(int i) {
                if(pages.size()) currentPageIndex = (i + pages.size()) % pages.size();
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
            Page& Gui::addParameters(ParameterGroup &parameters) {
                Page* page(new Page(this, &parameters, pages.size()));
                return addPage(page);
            }
            
            //--------------------------------------------------------------
            Page& Gui::addPage(Page* page) {
                if(!isSetup) setup();
                
                pages.push_back(page);
                return *page;
            }
         
            //--------------------------------------------------------------
            void Gui::update() {
                if(!checkOkToRun()) return;
//                if(!isSetup) setup();
                
                Container::update();
                pages[currentPageIndex]->_update();
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
                
                Page &page = *pages[currentPageIndex];
                
                // create layout manager for the page if one doesn't exist
                if(!page.layoutManager) page.layoutManager = LayoutManagerPtr(new LayoutManager);
                
                // configure layout manager
                page.layoutManager->boundRect.set(pconfig->layout.scrollbarWidth + pconfig->layout.padding.x, pconfig->layout.padding.y, 0, 0);  // use full width and height of window
                
                // iterate all controls on page, set position and add to render queue
                page.layoutManager->update(page);
                
                // sort and draw
                //                Renderer::instance().update();
                Renderer::instance().draw();
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(int x, int y) {
                if(!checkOkToRun()) return;
                pages[currentPageIndex]->mouseMoved(x, y);
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(int x, int y, int button) {
                if(!checkOkToRun()) return;
                pages[currentPageIndex]->mousePressed(x, y, button);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(int x, int y, int button) {
                if(!checkOkToRun()) return;
                pages[currentPageIndex]->mouseDragged(x, y, button);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(int x, int y, int button) {
                if(!checkOkToRun()) return;
                pages[currentPageIndex]->mouseReleased(x, y, button);
                //	if(doAutoSave) doSave = true;
                //                if(doAutoSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::keyPressed(int key) {
                if(!pages.size()) return;
                if(doDefaultKeys) {
                    if(key == ' ') {
                        toggleDraw();
                    } else if(key>='1' && key<='9') {
                        setPage((int)(key - '1'));
                        setDraw(true);
                    } else if(doDraw) {
                        switch(key) {
                            case '[': prevPage(); break;
                            case ']': nextPage(); break;
                        }
                    }
                }
                
                if(doDraw) {
                    pages[currentPageIndex]->keyPressed(key);
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(int key) {
                if(!checkOkToRun()) return;
                pages[currentPageIndex]->keyReleased(key);
            }
            
            
        }
    }
}
