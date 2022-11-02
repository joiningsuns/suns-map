#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char *argv[])
{	
	vector<string> args;
	for (int i = 0; i < argc - 1; i++)
	{
		if (ofToString(argv[i]) == "--args")
		{
			for (i++; i < argc; i++)
			{
				args.push_back(ofToString(argv[i]));
			}
		}
	}

	// Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1000, 1000);
	settings.windowMode = OF_WINDOW; // can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>(args));
	ofRunMainLoop();
}
