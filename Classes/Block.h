#ifndef __tetris__Block__
#define __tetris__Block__

#include <iostream>

class Block
{
private:
    
    int number;
    int color;
    
public:

	enum kColor {
		kColor_blue,
		kColor_dark_blue,
		kColor_green,
		kColor_red,
		kColor_yellow,
		kColor_dark_yellow
	};
    
    Block(int number, int color);
    ~Block();
    
    int getNumber();
    int getColor();
};

#endif /* defined(__tetris__Block__) */
