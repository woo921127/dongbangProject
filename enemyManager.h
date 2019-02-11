#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "minion.h" 
#include "boss.h"
#include "semiboss.h"
#include "bulletPool.h"
#include "ItemManager.h"
#include <vector>

enum STAGE
{
	ST_ONE = 1,
	ST_TWO,
	ST_THREE,
	ST_FOUR,
	ST_FIVE,
	ST_SIX,
	ST_SEVEN,
	ST_CLEAR

};

enum BULFIRE
{
	BUL_ONE = 1,
	BUL_TWO,
	BUL_THREE,
	BUL_FOUR,
	BUL_FIVE,
	BUL_SIX
};

enum BOSSFIRE
{
	BUL_BOSS_ONE = 1,
	BUL_BOSS_TWO,
	BUL_BOSS_THREE,
	BUL_BOSS_FOUR,
	BUL_BOSS_FIVE
};

class player;


class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:

	image* lastboss;
	image* semiboss3;


	vEnemy	_vMinion;
	viEnemy _viMinion;

	vEnemy _v2Minion;
	viEnemy _vi2Minion;

	vEnemy _v3Minion;
	viEnemy _vi3Minion;

	vEnemy _vsemiBoss;
	viEnemy _visemiBoss;

	vEnemy	_vBoss;
	viEnemy _viBoss;
		

	vEnemy _vsemiimg;
	viEnemy _visemiimg;

	bullet* _bullet;
	ItemManager* _item;


	BulletPool* _bulletPool;
	BulletPool* _bulletPool2;
	BulletPool* _bulletPool3;
	BulletPool* _bulletPool4;


	BulletPool* _semibullet;
	BulletPool* _bossbullet;
	BulletPool* _bossbullet2;
	BulletPool* _bossbullet3;
	BulletPool* _bossbullet4;
	BulletPool* _bossbullet5;


	player* _play;
	
	image* boss3pt;
	image* boss3pt1;
	image* bossmove;

	int playerHP;
	float mini2angle;
	int semibosspt;
	int semiindex;
	
	float pt2angle;
	float pt2angle2;
	float speed5;
	bool pt2change;
	int bosspt;
	int bosindex;

	int _count;
	int _count2;
	int _count3;
	int _count4;
	int _count5;
	int _count6;
	int _count7;
	int _count12;
	int _semicount;
	int score;

	bool aa;
	//=================================//
	int _count8; //보스2번째 대기시간
	int _count9; //보스3번쨰 대기시간
	int _count10;//보스4번째 대기시간
	int _count11; //보스5번째 대기시간

	//================================//
	int _stage;
	int _bul;
	int _bossbul;



	int _semibossHP;

	float angle;
	float angle2;
	float angle3;
	float angle4;
	float angle5;
	float angle6;
	float angle7;
	float angle8;

	float semiangle;
	float semiangle2;
	float legth;

	float speed;
	float speed2;
	float speed3;


	bool check;
	bool change;
	float speed4;

	int bopt2;
	bool bopt2count;
	int bopt3;
	bool bopt3count;
	int bopt4;
	bool bopt4count;
	int bopt5;
	bool bopt5count;
	bool crashcheck;
	int crashcount;

	bool misscheck;
	int misscount;
	int pt3count;
	int index;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion_and_boss();

	void minionBulletFire(int fire);

	void BossBulletFire(int fire);

	void BulletplayCollision();
	void bulletsideout();
	void BombMinionBulletCollision();


	vector<enemy*> getVMinion()				{ return _vMinion; }
	vector<enemy*>::iterator getVIMinion()  { return _viMinion; }

	vector<enemy*> getV2Minion()			{ return _v2Minion; }
	vector<enemy*>::iterator getVI2Minion() { return _vi2Minion; }

	vector<enemy*> getV3Minion()		    { return _v3Minion; }
	vector<enemy*>::iterator getVI3Minion() { return _vi3Minion; }


	vector<enemy*> getVsemiBoss() { return _vsemiBoss; }
	vector<enemy*>::iterator getVIsemiBoss() { return _visemiBoss; }

	vector<enemy*> getVsemiimg() { return _vsemiimg; }
	vector<enemy*>::iterator getVIsemiimg() { return _visemiimg; }

	vector<enemy*> getVBoss()			 { return _vBoss; }
	vector<enemy*>::iterator getVIBoss() { return _viBoss; }



	void deleteMinion(int minionNum);
	void delete2Minion(int minionNum);
	void delete3Minion(int minionNum);
	void deleteBoss(int minionNum);
	void deletesemiBoss(int minionNum);


	void setplayAdressLink(player* play) { _play = play; }

	inline int getStage() { return _stage; }
	void setStage(int stage) { _stage = stage; }


	inline int getcount() { return misscount; }
	void setcount(int crashCheck) { misscount = crashCheck; }

	inline int getcount2() { return crashcount; }
	void setcount2(int crashCheck) { crashcount = crashCheck; }

	inline int getplayHP() { return playerHP; }
	void setplayHP(int hp) { playerHP = hp; }

	image* getImage() { return lastboss; }
	
	void bulletpt1erase();
	void bulletpt2erase();
	void bulletpt3erase();
	void bulletpt4erase();


	void deleteSideMinion();

};

