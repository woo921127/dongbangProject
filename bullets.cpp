#include "stdafx.h"
#include "bullets.h"


bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	bulletMove();
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->GetWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,bullet.bulletImage->GetWidth(),bullet.bulletImage->GetHeight());
	
	_vBullet.push_back(bullet);

}

void bullet::bulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,_viBullet->bulletImage->GetWidth(),_viBullet->bulletImage->GetHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::deleteBullet(int bullet)
{
	_vBullet.erase(_vBullet.begin() + bullet);
}


Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

HRESULT Bomb::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; ++i)
	{
		tagBullet bomb;
		ZeroMemory(&bomb, sizeof(bomb));
		bomb.bulletImage = new image;
		bomb.bulletImage->init("Bomb2.bmp", 200, 97, true, RGB(255, 0, 255));
		bomb.speed = 1.0f;
		bomb.isFire = false;

		_vBomb.push_back(bomb);
	}

	return S_OK;
}

void Bomb::release()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		SAFE_RELEASE(_viBomb->bulletImage);
		SAFE_DELETE(_viBomb->bulletImage);
		_vBomb.clear();
	}
}

void Bomb::update()
{
	move();
}

void Bomb::render()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (!_viBomb->isFire) continue;

		//_viBomb->bulletImage->render(getMemDC(),_viBomb->rc.left,_viBomb->rc.top,0, 0,_viBomb->bulletImage->GetWidth(),_viBomb->bulletImage->GetHeight());
	}
}

void Bomb::fire(float x, float y)
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (_viBomb->isFire) continue;

		_viBomb->isFire = true;
		_viBomb->x = _viBomb->fireX = x;
		_viBomb->y = _viBomb->fireY = y;
		//_viBomb->rc = RectMakeCenter(_viBomb->x, _viBomb->y, _viBomb->bulletImage->GetWidth(), _viBomb->bulletImage->GetHeight());
	}

}

void Bomb::move()
{
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		if (!_viBomb->isFire) continue;
		
		//_viBomb->y -= _viBomb->speed;
		//_viBomb->rc = RectMakeCenter(_viBomb->x, _viBomb->y,_viBomb->bulletImage->GetWidth(),_viBomb->bulletImage->GetHeight());

		if (_range < getDistance(_viBomb->x, _viBomb->y, _viBomb->fireX, _viBomb->fireY))
		{
			_viBomb->isFire = false;
		}
	}
}

playbullet::playbullet()
{
}

playbullet::~playbullet()
{
}

HRESULT playbullet::init(int bulletMax, float range)
{
	_playbulletMax = bulletMax;
	_range = range;


	return S_OK;
}

void playbullet::release()
{
}

void playbullet::update()
{
	move();
}

void playbullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
			_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 0, 0, 16, 16);
	}

	for (_visemiBullet = _vsemiBullet.begin(); _visemiBullet != _vsemiBullet.end(); ++_visemiBullet)
	{
		_visemiBullet->bulletImage->render(getMemDC(), _visemiBullet->rc.left, _visemiBullet->rc.top, 0, 0, 16, 16);
	}

}

void playbullet::fire(float x, float y, float angle, float speed)
{
	if (_playbulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));

	bullet.bulletImage = new image;
	bullet.bulletImage->init("bullet32.bmp", 16, 16, true, RGB(0, 0, 0));
	bullet.speed = 15.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->GetWidth(), bullet.bulletImage->GetHeight());

	_vBullet.push_back(bullet);
}

void playbullet::fire2(float x, float y, float angle, float speed)
{
	if (_playbulletMax < _vsemiBullet.size()) return;
	
	tagBullet semibullet;
	ZeroMemory(&semibullet, sizeof(semibullet));
	
	semibullet.bulletImage = new image;
	semibullet.bulletImage->init("subbullet.bmp", 16, 16, true, RGB(0, 0, 0));
	//IMAGEMANAGER->findImage("fild")->render(getMemDC(), semirc.right + 90, semirc.top + (semirc.bottom - semirc.top) / 2 - 30);
	semibullet.speed = 15.0f;
	semibullet.x = semibullet.fireX = x;
	semibullet.y = semibullet.fireY = y;
	semibullet.angle = angle;
	semibullet.rc = RectMakeCenter(semibullet.x, semibullet.y, semibullet.bulletImage->GetWidth(), semibullet.bulletImage->GetHeight());
	
	_vBullet.push_back(semibullet);

}

void playbullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->GetWidth(), _viBullet->bulletImage->GetHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

	for (_visemiBullet = _vsemiBullet.begin(); _visemiBullet != _vsemiBullet.end(); )
	{
		_visemiBullet->x += cosf(_visemiBullet->angle) * _visemiBullet->speed;
		_visemiBullet->y += -sinf(_visemiBullet->angle) * _visemiBullet->speed;
		_visemiBullet->rc = RectMakeCenter(_visemiBullet->x, _visemiBullet->y, _visemiBullet->bulletImage->GetWidth(), _visemiBullet->bulletImage->GetHeight());
	
		if (_range < getDistance(_visemiBullet->x, _visemiBullet->y, _visemiBullet->fireX, _visemiBullet->fireY))
		{
			SAFE_RELEASE(_visemiBullet->bulletImage);
			SAFE_DELETE(_visemiBullet->bulletImage);
			_visemiBullet = _vBullet.erase(_visemiBullet);
		}
		else ++_visemiBullet;
	}
}

void playbullet::deleteplaybullet(int playbulletNum)
{
	SAFE_RELEASE(_vBullet[playbulletNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + playbulletNum);
}
