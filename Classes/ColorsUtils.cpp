/*
 * ColorsUtils.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: CreoleStudios
 */

#include "ColorsUtils.h"

Color3B ColorsUtils::findColors(int colors) {
	switch (colors) {
	case Block::kColor_blue: {
		return Color3B(51, 152, 255);
		break;
	}
	case Block::kColor_dark_blue: {
		return Color3B(31, 78, 254);
		break;
	}

	case Block::kColor_yellow: {
		return Color3B(232, 236, 19);
		break;
	}
	case Block::kColor_dark_yellow: {
		return Color3B(255, 145, 30);
		break;
	}
	case Block::kColor_green: {
		return Color3B(18, 178, 18);
		break;
	}
	case Block::kColor_red: {
		return Color3B(186, 51, 19);
		break;
	}

	}
}

Sprite* ColorsUtils::findSprite(int colors) {
	switch (colors) {
	case Block::kColor_blue: {
		return Sprite::create("sky.png");
		break;
	}
	case Block::kColor_dark_blue: {
		return Sprite::create("blue.png");
		break;
	}
	case Block::kColor_yellow: {
		return Sprite::create("yellow.png");
		break;
	}
	case Block::kColor_dark_yellow: {
		return Sprite::create("orange.png");
		break;
	}
	case Block::kColor_green: {
		return Sprite::create("green.png");
		break;
	}
	case Block::kColor_red: {
		return Sprite::create("red.png");
		break;
	}
	}
}
