#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

enum tagplayground
{
	Ysize = 5000,

};

class playGround : public gameNode
{
private:



	player* _play;
	enemyManager* _em;
	ItemManager* _item;
	float alpha;
	float alpha2;
	float img_x, img_y;
	RECT backrc;
	RECT mainrc;
	int alpha3;
	int alpha4;
	int numindex;
	int alpha5;
	int alpha6;
	int alpha7;
	int alpha8;
	int timecount;

	int startNum;
	bool _isstart;
	bool check;
	bool check2;
	bool check3;
	bool check4;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	playGround();
	~playGround();
};

