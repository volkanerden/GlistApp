/*
 * GameStart.cpp
 *
 *  Created on: Apr 22, 2023
 *      Author: Volkan
 */

#include "GameStart.h"




GameStart::GameStart(gApp *root) : gBaseCanvas(root) {
	this->root = root;

}

GameStart::~GameStart() {
}

void GameStart::setup() {
	gameover.loadImage("gameover.png");
}

void GameStart::draw() {
	gameover.draw(0, 0);
}

void GameStart::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	if(x > 0 && x < getWidth() && y > 0 && y < getHeight()) {
		GameCanvas *cnv = new GameCanvas(root);
		root->getAppManager()->setCurrentCanvas(cnv);
	}
}
