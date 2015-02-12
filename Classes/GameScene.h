#ifndef __tetris__GameScene__
#define __tetris__GameScene__

#include "cocos2d.h"
#include "Game.h"

#define FONT_NAME MarkerFelt.ttf

class GameScene : public cocos2d::Layer
{
private:
    Game* game;
    int lastBlockNumber = 0;
    
    void makeField();
    
    void makeControlButton();
    void tapMoveLeft();
    void tapMoveRight();
    void tapTurnLeft();
    void tapTurnRight();
    
    void startGame();
    
    void makeChunk();
    void moveChunk();
    void makeAndMoveChunk(float dt);
    
    void moveUnder(float dt);
    
    void deleteLines();
    
    void resetIfGameover();
    
    void setUpTouchEvent();

    void onPauseGame();

    void onResumeGame();

public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);

    bool isTouching; // default is false
    int touchPosition;

    void update(float ft);

    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event);
    void onTouchMove(cocos2d::Touch *touch,cocos2d::Event * event);
    void onTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif /* defined(__tetris__GameScene__) */
