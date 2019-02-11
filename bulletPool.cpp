#include "stdafx.h"
#include "bulletPool.h"

Bullet::Bullet()
	: _bulletImage(NULL), _isActive(false), _radius(10.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::init(image * image, float radius, float range)
{
	_bulletImage = image;
	_radius = radius;
	_range = range;
	_isActive = false;

}

void Bullet::release()
{
}

void Bullet::update()
{
	bulletMove();
}

void Bullet::render()
{
	_bulletImage->render(getMemDC(), _rc.left, _rc.top);
}

void Bullet::bulletFire(float x, float y, float angle, float speed)
{
	_porc.x = _x = _fireX = x;
	_porc.y = _y = _fireY = y;
	
	_angle = angle;
	_speed = speed;
	_rc = RectMakeCenter(_porc.x, _porc.y, _bulletImage->GetWidth(), _bulletImage->GetHeight());

	_isActive = true;
}

void Bullet::bulletMove()
{
	_porc.x = _x += cosf(_angle) * _speed;
	_porc.y = _y += -sinf(_angle) * _speed;
	_rc = RectMakeCenter(_porc.x, _porc.y ,_bulletImage->GetWidth(),_bulletImage->GetHeight());

	if (_range < getDistance(_porc.x, _porc.y, _fireX, _fireY))
		_isActive = false;
}

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}

void BulletPool::init(const char * imageName, int createBullet, float range, float radius)
{
	_imageName = imageName;
	_defaultRadius = radius;
	_defaultRange = range;

	_disableBullets.reserve(createBullet);
	_enableBullets.reserve(createBullet);

	image* tempImage = IMAGEMANAGER->findImage(imageName);

	for (int i = 0; i < createBullet; ++i)
	{
		_disableBullets.push_back(new Bullet);
		_disableBullets[i]->init(tempImage, _defaultRadius, _defaultRange);
	}

}

void BulletPool::release()
{
	for (int i = 0; i < _disableBullets.size(); ++i) SAFE_DELETE(_disableBullets[i]);
	for (int i = 0; i < _enableBullets.size(); ++i)  SAFE_DELETE(_enableBullets[i]);

	_disableBullets.clear();
	_enableBullets.clear();
}

void BulletPool::update()
{
	for (int i = 0; i < _enableBullets.size(); ++i)
	{
		if (_enableBullets[i]->getActive())
		{
			_enableBullets[i]->update();
		}
		else
		{
			Bullet* tempBullet = _enableBullets[i];
			_enableBullets.erase(_enableBullets.begin() + i--);
			_disableBullets.push_back(tempBullet);
		}
	}
}

void BulletPool::render()
{
	for (int i = 0; i < _enableBullets.size(); ++i)
	{
		_enableBullets[i]->render();
	}
}

void BulletPool::fire(float x, float y, float angle, float speed)
{
	Bullet* tempBullet = NULL;
	if (_disableBullets.size() == 0)
	{
		tempBullet = new Bullet;
		//image* tempImage = IMAGEMANAGER->findImage(_imageName);
		image* tempImage = IMAGEMANAGER->addFrameImage("minionbullet", "minionbullet.bmp", 0, 0, 70, 10, 7, 1, true, RGB(255, 0, 255));
		tempBullet->init(tempImage, _defaultRadius, _defaultRange);
	}
	else
	{
		tempBullet = _disableBullets.back();
		_disableBullets.pop_back();
	}
	tempBullet->bulletFire(x, y, angle, speed);
	_enableBullets.push_back(tempBullet);
}

void BulletPool::deleteBullet(int bullet)
{
	//BulletPool.erase(_vBullet.begin() + bullet);
	(_disableBullets.begin() + bullet);
}

