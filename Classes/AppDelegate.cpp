#include "AppDelegate.h"
#include "GameWorldScene.h"

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
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    auto curRes =director->getWinSize();
    auto designRes = Size(1280,2400);
    
    CCLOG("%f %f",director->getWinSize().width,director->getWinSize().height);
    
    if(!glview) {
        //glview = GLViewImpl::createWithRect("Prototype02", Rect(0, 0, 960, 640));
        glview = GLViewImpl::createWithRect("Prototype02", Rect(0, 0, curRes.width, curRes.height));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(curRes.width, curRes.height, ResolutionPolicy::NO_BORDER);

    //Set content scale factor
    if(1242 == curRes.width && 2208 == curRes.height)//iphone 6+
    {
        director->setContentScaleFactor(designRes.height/2400);
    }
    else if(750 == curRes.width && 1334 == curRes.height)//iphone 6
    {
        director->setContentScaleFactor(designRes.height/1440);
    }
    else if(640 == curRes.width && 1136 == curRes.height)//iphone 5 or 5s
    {
        director->setContentScaleFactor(designRes.height/1232);
    }
    else if(640 == curRes.width && 960 == curRes.height)//iphone 4
    {
        director->setContentScaleFactor(designRes.height/1248);
    }
    else if(1536 == curRes.width && 2048 == curRes.height)//iPad Retina or Air
    {
        director->setContentScaleFactor(designRes.height/2968);
    }
    else if(768 == curRes.width && 1024 == curRes.height)//iPad 2
    {
        director->setContentScaleFactor(designRes.height/1472);
    }
    else
    {
        director->setContentScaleFactor(designRes.height/curRes.height);
    }
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = GameWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
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
