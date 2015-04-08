#define COCOS2D_DEBUG 1
#include "GameScene.h"
#include "Constants.h"
#include "ColorsUtils.h"

USING_NS_CC;
using namespace std;

Scene* GameScene::scene()
{
    Scene* scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size windowSize = Director::getInstance()->getWinSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Sprite* background = Sprite::create("ic_game_background.png");
    background->setPosition(Point(windowSize.width / 2, windowSize.height / 2));
    this->addChild(background,-1);

//    setUpTouchEvent();

    makeField();
    
    makeControlButton();
    
    startGame();
    
    return true;
}

void GameScene::setUpTouchEvent(){

	isTouching = false;
	touchPosition = 0;

	// Game scene touch event listener
	auto eventListener = EventListenerTouchOneByOne::create();
	//touch occurred by detecting the touches
	eventListener->setSwallowTouches(true);

	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	eventListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMove,this);
	eventListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnd,this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener,this);
}


void GameScene::makeControlButton()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    Label* moveLeftLabel = Label::createWithTTF("Left", "fonts/Arial.ttf", GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* moveLeft = MenuItemLabel::create(moveLeftLabel,CC_CALLBACK_0(GameScene::tapMoveLeft,this));
    moveLeft->setPosition(winSize.width * 0.2, winSize.height * 0.2);
    
    Label* moveRightLabel = Label::createWithTTF("Right", "fonts/Arial.ttf", GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* moveRight = MenuItemLabel::create(moveRightLabel,CC_CALLBACK_0(GameScene::tapMoveRight,this));
    moveRight->setPosition(winSize.width * 0.8, winSize.height * 0.2);

    Label* turnLeftLabel = Label::createWithTTF("TLeft", "fonts/Arial.ttf", GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* turnLeft = MenuItemLabel::create(turnLeftLabel,CC_CALLBACK_0(GameScene::tapTurnLeft,this));
    turnLeft->setPosition(winSize.width * 0.2, winSize.height * 0.05);
    
    Label* turnRightLabel = Label::createWithTTF("TRight", "fonts/Arial.ttf", GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* turnRight = MenuItemLabel::create(turnRightLabel,CC_CALLBACK_0(GameScene::tapTurnRight,this));
    turnRight->setPosition(winSize.width * 0.8, winSize.height * 0.05);
    
    Label* pauseGame = Label::createWithTTF("Pause", "fonts/Arial.ttf",GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* menuPauseGame = MenuItemLabel::create(pauseGame,CC_CALLBACK_0(GameScene::onPauseGame,this));
	menuPauseGame->setPosition(winSize.width * 0.2,winSize.height - pauseGame->getContentSize().height);

	Label* resumeGame = Label::createWithTTF("Resume", "fonts/Arial.ttf",GAME_CONTROL_FONT_SIZE);
    MenuItemLabel* menuResumeGame = MenuItemLabel::create(resumeGame,CC_CALLBACK_0(GameScene::onResumeGame,this));
    menuResumeGame->setPosition(winSize.width * 0.8,winSize.height - resumeGame->getContentSize().height);

    Menu* menu = Menu::create(moveLeft, moveRight, turnLeft, turnRight,menuPauseGame,menuResumeGame, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
}

void GameScene::onPauseGame() {
	CCLOG("GameScene::onPauseGame");
	Director::getInstance()->pause();
}

void GameScene::onResumeGame() {
	CCLOG("GameScene::onResumeGame");
	Director::getInstance()->resume();
}

void GameScene::tapMoveLeft()
{
    game->moveLeft();
    moveChunk();
}

void GameScene::tapMoveRight()
{
    game->moveRight();
    moveChunk();
}

void GameScene::tapTurnLeft()
{
    game->chunk->turnLeft();
    moveChunk();
}

void GameScene::tapTurnRight()
{
    game->chunk->turnRight();
    moveChunk();
}

void GameScene::startGame()
{
    game = new Game();

    this->scheduleUpdate();

    this->scheduleOnce(schedule_selector(GameScene::makeAndMoveChunk), START_GAME_DELAY_TIME);
}

void GameScene::makeField()
{
    Size winSize = Director::getInstance()->getWinSize();
    for (int row = 0; row < FIELD_HEIGHT; row++) {
        for (int col = 0; col <= FIELD_WIDTH_RIGHT_INDEX - FIELD_WIDTH_LEFT_INDEX; col++) {
        	//Label* b = Label::createWithTTF("□", "fonts/Arial.ttf", 50.0);
        	Sprite* gridcube = Sprite::create("ic_grid_cube.png");
        	gridcube->setPosition(Point(winSize.width * (0.30 + col * 0.05), winSize.height * (0.05 + row * 0.03)));
			//b->setColor(Color3B(128, 128, 128));
            this->addChild(gridcube);
        }
    }
}

void GameScene::makeChunk()
{
	int number = lastBlockNumber + 1;
	CCLOG("Block Number :%d", number);
    int numbers[] = { number, number+1, number+2, number+3 };
    game->makeChunk(CHUNK_START_X, CHUNK_START_Y, numbers);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            if (game->chunk->blocks[row][col] != NULL) {
            	Label* b = Label::createWithTTF("■", "fonts/Arial.ttf", 50.0);
                int x = CHUNK_START_X - FIELD_WIDTH_LEFT_INDEX + col;
                int y = (FIELD_HEIGHT - 1) - (CHUNK_START_Y + row);
                CCLOG("GameScene:: [makeChunk]=== x:%d y:%d", x, y);
                b->setPosition(Point(winSize.width * (0.30 + x * 0.05), winSize.height * (0.05 + y * 0.03)));
                b->setColor(ColorsUtils::findColors(game->chunk->blocks[row][col]->getColor()));
                b->setTag(number);
                number++;
                this->addChild(b);
            }
        }
    }
    
    lastBlockNumber += 4;
}

void GameScene::moveChunk()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            if (game->chunk->blocks[row][col] != NULL) {
                Block* b = game->chunk->blocks[row][col];
                int number = b->getNumber();
                Label* l = (Label*)this->getChildByTag(number);
                int x = game->chunk->posX - FIELD_WIDTH_LEFT_INDEX + col;
                CCLOG("game->chunk->posX : %d", game->chunk->posX);
                int y = (FIELD_HEIGHT - 1) - (game->chunk->posY + row);
                l->setPosition(Point(winSize.width * (0.30 + x *  0.05), winSize.height * (0.05 + y * 0.03)));
                CCLOG("GameScene :: [showChunk]=== x:%d y:%d", x, y);
            }
        }
    }
}

