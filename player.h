#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "bulletPool.h"
#include "progressbar.h"
#include "ItemManager.h"
#pragma warning(disable:4996)


struct semi_bossHP {
	int _semibossHp;
	int _lastbossHp;
};

enum PLAYSTATE
{
	PLAY_IDLE,
	PLAY_RIGHT_MOVE,
	PLAY_LEFT_MOVE,
};


class enemyManager;

class player : public gameNode
{
private:
	image* play;		
	Bomb* _Bomb;
	playbullet* _playbullet;
	
	image* playBomb;
	image* playFly;

	PLAYSTATE _state;

	ItemManager* _item;

	int _firecount;

	int _shift;
	int _shift2;

	float minionHP, minionHP2, minionHP3;
	//progressbar* _semibossHp;
	float _maxHP , _bossMaxHP;

	int crash;

	RECT HPbar;
	RECT bossHPbar;
	enemyManager* _em;

	int playscore;
	int playcount;

	int _count;
	int _index;
	int _power;
	int index;
	
	int _count1;
	int _count2;
	
	int _BombCount;
	int _Bombindex;
	
	int itemcount;

	int excount;
	int bomcount;
	semi_bossHP _HPcheck;
	bool check;
	bool bomcheck;
	bool change;

	int flycount;
	int flyindex;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void playMove();
	void bulletMinionCollision();
	void BombMinionCollision();
	
	inline int getSemiBossHp() { return _maxHP; }
	void setSemiBossHp(int hpCheck) { _maxHP = hpCheck; }


	inline int getLastBossHp() { return _bossMaxHP; }
	void setLaseBossHp(int hpCheck) { _bossMaxHP = hpCheck; }

	inline int getbomCount() { return excount; }
	void setbomCount(int bomb) { excount = bomb; }

	inline int getscoreCount() { return playscore; }
	void setscoreCount(int bomb) { playscore = bomb; }


	inline int getpower() { return _power; }
	void setpower(int power) { _power = power; }

	inline int getbomb() { return itemcount; }
	void setbomb(int power) { itemcount = power; }



	image* getImage() { return play; }

	image* getbombImage() { return playBomb; }


	Bomb* getPlayerBomb() {	return _Bomb;}

	
	void setEnemyAdressLink(enemyManager* em) { _em = em; }

	

};

