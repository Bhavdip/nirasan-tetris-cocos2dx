#define COCOS2D_DEBUG 1
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director *director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("nirasan-tetris");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    prepareResourcesForAndroid(director);

    // create a scene. it's an auto release object
    auto scene = GameScene::scene();
    // run
    CCLOG("Run the Game Scene");
    director->runWithScene(scene);

    return true;
}

void AppDelegate::prepareResourcesForAndroid(Director* pDirector){

	// window size
	Size windowSize = pDirector->getWinSize();

	auto glview = pDirector->getOpenGLView();

	auto fileutils = FileUtils::getInstance();

	CCLOG("FrameSize: %f %f", windowSize.width, windowSize.height);

	int dpi = Device::getDPI();
	float scale = (240/160);
	CCLOG("DPI :%d, Scale : %f ", dpi, scale);

	// vector string that reside the directory orders
	std::vector < std::string > resDirOrders;

	// check which assets the devices require
	if (dpi == 640) {
		//Pushing back the resolution directories allows the application to fall back to
		//lower-resolution assets if a higher-resolution asset is missing.
		resDirOrders.push_back("drawable-xxxhdpi");
		resDirOrders.push_back("drawable-xxhdpi");
		resDirOrders.push_back("drawable-hdpi");
		resDirOrders.push_back("drawable-mdpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 4");

	} else if (dpi == 480) {

		resDirOrders.push_back("drawable-xxhdpi");
		resDirOrders.push_back("drawable-xhdpi");
		resDirOrders.push_back("drawable-hdpi");
		resDirOrders.push_back("drawable-mdpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 3.0");

	} else if (dpi == 320) {

		resDirOrders.push_back("drawable-xhdpi");
		resDirOrders.push_back("drawable-hdpi");
		resDirOrders.push_back("drawable-mdpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 2.0");

	} else if (dpi == 240) {
		resDirOrders.push_back("drawable-hdpi");
		resDirOrders.push_back("drawable-mdpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 1.5");

	} else if (dpi == 160) { //base line

		resDirOrders.push_back("drawable-mdpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 1");

	} else {

		resDirOrders.push_back("drawable-ldpi");

		glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);

		CCLOG("Scale 0.75");
	}

	fileutils->setSearchPaths(resDirOrders);
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
