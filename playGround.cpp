#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	
	IMAGEMANAGER->addImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minionbullet", "minionbullet.bmp", 28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minionbullet2", "minionbullet2.bmp", 28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minionbullet3", "minionbullet3.bmp", 14, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minionbullet4", "minionbullet4.bmp", 14, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("semibullet", "semibullet.bmp", 63, 62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbullet", "bosslastbullet.bmp", 14, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbullet2", "bosslastbullet2.bmp", 28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbullet3", "bosslastbullet3.bmp", 63, 62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbullet4", "bosslastbullet4.bmp", 63, 62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbullet5", "bosslastbullet5.bmp", 63, 62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("main", "mainimg.bmp", 1062, 854, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startbutten", "startbutten.bmp", 126, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("quitbutten", "quitbutten.bmp", 98, 44, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("effect", "bosseffect.bmp", 600, 800, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("number", "number.bmp", 0, 0, 150, 15, 10, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addImage("menu", "menu.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("fild", "fild.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss3pt", "boss3pt.bmp", 0, 0, 970, 97, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("semiBoss", "semiBoss.bmp", 0, 0,300, 100, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("stageMinion", "minion.bmp", 0, 0, 180, 33, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경", "background2.bmp", 600, Ysize, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("백", "background4.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("start", "start.bmp", 192, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("clear", "clear.bmp", 174, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("무적중", "무적중.bmp", 57, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("충돌중", "충돌중.bmp", 57, 18, true, RGB(255, 0, 255));
	img_y = Ysize - WINSIZEY;
	alpha = 0;
	alpha2 = 255;
	IMAGEMANAGER->findImage("백")->setAlpahBlend(true, alpha);
	IMAGEMANAGER->findImage("start")->setAlpahBlend(true, alpha2);
	IMAGEMANAGER->findImage("startbutten")->setAlpahBlend(true, alpha3);
	IMAGEMANAGER->findImage("quitbutten")->setAlpahBlend(true, alpha4);
	IMAGEMANAGER->findImage("clear")->setAlpahBlend(true, alpha5);
	IMAGEMANAGER->findImage("effect")->setAlpahBlend(true, alpha6);
	IMAGEMANAGER->findImage("무적중")->setAlpahBlend(true, alpha7);
	IMAGEMANAGER->findImage("충돌중")->setAlpahBlend(true, alpha8);


	_play = new player;
	_play->init();

	_em = new enemyManager;
	_em->init();

	_item = new ItemManager;
	_item->init();

	_em->setMinion_and_boss();
	alpha3 = 125;
	alpha4 = 125;
	alpha5 = 255;
	alpha6 = 125;

	alpha7 = 255;
	alpha8 = 255;
	_isstart = false;
	numindex = 0;

	startNum = 2;

	_em->setplayAdressLink(_play);
	_play->setEnemyAdressLink(_em);

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_play);
	SAFE_DELETE(_em);
	SAFE_DELETE(_item);
}


void playGround::update()
{
	gameNode::update();

	
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		startNum = 0;


	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		startNum = 1;
	}

	if (startNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_isstart = true;
		}
	}

	if (startNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			PostQuitMessage(0);
		}
	}



	if (_isstart == true)
	{
		_play->update();
		_em->update();
	}

	if (_em->getplayHP() < 0)
	{
		_isstart = false;
		init();
	}

	if (_em->getStage() > 8)
	{

		alpha5 += 3;
		if (alpha5 >= 255)
		{
			alpha5 = 125;
		}


		timecount++;


		if (timecount >= 300)
		{
			_isstart = false;
			init();
		}

	}
	if (check == false)
	{
		if (_play->getLastBossHp() <= 464)
		{
			alpha6--;
		}
		if (alpha6 <= 0)
		{

			check = true;
			alpha6 = 125;
		}
	}

	if (check2 == false)
	{
		if (_play->getLastBossHp() <= 348)
		{
			alpha6--;
		}
		if (alpha6 <= 0)
		{
			check2 = true;
			alpha6 = 125;

		}
	}

	if (check3 == false)
	{
		if (_play->getLastBossHp() <= 232)
		{
			alpha6--;
		}
		if (alpha6 <= 0)
		{
			check3 = true;
			alpha6 = 125;

		}
	}

	if (check4 == false)
	{
		if (_play->getLastBossHp() <= 116)
		{
			alpha6--;
		}
		if (alpha6 <= 0)
		{
			check4 = true;
			alpha6 = 125;

		}
	}


}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	

	IMAGEMANAGER->findImage("배경")->render(getMemDC(), backrc.left + 59, backrc.top + 27, 0, img_y, 600,800);
	_play->render();
	_em->render();
	IMAGEMANAGER->findImage("main")->render(getMemDC(), mainrc.left, mainrc.top, 0, 0, WINSIZEX, WINSIZEY);


	if (check == false)
	{
		if (_play->getLastBossHp() <= 464)
		{

			IMAGEMANAGER->findImage("effect")->alphaRender(getMemDC(), backrc.left + 59, backrc.top + 27, alpha6);
		}
	}
	
	if (check2 == false)
	{
		if (_play->getLastBossHp() <= 348)
		{

			IMAGEMANAGER->findImage("effect")->alphaRender(getMemDC(), backrc.left + 59, backrc.top + 27, alpha6);
		}
	}


	if (check3 == false)
	{
		if (_play->getLastBossHp() <= 232)
		{

			IMAGEMANAGER->findImage("effect")->alphaRender(getMemDC(), backrc.left + 59, backrc.top + 27, alpha6);
		}
	}

	if (check4 == false)
	{
		if (_play->getLastBossHp() <= 116)
		{

			IMAGEMANAGER->findImage("effect")->alphaRender(getMemDC(), backrc.left + 59, backrc.top + 27, alpha6);
		}
	}


	
	



	if (_em->getStage() > 8)
	{
		IMAGEMANAGER->findImage("clear")->alphaRender(getMemDC(), 280, 360, alpha5);
	}

	

	if (_isstart == false)
	{
		
		

		IMAGEMANAGER->findImage("menu")->render(getMemDC(), mainrc.left, mainrc.top, 0, 0, WINSIZEX, WINSIZEY);

		
		alpha2-= 10;


		IMAGEMANAGER->findImage("startbutten")->alphaRender(getMemDC(), 240, 420, alpha3);
		IMAGEMANAGER->findImage("quitbutten")->alphaRender(getMemDC(), 240, 480, alpha4);
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			alpha3 = 255;
			alpha4 = 125;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			alpha3 = 125;
			alpha4 = 255;
		}
		
		
		




	}


	if (_isstart == true)
	{
		if (_em->getStage() != 3)
		{
			if (img_y > 0)
			{
				img_y -= 1;

			}
		}
		if (_em->getStage() == 6)
		{
			if (img_y > 20)
			{
				img_y -= 20;
			}

			
		}

		for (int i  = 0 ; i < 10; ++i)
		{ 
			if (_play->getpower() % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 875, 335, i, 0);
			}
			if ((_play->getpower() / 10) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 855, 335, i, 0);
			}
		}
		
		for (int i = 0; i < 10; ++i)
		{
			if (_play->getbomb() % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 855, 265, i, 0);
			}
		}
		
		for (int i = 0; i < 10; ++i)
		{
			if (_em->getplayHP() % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 855, 220, i, 0);
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			if (_play->getscoreCount() % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 915, 150, i, 0);
			}
			if ((_play->getscoreCount() / 10) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 895, 150, i, 0);
			}

			if ((_play->getscoreCount() / 100) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 875, 150, i, 0);
			}

			if ((_play->getscoreCount() / 1000) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 855, 150, i, 0);
			}

			if ((_play->getscoreCount() / 10000) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 835, 150, i, 0);
			}

			if ((_play->getscoreCount() / 100000) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 815, 150, i, 0);
			}

			if ((_play->getscoreCount() / 1000000) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 795, 150, i, 0);
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			if (_play->getbomCount() % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 975, 265, i, 0);
			}
			if ((_play->getbomCount() / 10) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 955, 265, i, 0);
			}

			if ((_play->getbomCount() / 100) % 10 == i)
			{
				IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), 935, 265, i, 0);
			}
		}
	



		
	
		if (KEYMANAGER->isToggleKey('5'))
		{
			IMAGEMANAGER->findImage("충돌중")->alphaRender(getMemDC(), 850, 420, alpha7);
		}
		else
		{
			IMAGEMANAGER->findImage("무적중")->alphaRender(getMemDC(), 850, 420, alpha8);
		}
		
	}


	
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

