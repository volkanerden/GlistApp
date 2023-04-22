#include "GameCanvas.h"

/*TODO
 * Fix - enemy draw blackscreen
 * Fix - enemies always standing on left and stacks up on top
 * Loading Screen
 */

GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
		loadAssets();
		loadVariables();
}

void GameCanvas::update() {
	if(!isGameOver) {
		updatePlayer();
		updateEnemy();
		updateAnimations();
		updateCollisionCheck();
	}
}

void GameCanvas::draw() {
//	Draw Map
	map.draw(mapposx, mapposy, map.getWidth() * scale, map.getHeight() * scale);
	drawProps();
	if(!isGameOver) {
		drawPlayer();
		drawEnemy();
		drawGUI();
	}
	else
		gameover.draw(0, 0);
//	gLogi() << enemies.size();
}
void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;

	if(key == G_KEY_A) moveleft = true;
	if(key == G_KEY_D) moveright = true;
	if(key == G_KEY_W) moveup = true;
	if(key == G_KEY_S) movedown = true;

	if(key == G_KEY_SPACE) player.isAttacking = true;
}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;

	if(key == G_KEY_A) moveleft = false;
	if(key == G_KEY_D) moveright = false;
	if(key == G_KEY_W) moveup = false;
	if(key == G_KEY_S) movedown = false;

	if(key == G_KEY_SPACE) player.isAttacking = false;
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void GameCanvas::mousePressed(int x, int y, int button) {

}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	if(x > 0 && x < getWidth() && y > 0 && y < getHeight()) {
		std::vector<Enemy>& enemies_ = enemies;
		for (int i = 0; i < enemies_.size(); i++) {
		enemies_.clear();
		loadVariables();
		isGameOver = false;
		}
	}
}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

float GameCanvas::Vec2Length(float x, float y) {
	float result = sqrtf((x * x) + (y * y));
	return result;
}

float GameCanvas::Vec2xNormalize(float x, float y) {
	float result;
	float length = sqrtf((x*x) + (y*y));

	if (length > 0)
	{
		float ilength = 1.0f/length;
	    result = x*ilength;
	}
	return result;
}

float GameCanvas::Vec2yNormalize(float x, float y) {
	float result;
	float length = sqrtf((x*x) + (y*y));

	if (length > 0)
	{
		float ilength = 1.0f/length;
	    result = y*ilength;
	}
	return result;
}

bool GameCanvas::checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2) {
	if(xLeft1 < xRight2 && xRight1 > xLeft2 && yBottom1 > yUp2 && yUp1 < yBottom2) {
		return true;
	}
	return false;
}