void GameScene::deleteLines()
{
    if (game->checkDeletableLines())
    {
        for (int i = 0; i < FIELD_HEIGHT; i++)
        {
            if (game->deletableLines[i])
            {
                for (int j = 0; j < FIELD_WIDTH; j++)
                {
                    if (game->field->blocks[i][j] != NULL)
                    {
                        Block* b = game->field->blocks[i][j];
                        int number = b->getNumber();
                        
                        this->removeChildByTag(number);
                    }
                }
            }
        }
        
        game->deleteDeletableLines();
        
        Size winSize = Director::getInstance()->getWinSize();
        
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                if (game->field->blocks[i][j] != NULL) {
                    Block* b = game->field->blocks[i][j];
                    int number = b->getNumber();
                    Label* l = (Label*)this->getChildByTag(number);
                    int x = j - FIELD_WIDTH_LEFT_INDEX;
                    int y = (FIELD_HEIGHT - 1) - i;
                    MoveTo* action = MoveTo::create(0.2, Point(winSize.width * (0.30 + x * 0.05), winSize.height * (0.05 + y * 0.03)));
                    l->runAction(action);
                }
            }
        }


    }
}

void GameScene::moveUnder(float dt)
{
    if (game->canMoveUnder()) {
        game->moveUnder();
        moveChunk();
        CCLOG("GameScene:: moveUnder :: moveChunk");
    } else {
    	game->copyBlocks();
        this->unschedule(schedule_selector(GameScene::moveUnder));
        deleteLines();
        resetIfGameover();
        this->scheduleOnce(schedule_selector(GameScene::makeAndMoveChunk), START_GAME_DELAY_TIME);
        CCLOG("GameScene:: moveUnder :: makeAndMoveChunk ");
    }
}

void GameScene::makeAndMoveChunk(float dt)
{
    makeChunk();
    this->schedule(schedule_selector(GameScene::moveUnder), SPEED_TETROMINO_INTERVAL);
}

void GameScene::resetIfGameover()
{
	bool needReset = false;
    for (int i = 0; i < FIELD_HEIGHT_UPPER_INDEX; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (game->field->blocks[i][j] != NULL) {
				CCLOG("GameScene::resetIfGameover: %d", game->field->blocks[i][j]->getNumber());
				needReset = true;
            }
        }
    }
    if(needReset)
    Director::getInstance()->replaceScene((Scene*)GameScene::scene());
}

//*********************
// Game Touch Event Listener
//**********************
void GameScene::update(float dt){
	//CCLOG("GameScene::update");

	Size visibleSize = Director::getInstance()-> getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	if(true == isTouching)
	{
		// check which half of the screen is being touched
		if(touchPosition < visibleSize.width/2)
		{
			// move the object left side
			tapMoveLeft();
		}
		else
		{
			// move the object right side
			tapMoveRight();
		}
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	CCLOG("GameScene :: onTocuhBean");
	isTouching = true;
	touchPosition = touch->getLocation().x;
	return true;
}

void GameScene::onTouchMove(Touch* touch,Event* event){
	CCLOG("GameScene :: onTouchMove");
}

void GameScene::onTouchEnd(Touch *touch,Event* event){
	isTouching = false;
	CCLOG("GameScene :: onTouchEnd");
}

void GameScene::onTouchCancelled(Touch *touch,Event* event){
	CCLOG("GameScene :: onTouchCancelled");
}
