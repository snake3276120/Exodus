
#ifndef __DemoApp_h_
#define __DemoApp_h_

#include "BaseApplication.h"

class DemoApp : public BaseApplication
{
public:
    DemoApp(void);
    virtual ~DemoApp(void);

	
protected:
    virtual void createScene(void);
};

#endif // #ifndef __DemoApp_h_