void GameCanvas::loadAssets() {
//	Load Map
	map.loadImage("worldmap.png");

//	Load Character Animations
	//IDLE
	for(int i = 0; i < PLAYER_FRAME; i++) {
		player_idle_right[i].loadImage("character/Idle/right/tile00" + gToStr(i) + ".png");
		player_idle_left[i].loadImage("character/Idle/left/tile00" + gToStr(i) + ".png");
	}
	//RUN
	for(int i = 0; i < PLAYER_FRAME; i++) {
		player_move_right[i].loadImage("character/Run/right/tile00" + gToStr(i) + ".png");
		player_move_left[i].loadImage("character/Run/left/tile00" + gToStr(i) + ".png");
	}
	for(int i = 0; i < PLAYER_FRAME; i++) {
		player_attack_right[i].loadImage("character/Attack/right/tile00" + gToStr(i) + ".png");
		player_attack_left[i].loadImage("character/Attack/left/tile00" + gToStr(i) + ".png");
	}
	for(int i = 0; i < PLAYER_FRAME; i++) {
		player_dead[i].loadImage("character/Death/right/tile00" + gToStr(i) + ".png");
	}
//	Load Props
	for(int i = 0; i < PROP_COUNT; i++) {
		props[i].loadImage("props/tile0" + gToStr(i) + ".png");
	}

//	Load Enemy Animations
	for(int i = 0; i < ENEMYMOVE_FRAME; i++) {
		enemy_move_right[i].loadImage("enemy/Walk/right/tile0" + gToStr(i) + ".png");
		enemy_move_left[i].loadImage("enemy/Walk/left/tile0" + gToStr(i) + ".png");
	}
	for(int i = 0; i < ENEMYATTACK_FRAME; i++) {
		enemy_attack_right[i].loadImage("enemy/Attack/right/tile0" + gToStr(i) + ".png");
		enemy_attack_left[i].loadImage("enemy/Attack/left/tile0" + gToStr(i) + ".png");
	}
	for(int i = 0; i < ENEMYDIE_FRAME; i++) {
		enemy_dead[i].loadImage("enemy/Dead/tile0" + gToStr(i) + ".png");
	}
	for(int i = 0; i < PROP_COUNT; i++) {
		propx[i] = gRandom(3000);
		propy[i] = gRandom(3000);
	}
	defaultfont.loadFont("FreeSans.ttf", 20);
	gameover.loadImage("game_over.png");
}
void GameCanvas::loadVariables() {
	moveleft = false;
	moveright = false;
	moveup = false;
	moveleft = false;
	player.isMoving = false;
	facingright = true;
	player.isAttacking = false;
	player.isDead = false;
	enemy.isDead = false;
	enemy.isAttacking = false;
	isGameOver = false;

	mapposx = -1800.0f;
	mapposy = -1500.0f;
	scale = 6.0f;

	directionx = 0.0f;
	directiony = 0.0f;
	player.speed = 10.0f;
	player.x = 200;
	player.y = 200;
	player.w = player_move_right[0].getWidth() * 2.5f;
	player.h = player_move_right[0].getHeight() * 2.5f;
	player.health = 100.0f;
	player.damage = 1.0f;

	enemy.x = gRandom(3000);
	enemy.y = gRandom(3000);
	enemy.w = enemy_move_right[0].getWidth() * 3;
	enemy.h = enemy_move_right[0].getHeight() * 3;
	enemy.speed = 2.0f;
	enemy.health = 100.0f;
	enemy.damage = 0.3f;

	chasex = 0.0f;
	chasey = 0.0f;

	animcounter = 0;
	animdiecounter = 0;
	enemydiecounter = 0;
	enemymovecounter = 0;
	enemyattackcounter = 0;
	updatetime = 1.0f/12.0f;

	aiSpawnCounter = 0;
	aiSpawnCntLimit = 120;

	indent = 50;
	score = 0;
}
void GameCanvas::stopMoving() {
	mapposx = mapposlastframex;
	mapposy = mapposlastframey;
}
void GameCanvas::drawPlayer() {
	if(!player.isDead) {
//	Draw Character Animations
	//	RUN
		if(player.isMoving && directionx > 0) {
			player_move_right[animcounter].draw(player.x, player.y, player.w, player.h);
			facingright = true;
		}
		else if(player.isMoving && directionx < 0) {
			player_move_left[animcounter].draw(player.x, player.y, player.w, player.h);
			facingright = false;
		}
		else if(player.isMoving && (directiony > 0 || directiony < 0) && facingright)
			player_move_right[animcounter].draw(player.x, player.y, player.w, player.h);
		else if(player.isMoving && (directiony > 0 || directiony < 0) && !facingright)
			player_move_left[animcounter].draw(player.x, player.y, player.w, player.h);
		else if(player.isAttacking && facingright) {
			player_attack_right[animcounter].draw(player.x, player.y, player.w, player.h);
		}
		else if(player.isAttacking && !facingright) {
			player_attack_left[animcounter].draw(player.x, player.y, player.w, player.h);
		}
		//IDLE
		if(!player.isMoving && facingright && !player.isAttacking) {
			player_idle_right[animcounter].draw(player.x, player.y, player.w, player.h);
		}
		else if (!player.isMoving && !facingright && !player.isAttacking){
			player_idle_left[animcounter].draw(player.x, player.y, player.w, player.h);
		}
	}
	else player_dead[animdiecounter].draw(player.x, player.y, player.w, player.h);
}
void GameCanvas::drawEnemy() {
	std::vector<Enemy>& enemies_ = enemies;
	for (int i = 0; i < enemies_.size(); i++) {
		Enemy& enemy = enemies_[i];
		if(enemy.isDead) {
			return;
		}
		if(!enemy.isAttacking) {
			if(enemy.isOnLeft) enemy_move_right[enemymovecounter].draw(enemy.x + mapposx +50, enemy.y + mapposy +100, enemy.w, enemy.h);
			else enemy_move_left[enemymovecounter].draw(enemy.x + mapposx +50, enemy.y + mapposy +100, enemy.w, enemy.h);
		}
		else {
			if (enemy.isOnLeft) enemy_attack_right[enemyattackcounter].draw(enemy.x + mapposx +50 -5, enemy.y + mapposy +100-10, enemy.w * 2, enemy.h + 15);
			else enemy_attack_left[enemyattackcounter].draw(enemy.x + mapposx +50, enemy.y + mapposy +100, enemy.w * 2, enemy.h + 15);
		}
	}
}
void GameCanvas::updatePlayer() {

	mapposlastframex = mapposx;
	mapposlastframey = mapposy;

//	Keypressed-direction relations
	if(moveleft == true) directionx -= 1.0;
	else if(moveright == true) directionx += 1.0;
	else if(moveup == true) directiony -= 1.0;
	else if(movedown == true) directiony += 1.0;
	else {
		directionx = 0;
		directiony = 0;
	};
//	Move the map
	if(Vec2Length(directionx, directiony) != 0.0f) {
		mapposx = mapposx - (Vec2xNormalize(directionx, directiony) * player.speed);
		mapposy = mapposy - (Vec2yNormalize(directionx, directiony) * player.speed);
	}
//	Player Movement
	if(directionx == 0 && directiony == 0) player.isMoving = false;
	else player.isMoving = true;

//	Player Die Condition
	if(player.health <= 0) {
		player.health = 0;
		player.isDead = true;
		isGameOver = true;
	}
	if(player.health >= 100) player.health = 100;

//	Limit Borders
	if(mapposx > 0 || mapposy > 0 || mapposx < -MAP_LIMIT_RIGHT|| mapposy < -MAP_LIMIT_BOTTOM )
		stopMoving();
}
void GameCanvas::updateAnimations() {
//	Update Animation Frame
	dt = ft.Mark();
	runtime += dt;
	if(runtime >= updatetime) {
		animcounter++;
		enemymovecounter++;
		enemyattackcounter++;
		enemydiecounter++;
		runtime = 0.0f;
		if(animcounter >= PLAYER_FRAME) animcounter = 0;
		if(enemymovecounter >= ENEMYMOVE_FRAME) enemymovecounter = 0;
		if(enemyattackcounter >= ENEMYATTACK_FRAME) enemyattackcounter = 0;
	}
	if(enemydiecounter >= ENEMYDIE_FRAME) enemydiecounter = 13;
}
void GameCanvas::updateCollisionCheck() {
//	Check Prop Collision
	for(int i = 0; i < PROP_COUNT; i++) {
		if(checkCollision(300, 300, 380, 400,
			propx[i] + mapposx + indent, propy[i] + mapposy + indent,
			propx[i] + mapposx + props[i].getWidth() * scale - indent,
			propy[i] + mapposy + props[i].getHeight() * scale - indent)) stopMoving();
	}
	std::vector<Enemy>& enemy_ = enemies;
	for(int i = 0; i < enemy_.size(); i++) {
		Enemy& enemy = enemy_[i];
//		Check Enemy Collision
		if (!enemy.isDead && checkCollision(300, 300, 380, 400,
			enemy.x + mapposx +50, enemy.y + mapposy +100,
			enemy.w + enemy.x + mapposx +50 -30, enemy.h + enemy.y + mapposy +100 +10)) stopMoving();
	}
}
void GameCanvas::updateEnemy() {
	aiSpawnCounter++;
	if(aiSpawnCounter >= aiSpawnCntLimit) {
		aiSpawnCounter = 0;
		generateEnemy(enemy.x + mapposx +50, enemy.y + mapposy +100, enemy.w, enemy.h, 3, 100, 0.2, 0, 0);
	}
	std::vector<Enemy>& enemy_ = enemies;
	for(int i = 0; i < enemy_.size(); i++) {
		Enemy& enemy = enemy_[i];

//	Enemy Movement
	chasex = player.x - (enemy.x + mapposx) + enemy.w + 50;
	chasey = player.y - (enemy.y + mapposy);
	chasex = Vec2xNormalize(chasex, chasey);
	chasey = Vec2yNormalize(chasex, chasey);
	chasex *= enemy.speed;
	chasey *= enemy.speed;
	enemy.x += chasex;
	enemy.y += chasey;

//	Enemy Attack Condition
	if (!enemy.isDead && enemyattackcounter >= 8 && checkCollision(270, 300, 380, 400,
			enemy.x + mapposx + 50, enemy.y + mapposy + 100,
			enemy.w + enemy.x + mapposx +50, enemy.h + enemy.y + mapposy +100)) {
		enemy.isAttacking = true;
		player.health -= enemy.damage;
	}
	else enemy.isAttacking = false;

//	Enemy Die Condition
	if(enemy.health <= 0) {
		enemy.isDead = true;
		score++;
		player.health += 5;
		enemy_.erase(enemy_.begin() + i);
		continue;
	}
	if(player.isAttacking && (checkCollision(270, 300, 380, 400,
			enemy.x + mapposx +50, enemy.y + mapposy +100,
			enemy.w + enemy.x + mapposx +50, enemy.h + enemy.y + mapposy +100))) enemy.health -= player.damage;

	if(-mapposx >= enemy.x - 300) enemy.isOnLeft = true;
	else enemy.isOnLeft = false;
	}
}

void GameCanvas::drawProps() {
	for(int i = 0; i < PROP_COUNT; i++) {
		props[i].draw(propx[i] + mapposx, propy[i] + mapposy, props[i].getWidth() * scale, props[i].getHeight() * scale);
	}
}

void GameCanvas::generateEnemy(float x, float y, int w, int h, float speed, float health, float damage, bool isDead, bool isAttacking) {
	Enemy enemy;
	enemy.x = x;
	enemy.y = y;
	enemy.w = w;
	enemy.h = h;
	enemy.speed = speed;
	enemy.health = health;
	enemy.damage = damage;
	enemy.isDead = 0;
	enemy.isAttacking = 0;
	enemy.isOnLeft = 0;

	enemies.push_back(enemy);
}

void GameCanvas::drawGUI() {
	defaultfont.drawText("Health: %" + gToStr((int)player.health), 50, 50);
	defaultfont.drawText("Score: " + gToStr(score), 600, 50);

}
