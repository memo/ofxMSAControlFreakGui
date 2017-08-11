//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreakGui
//

#pragma once

#include "Panel.h"

namespace msa {
    namespace controlfreak {
        namespace gui {
            class Container;
            
            class Page : public Panel {
            public:
                Page(Container *parent, ParameterGroup *p) : Panel(parent, p, false) {}
                
            protected:
            };
            
            
        }
    }
}
