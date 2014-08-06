#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "SquareSprite.h"
#include "Raindrop.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();
	static Scene* createScene();
	CREATE_FUNC(GameLayer);

	virtual bool init() override;
	virtual bool onTouchBegan(Touch *touch, Event *unused) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)override;

	void ReturnToMainFunc(cocos2d::Ref* pSender);
private:
	//���ؼ�����
	LabelTTF * m_exit;
	//����ָ�����з������ָ��
	SquareSprite ** m_matrix;
	//��ǣ�һ��ѡ·�������Ƿ��ҹ��þ���
	bool * m_mark;
	//SpriteBatchNode *spriteSheet;
	int m_width;
	int m_height;
	bool m_isTouchEnable;
	Raindrop* m_raindrop;
	int m_markSize;
	bool m_isTrapped;

	Point positionOfItem(int row, int col);
	int findWay(int row,int col,int result);
	SquareSprite *GameLayer::spriteOfPoint(Point *point);
	void initCloud();
	void moveRaindrop();
};
#endif /* defined(__GAMELAYER_H__) */