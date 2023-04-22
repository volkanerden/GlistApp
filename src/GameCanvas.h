#ifndef GAMECANVAS_H_
#define GAMECANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include <cmath>
#include "FrameTimer.h"

class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gApp* root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();

private:
	struct Player {
		int w, h;
		float x, y;
		float speed;
		float health;
		float damage;
		bool isDead;
		bool isMoving;
		bool isAttacking;

	};
	struct Enemy {
		float x;
		float y;
		int w;
		int h;
		float speed;
		float health;
		float damage;
		bool isDead;
		bool isOnLeft;
		bool isAttacking;
	};
	static const int PROP_COUNT = 12;
	static const int PLAYER_FRAME = 10;
	static const int ENEMYDIE_FRAME = 15, ENEMYMOVE_FRAME = 13, ENEMYATTACK_FRAME = 18;
	static const int MAP_LIMIT_RIGHT = 3840 , MAP_LIMIT_BOTTOM = 3835 ;
	static const int DIRT = 0, CACTUS = 1, PLANT1 = 2, PLANT2 = 3, SKELETON = 4, BUSH = 5,
			BRUSHWOOD = 6, THING = 7, TREE = 8, WOOD = 9, ROCK = 10 , SIGN = 11;

	gApp* root;
	//MAP
	gImage map;
	//PLAYER
	gImage player_idle_right[PLAYER_FRAME];
	gImage player_idle_left[PLAYER_FRAME];
	gImage player_move_right[PLAYER_FRAME];
	gImage player_move_left[PLAYER_FRAME];
	gImage player_attack_right[PLAYER_FRAME];
	gImage player_attack_left[PLAYER_FRAME];
	gImage player_dead[PLAYER_FRAME];
	//PROPS
	gImage props[PROP_COUNT];
	//ENEMY
	gImage enemy_idle_right[11];
	gImage enemy_idle_left[11];
	gImage enemy_move_right[13];
	gImage enemy_move_left[13];
	gImage enemy_attack_right[18];
	gImage enemy_attack_left[18];
	gImage enemy_dead[15];

	gImage gameover;

	gFont defaultfont;

	FrameTimer ft;
	Player player;
	Enemy enemy;

	float dt;

	bool isGameOver;
	bool moveleft, moveright, moveup, movedown;
	bool facingright;

	float mapposx, mapposy;
	float velocityx, velocityy;
	float directionx, directiony;

	float enemy_worldposx, enemy_worldposy;
	float chasex, chasey;

	float propx[PROP_COUNT], propy[PROP_COUNT];

	float scale;

	int animcounter;
	int animdiecounter;
	int enemydiecounter;
	int enemymovecounter;
	int enemyattackcounter;

	float runtime;
	float updatetime;
	float mapposlastframex, mapposlastframey;

	int aiSpawnCounter;
	int aiSpawnCntLimit;

	int currentframe;

	int indent;
	int score;

	std::vector<Enemy> enemies;

	float Vec2Length(float x, float y);
	float Vec2xNormalize(float x , float y);
	float Vec2yNormalize(float x , float y);

	void loadAssets();
	void loadVariables();

	void updatePlayer();
	void updateEnemy();
	void updateAnimations();

	void drawPlayer();
	void drawEnemy();
	void drawProps();
	void drawGUI();

	void updateCollisionCheck();

	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);
	void stopMoving();
	bool isDead();

	void generateEnemy(float x, float y, int w, int h, float speed, float health, float damage, bool isDead, bool isAttacking);
};
#endif /* GAMECANVAS_H_ */
