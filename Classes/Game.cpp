#define COCOS2D_DEBUG 1
#include "Game.h"
#include "Config.h"
#include "Chunk.h"
#include "cocos2d.h"

USING_NS_CC;

Game::Game()
{
    field = new Field();
    chunk = new Chunk();
    deletableLines = new bool[FIELD_HEIGHT];
    for (int i = 0; i < FIELD_HEIGHT; i++) deletableLines[i] = false;
}

Game::~Game()
{
    delete field;
    delete chunk;
    delete[] deletableLines;
}

void Game::makeChunk(int x, int y, int numbers[])
{
    chunk->setPos(x, y);
    int shape = rand() % Chunk::kShape_last;
    //shape = Chunk::kShape_rl;
    Chunk::makeBlocks(chunk->blocks, shape, numbers);
}

void Game::moveLeft()
{
    if (canMoveLeft()){
    	chunk->posX = chunk->posX - 1;
    }
}

void Game::moveRight()
{
    if (canMoveRight()){
    	chunk->posX = chunk->posX + 1;
    }
}

void Game::moveUnder()
{
    if (canMoveUnder()) {
    	chunk->posY = chunk->posY + 1;
    }
}

bool Game::canMoveLeft()
{
	for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = 0; col < CHUNK_WIDTH; col++) {
            if (chunk->blocks[row][col] != NULL) {
                int leftX = chunk->posX + col - 1;
                CCLOG("field->blocks[%d][%d]",row,leftX);
                if (leftX < FIELD_WIDTH_LEFT_INDEX) return false;
                if (field->blocks[row][leftX] != NULL){
                	CCLOG("field->blocks[%d][%d]",row,leftX);
                	return false;
                }else{
                	CCLOG("field->blocks[i][leftX] == NULL");
                }
                break;                
            }
        }
    }
    return true;
}

bool Game::canMoveRight()
{
    for (int row = 0; row < CHUNK_HEIGHT; row++) {
        for (int col = CHUNK_WIDTH - 1; col > 0; col--) {
            if (chunk->blocks[row][col] != NULL) {
                int rightX = chunk->posX + col + 1;
                CCLOG("canMoveRight:%d", rightX);
                if (rightX > FIELD_WIDTH_RIGHT_INDEX) return false;
                if (field->blocks[row][rightX] != NULL) return false;
                break;
            }
        }
    }
    return true;
}

bool Game::canMoveUnder()
{
    bool checked = false;
    for (int i = 0; i < CHUNK_WIDTH; i++) {
        for (int j = CHUNK_HEIGHT - 1; j >= 0; j--) {
            if (chunk->blocks[j][i] != NULL) {
                CCLOG("[canMoveUnder] x:%d y:%d", j, i);
                int underX = chunk->posX + i;
                int underY = chunk->posY + j + 1;
                if (underY > FIELD_HEIGHT - 1) return false;
                if (field->blocks[underY][underX] != NULL) return false;
                checked = true;
                break;
            }
        }
    }
    return checked;
}

void Game::copyBlocks()
{
    for (int i = 0; i < CHUNK_HEIGHT; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {
            int y = i + chunk->posY;
            int x = j + chunk->posX;
            if (chunk->blocks[i][j] != NULL) {
                CCLOG("[copyBlocks] posX:%d posY:%d i:%d j:%d x:%d y:%d", chunk->posX, chunk->posY, i, j, x, y);
                field->blocks[y][x] = chunk->blocks[i][j];
                chunk->blocks[i][j] = NULL;
            }
        }
    }
}

void Game::turnLeft()
{
    //chunk->turnLeft();
    if (isConflict()) {
    	chunk->turnLeft();
        chunk->turnRight();
    }
}

void Game::turnRight()
{
//    chunk->turnRight();
    if (isConflict()) {
    	chunk->turnRight();
        chunk->turnLeft();
    }
}

bool Game::isConflict()
{
    for (int i = 0; i < CHUNK_HEIGHT; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {
            int y = i + chunk->posY;
            int x = j + chunk->posX;
            if (chunk->blocks[i][j] != NULL) {
                CCLOG("===== i:%d j:%d x:%d y:%d", i, j, x, y);
                if (y < 0 || FIELD_HEIGHT-1 < y) return true;
                CCLOG("===== %d", 1);
                if (x < FIELD_WIDTH_LEFT_INDEX || FIELD_WIDTH_RIGHT_INDEX < x) return true;
                CCLOG("===== %d", 2);
                if (field->blocks[y][x] != NULL) return true;
                CCLOG("===== %d", 3);
            }
        }
    }
    return false;
}

bool Game::checkDeletableLines()
{
    bool ret = false;
    for (int i = 1; i < FIELD_HEIGHT; i++) {
        deletableLines[i] = false;
        bool check = true;
        for (int j = FIELD_WIDTH_LEFT_INDEX; j <= FIELD_WIDTH_RIGHT_INDEX; j++) {
            if (field->blocks[i][j] == NULL) {
                CCLOG("[checkDeletableLines] x:%d y:%d is NULL", j, i);
                check = false;
                break;
            }
        }
        if (check) {
            deletableLines[i] = ret = true;
        }
    }
    return ret;
}

void Game::deleteDeletableLines()
{
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        if (!deletableLines[i]) continue;
        // delete blocks
        for (int j = FIELD_WIDTH_LEFT_INDEX; j <= FIELD_WIDTH_RIGHT_INDEX; j++) {
            if (field->blocks[i][j] != NULL) {
                delete field->blocks[i][j];
                field->blocks[i][j] = NULL;
            }
        }
        // copy block from upper
        for (int j = i; j > 0; j--) {
            for (int k = FIELD_WIDTH_LEFT_INDEX; k <= FIELD_WIDTH_RIGHT_INDEX; k++) {
                if (field->blocks[j-1][k] != NULL) {
                    field->blocks[j][k] = field->blocks[j-1][k];
                    field->blocks[j-1][k] = NULL;
                }
            }
        }
        deletableLines[i] = false;
    }
}

