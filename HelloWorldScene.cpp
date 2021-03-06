#include "HelloWorldScene.h"
#include "About.h"

#define userDefault UserDefault::getInstance()

USING_NS_CC;

bool isFirstMusic = true;
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}


bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//初始化
	touchedBack = 0;
	exit = NULL;
	Size screenSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	CCSprite* Background = CCSprite::create("menu/UI1.png");
	Background->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	this->addChild(Background);
	//触摸效果开启
	this->setTouchEnabled(true);

	//冒险模式
	auto item_Adventure = MenuItemImage::create(
							"menu/play1.png",
							"menu/play2.png",
							CC_CALLBACK_1(HelloWorld::startGame, this));
	item_Adventure->setPosition(ccp(80,-135));
	//关于界面
	auto item_About= MenuItemImage::create(
							"menu/about1.png",
							"menu/about2.png",
							CC_CALLBACK_1(HelloWorld::aboutFunc, this));
	item_About->setPosition(ccp(-110,-200));
	//播放背景音乐
	if(!userDefault->getBoolForKey("Music")){
		userDefault->getBoolForKey("Music",true);
		userDefault->flush();
	}
	int musBef = userDefault->getBoolForKey("Music");
	userDefault->flush();
	if(isFirstMusic & musBef)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/Babkg_music.wav",true);
		isFirstMusic = false;
	}

	//声音开关
	//打开关闭两个状态
	auto on = MenuItemImage::create("menu/voice1.png","menu/voice2.png",NULL,NULL);
	auto off = MenuItemImage::create("menu/voice3.png","menu/voice4.png",NULL,NULL);
	//初始化状态为1
	MenuItemToggle *item_Voice;
	int selectId;
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		item_Voice = MenuItemToggle::createWithTarget(this, menu_selector(HelloWorld::setOptions),on,off, NULL);
		AudioState = 1;
		selectId = AudioState? 0 : 1;
	}
	else
	{
		item_Voice = MenuItemToggle::createWithTarget(this, menu_selector(HelloWorld::setOptions),off,on, NULL);
		AudioState = 0;
		selectId = AudioState? 1 : 0;
	}
	//int selectId = AudioState? 0 : 1;
	item_Voice->setSelectedIndex(selectId);
	item_Voice->setPosition(ccp(-30,-155));

	CCMenu* menu = CCMenu::create(item_Adventure,item_Voice,item_About,NULL);
	this->addChild(menu);

	//响应键盘消息
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	// bind touch event实现触摸效果
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}
//关于按键的回调函数
void HelloWorld::aboutFunc(Ref* pSender)
{
	CCLOG("about_Menu item clicked");
	Director::sharedDirector()->replaceScene(GameAbout::createScene());
}
//开始游戏按键的回调函数
void HelloWorld::startGame(cocos2d::Ref* pSender)
{
	CCLOG("dventure_Menu item clicked");
	CCDirector::sharedDirector()->replaceScene(GameLayer::createScene());
}
//声音按键的回调函数，把用户的选择存储在后台
void HelloWorld::setOptions(cocos2d::Ref* pSender)
{
	bool temp = userDefault->getBoolForKey("Music");
	userDefault->flush();
	userDefault->setBoolForKey("Music",!temp);
	userDefault->flush();

	bool tmpSound = AudioState;
	AudioState = !AudioState;

	if (!tmpSound) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/Babkg_music.wav",true);
		isFirstMusic = false;
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}
//响应安卓返回键
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)
{
	exit = LabelTTF::create("Press back button again to exit", "fonts/fzmwt.ttf", 15);
	if(keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		if(!touchedBack)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Point origin = Director::getInstance()->getVisibleOrigin();
			exit->runAction(CCFadeOut::create(2.0));
			exit->setPosition(Point(origin.x + visibleSize.width/2,
				origin.y + visibleSize.height/2));
			this->addChild(exit);
			touchedBack = true;
		}
		else 
			Director::getInstance()->end();
	}
	else
	{
		touchedBack = false;
		if(exit)
		{
			exit->removeFromParentAndCleanup(true);
		}
	}
}
//响应触摸
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused)
{
	touchedBack = false;
	if(exit)
	{
		exit->removeFromParentAndCleanup(true);
	}
	return touchedBack;
}
