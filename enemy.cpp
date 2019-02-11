#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINTF position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	// 0.01 ~ 1초
	_rndFireCount = RND->getFromIntTo(5, 15);
	_rndFire2Count = RND->getFromIntTo(7, 8);
	_rndFire3Count = RND->getFromIntTo(10, 20);
	_rndFire4Count = RND->getFromIntTo(5, 6);
	_rndFire5Count = RND->getFromIntTo(1, 2);
	_rndFire6Count = RND->getFromIntTo(10,11);
	_posX = position.x;
	_posY = position.y;

	_rc = RectMakeCenter(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());


	change = false;

	wave2change = false;
	wave2change2 = false;
	wave2change3 = false;
	wave2change4 = false;
	_type = ONE;
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	if (_count % 8 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = -1;
		_imageName->SetFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

	move(_type);

}

void enemy::render()
{
	draw();

	

}

void enemy::move(int type)
{
	switch (type)
	{
		//=============1웨이브====================//
	case ONE:
		_rc.left += 2;
		_rc.right += 2;
		break;

	case TWO:
		
		_rc.left -= 2;
		_rc.right -= 2;
		
		break;


		//=============2웨이브====================//
	case THREE:
		if (wave2change3 == false)
		{
			if (_rc.bottom <= 200)
			{
				_rc.top +=2;
				_rc.bottom += 2;
			}
			if (_rc.bottom >= 200)
			{
				wave2change3 = true;
			}
		}
		else if (wave2change3 == true)
		{
			if (wave2change4 == false)
			{
				_angle -= 0.02f;
				_posX = 231 + -cosf(_angle) * 100;
				_posY = 165 + -sinf(_angle) * 100;
				_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());

				if (_rc.bottom < WINSIZEY / 2 && _rc.right > 270)
				{
					//_angle -= 0.02f;
					_posX = 231 - cosf(_angle) * 100;
					_posY = 365 - -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}

				if (_rc.bottom > WINSIZEY / 2 + 69)
				{
					wave2change4 = true;
				}
			}
			else if (wave2change4 == true)
			{
				if (_rc.bottom <= WINSIZEY - 158)
				{
					_angle -= 0.02f;
					_posX = 231 + -cosf(_angle) * 100;
					_posY = 565 + -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}
				if (_rc.bottom >= WINSIZEY - 158)
				{
					_angle -= 0.02f;
					_posX = 234 - cosf(_angle) * 100;
					_posY = 765 - -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}
			}
		}
		break;


		
	case FOUR:
		if (wave2change == false)
		{
			if (_rc.bottom <= 200)
			{
				_rc.top += 2;
				_rc.bottom += 2;
			}
			if (_rc.bottom >= 200)
			{
				wave2change = true;
			}
		}
		else if (wave2change == true)
		{
			if (wave2change2 == false)
			{
				_angle -= 0.02f;
				_posX = 431 + cosf(_angle) * 100;
				_posY = 165 + -sinf(_angle) * 100;
				_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());

				if (_rc.bottom < WINSIZEY / 2 && _rc.right < 470)
				{
					//_angle -= 0.02f;
					_posX = 431 - -cosf(_angle) * 100;
					_posY = 365 - -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}

				if (_rc.bottom > WINSIZEY / 2 + 69)
				{
					wave2change2 = true;
				}
			}
			else if (wave2change2 == true)
			{
				if (_rc.bottom <= WINSIZEY - 158)
				{
					_angle -= 0.02f;
					_posX = 431 + cosf(_angle) * 100;
					_posY = 565 + -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}
				if (_rc.bottom >= WINSIZEY - 158)
				{
					_angle -= 0.02f;
					_posX = 431 - -cosf(_angle) * 100;
					_posY = 765 - -sinf(_angle) * 100;
					_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
				}
			}
			
		}
		break;


		//=============중간 보스웨이브====================//
	case FIVE:
		if (change == false)
		{
			if (_rc.bottom <= 150)
			{
				_rc.top += 2;
				_rc.bottom += 2;
			}
			else if (_rc.bottom >= 150)
			{
				change = true;
			}
		}
		else if (change == true)
		{
			_angle += 0.02f;
			_posX = 320 + cosf(_angle) * 100;
			_posY = 150 + -sinf(_angle) * 100;
			_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
		}
		break;
		//=====================================================//
	case SIX:
		_angle += 0.015f;
		_posX = WINSIZEX - 55 + cosf(_angle) * 160;
		_posY = WINSIZEY / 3 + -sinf(_angle) * 200;
		_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
		break;


		//=============4웨이브====================//
	case SEVEN:
		if (change == false)
		{
			if (_rc.top >= 150)
			{
				_rc.top -= 4;
				_rc.bottom -= 4;
			}
			else if (_rc.top <= 150)
			{
				change = true;
			}
		}
		else if (change == true)
		{
			if (_rc.right <= 304)
			{
				_angle += 0.03f;
				_posX = 170 + cosf(_angle) * 100;
				_posY = 150 + sinf(_angle) * 100;
				_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
			}
			else if (_rc.right >= 304)
			{
				_rc.top += 4;
				_rc.bottom += 4;
			}
		}

		break;

	case EIGHT:
		if (change == false)
		{
			if (_rc.top >= 150)
			{
				_rc.top -= 4;
				_rc.bottom -= 4;
			}
			else if (_rc.top <= 150)
			{
				change = true;
			}
		}
		else if (change == true)
		{
			if (_rc.left >= 426)
			{
				_angle += 0.03f;
				_posX = 525 + -cosf(_angle) * 100;
				_posY = 150 + sinf(_angle) * 100;
				_rc = RectMake(_posX, _posY, getImage()->getFrameWidth(), getImage()->getFrameHeight());
			}
			else if (_rc.left <= 426)
			{
				_rc.top += 4;
				_rc.bottom += 4;
			}
		}
		break;


		//=============5웨이브====================//
	case NINE:
		if (change == false)
		{
			if (_rc.right <= 150)
			{
				_rc.top += 4;
				_rc.bottom += 4;
				_rc.left +=3;
				_rc.right += 3;
			}	
			else if (_rc.right >= 150)
			{				
				change = true;				
			}
		}
		else if (change == true)
		{
			_movecount++;
			if (_movecount > 200)
			{
				_rc.top += 4;
				_rc.bottom += 4;
				_rc.left -= 3;
				_rc.right -= 3;
			}
		}	
		break;
	case TEN:
		if (change == false)
		{
			if (_rc.left >= 600)
			{
				_rc.top += 4;
				_rc.bottom += 4;
				_rc.left -= 3;
				_rc.right -= 3;
			}
			else if (_rc.left <= 600)
			{
				change = true;
			}
		}
		else if (change == true)
		{
			_movecount++;
			if (_movecount > 200)
			{
				_rc.top += 4;
				_rc.bottom += 4;
				_rc.left += 3;
				_rc.right += 3;
			}
		}
		break;
		//============= 보스 웨이브====================//
	case ELEVEN:
		if (change == false)
		{
			if (_rc.right <= 450)
			{
				_rc.top += 3;
				_rc.bottom += 3;
				_rc.left += 2;
				_rc.right += 2;
			}
		}
		break;
	}
}
	
