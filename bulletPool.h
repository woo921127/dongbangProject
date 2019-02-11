#pragma once
#include "gameNode.h"
#include <vector>


class Bullet : public gameNode
{
private:
	image* _bulletImage;		
	RECT _rc;					
	float _x, _y;				
	float _fireX, _fireY;		
	float _angle;				
	float _radius;				
	float _speed;				
	float _range;				
	POINT _porc;
	bool _isActive;
public:
	Bullet();
	~Bullet();

	void init(image* image, float radius, float range);
	void release();
	void update();
	void render();

	void bulletFire(float x, float y, float angle, float speed);

	void bulletMove();

public:

	//È°µ¿ÁßÀÎ ÃÑ¾Ë ¿©ºÎ
	void setActive(bool isActive) { _isActive = isActive; }
	bool getActive() const { return _isActive; }

	RECT getRC() { return _rc; }
};

//ºæ·¿ Ç®~
class BulletPool
{
private:
	//RECT rc;
	float _defaultRange;
	float _defaultRadius;
	const char* _imageName;

	vector<Bullet*> _disableBullets;//¾È¾²´Â°Å
	vector<Bullet*> _enableBullets;//¾²´Â°Å

	//vector<Bullet*>			_getbullet;
	//vector<Bullet*>::iterator _getibullet;

	
public:
	BulletPool();
	~BulletPool();

	void init(const char* imageName, int createBullet = 10000, float range = 1200.0f, float radius = 10.0f);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void deleteBullet(int bullet);


	//vector<Bullet*> GetBullet() { return _getbullet; }
	//vector<Bullet*>::iterator GetVIBullet() { return _getibullet; }

public:
	//¹ß»çµÈ ÃÑ¾Ë º¤ÅÍ
	vector<Bullet*> getActiveBullets()const { return _enableBullets; }
};
