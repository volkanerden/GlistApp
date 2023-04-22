/*
 * GameStart.h
 *
 *  Created on: Apr 22, 2023
 *      Author: Volkan
 */

#ifndef SRC_GAMESTART_H_
#define SRC_GAMESTART_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gAppManager.h"
#include "GameCanvas.h"

class GameStart : public gBaseCanvas {
public:
	GameStart(gApp* root);
	virtual ~GameStart();

	void setup();
	void draw();

	void mouseReleased(int x, int y, int button);

private:
	gApp* root;
	gImage gameover;
};

#endif /* SRC_GAMESTART_H_ */
