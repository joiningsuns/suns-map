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

	ofGLWindowSettings settings;
	settings.setSize(MAP_WIDTH, MAP_HEIGHT);
	settings.windowMode = OF_WINDOW;
	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>(args));
	ofRunMainLoop();
}
