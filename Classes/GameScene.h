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
    
    void tapMoveBottom();

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

    void updateGameScore();

    void resetGameScore();

public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void registerEventDispatche();

    bool isTouching; // default is false
    int touchPosition;

    cocos2d::Label* scoreValue;

    void update(float ft);

    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event);
    void onTouchMove(cocos2d::Touch *touch,cocos2d::Event * event);
    void onTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif /* defined(__tetris__GameScene__) */