void enemy::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool enemy::bulletCountFire()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(5,15);

		return true;
	}

	return false;
}

bool enemy::bullet2CountFire()
{
	_fire2Count++;

	if (_fire2Count % _rndFire2Count == 0)
	{
		_fire2Count = 0;
		_rndFire2Count = RND->getFromIntTo(7, 8);

		return true;
	}

	return false;
}


bool enemy::bullet3CountFire()
{
	_fire3Count++;

	if (_fire3Count % _rndFire3Count == 0)
	{
		_fire3Count = 0;
		_rndFire3Count = RND->getFromIntTo(10, 20);

		return true;
	}

	return false;
}

bool enemy::bullet4CountFire()
{
	_fire4Count++;

	if (_fire4Count % _rndFire4Count == 0)
	{
		_fire4Count = 0;
		_rndFire4Count = RND->getFromIntTo(5, 6);

		return true;
	}

	return false;
}

bool enemy::bullet5CountFire()
{
	_fire5Count++;

	if (_fire5Count % _rndFire5Count == 0)
	{
		_fire5Count = 0;
		_rndFire5Count = RND->getFromIntTo(1, 2);

		return true;
	}

	return false;
}

bool enemy::bullet6CountFire()
{
	_fire6Count++;

	if (_fire6Count % _rndFire6Count == 0)
	{
		_fire6Count = 0;
		_rndFire6Count = RND->getFromIntTo(10,11);

		return true;
	}

	return false;
}