#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		
	RECT rc;				
	float x, y;				
	float angle;			
	float radius;			
	float speed;			
	float fireX, fireY;
	bool isFire;
	int count;
	POINT bomRc;
};

class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char*					_imageName;
	float						_range;
	int							_bulletMax;
public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void bulletFire(float x, float y, float angle, float speed);

	void bulletMove();

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

	void deleteBullet(int bullet);
};

class Bomb : public gameNode
{
private:
	vector<tagBullet>			_vBomb;
	vector<tagBullet>::iterator _viBomb;


	image* playBomb;


	float _range;
public:
	Bomb();
	~Bomb();

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
	void fire(float x, float y);

	void move();
	vector<tagBullet>			getVplayBomb() { return _vBomb; }
	vector<tagBullet>::iterator getVIplayBomb() { return _viBomb; }

	image* getImage() { return playBomb; }
};

class playbullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;


	vector<tagBullet>			_vsemiBullet;
	vector<tagBullet>::iterator _visemiBullet;

	float _range;
	int _playbulletMax;

public:
	playbullet();
	~playbullet();

	virtual HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);
	void fire2(float x, float y ,float angle, float speed);
	void move();

	vector<tagBullet> getVplaybullet()			{ return _vBullet; }
	vector<tagBullet>::iterator getVIplaybullet() { return _viBullet; }

	vector<tagBullet> getVplaysemibullet() { return _vsemiBullet; }
	vector<tagBullet>::iterator getVIsemiplaybullet() { return _visemiBullet; }


	void deleteplaybullet(int playbulletNum);
};
