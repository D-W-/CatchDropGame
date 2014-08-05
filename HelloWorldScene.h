#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(HelloWorld);

	void setOptions(cocos2d::Ref* pSender);
	//��Ӧ��׿���ؼ�
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)override;
	virtual bool onTouchBegan(Touch *touch, Event *unused) override;
private:
	CCMenuItemImage *item_Voice;
	bool AudioState;
	LabelTTF * exit;
	//��¼�Ƿ��˱�ĵط�
	bool touchedBack;
};

#endif // __HELLOWORLD_SCENE_H__
