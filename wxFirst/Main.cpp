#include <wx/wx.h>
#include "MyFrame.h"

class MyApp : public wxApp {
public:
	virtual bool OnInit();
	virtual int OnExit() { return 0; }
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);

	return true;
}