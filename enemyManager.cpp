#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	//_bullet = new bullet;
	//_bullet->init("bullet", 1000, 10000);

	boss3pt = IMAGEMANAGER->addFrameImage("boss3pt", "boss3pt.bmp", 0, 0, 970, 97, 10, 1, true, RGB(255, 0, 255));
	boss3pt1 = IMAGEMANAGER->addFrameImage("boss3pt1", "boss3pt1.bmp", 0, 0, 970, 97, 10, 1, true, RGB(255, 0, 255));

	semiboss3 = IMAGEMANAGER->addFrameImage("semiboss3", "semiboss3.bmp", 0, 0, 5600, 140, 40, 1, true, RGB(0, 0, 0));

	lastboss = IMAGEMANAGER->addFrameImage("boss", "boss.bmp", 0, 0, 2772, 130, 18, 1, true, RGB(255, 0, 255));

	bossmove = IMAGEMANAGER->addFrameImage("bossmove", "bossmove.bmp", 0, 0, 1800, 192, 9, 1, true, RGB(0, 0, 0));

	_bulletPool = new BulletPool;
	_bulletPool->init("minionbullet", 50000, 10000);

	_bulletPool2 = new BulletPool;
	_bulletPool2->init("minionbullet2", 50000, 10000);

	_bulletPool3 = new BulletPool;
	_bulletPool3->init("minionbullet3", 50000, 10000);

	_bulletPool4 = new BulletPool;
	_bulletPool4->init("minionbullet4", 50000, 10000);

	_semibullet = new BulletPool;
	_semibullet->init("semibullet", 50000, 1000);


	_bossbullet = new BulletPool;
	_bossbullet->init("bossbullet", 50000, 10000);

	_bossbullet2 = new BulletPool;
	_bossbullet2->init("bossbullet2", 50000, 10000);

	_bossbullet3 = new BulletPool;
	_bossbullet3->init("bossbullet3", 50000, 10000);

	_bossbullet4 = new BulletPool;
	_bossbullet4->init("bossbullet4", 50000, 10000);

	_bossbullet5 = new BulletPool;
	_bossbullet5->init("bossbullet5", 50000, 10000);



	_stage = ST_ONE;
	_bul = BUL_ONE;
	_bossbul = BUL_BOSS_ONE;
	speed = 2.f;
	speed2 = 2.f;
	score = 0;
	angle2 = 0;
	speed4 = 2.f;
	speed5 = 1.f;
	playerHP = 3;
	
	_semibossHP = 100;
	check = false;
	pt2change = false;
	aa = false;
	crashcheck = false;
	misscheck = false;
	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
	SAFE_DELETE(_bulletPool);
	SAFE_DELETE(_bulletPool2);
	SAFE_DELETE(_semibullet);
	SAFE_DELETE(_bossbullet);
	SAFE_DELETE(_bossbullet2);
	SAFE_DELETE(_bossbullet3);
	SAFE_DELETE(_bossbullet4);
	SAFE_DELETE(_bossbullet5);
}

void enemyManager::update()
{
	//===============필드몹==========================//
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();

	}
	for (_vi2Minion = _v2Minion.begin(); _vi2Minion != _v2Minion.end(); ++_vi2Minion)
	{
		(*_vi2Minion)->update();

	}
	for (_vi3Minion = _v3Minion.begin(); _vi3Minion != _v3Minion.end(); ++_vi3Minion)
	{
		(*_vi3Minion)->update();

	}
	//================보스===========================//
	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->update();

	}

	for (_visemiBoss = _vsemiBoss.begin(); _visemiBoss != _vsemiBoss.end(); ++_visemiBoss)
	{
		(*_visemiBoss)->update();

	}


	//_bullet->update();



	_bulletPool->update();
	_bulletPool2->update();
	_bulletPool3->update();
	_bulletPool4->update();
	_semibullet->update();
	_bossbullet->update();
	_bossbullet2->update();
	_bossbullet3->update();
	_bossbullet4->update();
	_bossbullet5->update();



	minionBulletFire(_bul);
	BossBulletFire(_bossbul);

	if (_vMinion.empty() && _v2Minion.empty() && _v3Minion.empty() && _vBoss.empty() && _vsemiBoss.empty())
	{
		_stage++;
		_bul++;
		setMinion_and_boss();
	}

	if (KEYMANAGER->isToggleKey('5'))
	{
		BulletplayCollision();
	}
	



	deleteSideMinion();
	BombMinionBulletCollision();
	bulletsideout();
	bulletpt1erase();
	bulletpt2erase();
	bulletpt3erase();
	bulletpt4erase();




	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_bossbul++;
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_bossbul--;
	}


	if (crashcheck == true)
	{
		_play->getImage()->SetFrameX(0);
		crashcount++;
		if (_play->getImage()->GetY() > WINSIZEY - 100)
		{
			_play->getImage()->SetY(_play->getImage()->GetY() - 4);
		}
		else if (crashcount >= 20)
		{
			crashcheck = false;
			crashcount = 0;
		}
	}


	if (misscheck == true)
	{	
		misscount++;
		if (misscount > 130)
		{
			misscheck = false;
			misscount = 0;
		}
	}

	if (_stage == ST_THREE)
	{
		semibosspt++;

		if (semibosspt % 3 == 0)
		{
			semiindex++;
			semiboss3->SetFrameX(semiindex);
			if (semiindex > 40) semiindex = 0;
		}

	}

	if (_stage == ST_SIX)
	{
		bosspt++;

		if (bosspt % 1 == 0)
		{
			bosindex++;
			bossmove->SetFrameX(bosindex);
			if (bosindex > 7) bosindex = -1;
		}

	}



}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	for (_vi2Minion = _v2Minion.begin(); _vi2Minion != _v2Minion.end(); ++_vi2Minion)
	{
		(*_vi2Minion)->render();
	}
	for (_vi3Minion = _v3Minion.begin(); _vi3Minion != _v3Minion.end(); ++_vi3Minion)
	{
		(*_vi3Minion)->render();
	}
	
	



	//================================================================================//

	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		EllipseMakeCenter(getMemDC(), _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(), 4,4);
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		RECT bossRc = (*_viBoss)->getRect();

		if (_stage == ST_SIX)
		{
			bossmove->frameRender(getMemDC(), bossRc.left + (bossRc.right - bossRc.left) / 2 - 98, bossRc.top + (bossRc.bottom - bossRc.top) / 2 - 40, bossmove->getFrameX(), 0);

			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232.5)
			{
				boss3pt->SetX(bossRc.left - 170);
				boss3pt->SetY(bossRc.top + (bossRc.bottom - bossRc.top) / 2 - 50);

				boss3pt1->SetX(bossRc.right + 70);
				boss3pt1->SetY(bossRc.top + (bossRc.bottom - bossRc.top) / 2 - 50);

				boss3pt->frameRender(getMemDC(), boss3pt->GetX(), boss3pt->GetY(), boss3pt->getFrameX(), 0);
				boss3pt1->frameRender(getMemDC(), boss3pt1->GetX(), boss3pt1->GetY(), boss3pt1->getFrameX(), 0);
			}
		}
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->render();
	}

	//_bullet->render();
	_bulletPool->render();
	_bulletPool2->render();
	_bulletPool3->render();
	_bulletPool4->render();
	_semibullet->render();
	_bossbullet->render();
	_bossbullet2->render();
	_bossbullet3->render();
	_bossbullet4->render();
	_bossbullet5->render();

	
	for (_visemiBoss = _vsemiBoss.begin(); _visemiBoss != _vsemiBoss.end(); ++_visemiBoss)
	{
		RECT semirc = (*_visemiBoss)->getRect();
		if (_stage == ST_THREE)
		{	
			semiboss3->frameRender(getMemDC(), semirc.left + (semirc.right - semirc.left)/ 2 - 70, semirc.top + (semirc.bottom - semirc.top) / 2 - 55, semiboss3->getFrameX(), 0);	
			if (_play->getSemiBossHp() <= 200)
			{
				IMAGEMANAGER->findImage("fild")->render(getMemDC(), semirc.left -150, semirc.top + (semirc.bottom - semirc.top) / 2 - 30);
				IMAGEMANAGER->findImage("fild")->render(getMemDC(), semirc.right + 90, semirc.top + (semirc.bottom - semirc.top)/2 - 30);	
			}
		}
	}
	for (_visemiBoss = _vsemiBoss.begin(); _visemiBoss != _vsemiBoss.end(); ++_visemiBoss)
	{
		(*_visemiBoss)->render();
	}
	
	char str[128];
	
	//sprintf_s(str, "보스 pt: %d  카운터 : %d", bopt4, bopt2count);
	//TextOut(getMemDC(), 120, 50, str, strlen(str));
}

void enemyManager::setMinion_and_boss()
{
	switch (_stage)
	{
	case ST_ONE:
	
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				enemy* monster;
				monster = new minion;
				if (i == 0)
				{
					monster->init("stageMinion", PointFMake(-300 + j * 50, 80 + j * 40));
					_vMinion.push_back(monster);
					monster->setType(ONE);
				}
				else if (i == 1)
				{
					monster->init("stageMinion", PointFMake(WINSIZEX - 40 - j * 50, 80 + j * 40));
					_v2Minion.push_back(monster);
					monster->setType(TWO);
				}
			}
		}
	
		break;
	case ST_TWO:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				enemy* monster;
				monster = new minion;
				if (i == 0)
				{
					monster->init("stageMinion", PointFMake(150, -200 - (j * 300)));
					_vMinion.push_back(monster);
					monster->setType(THREE);
				}
				 if (i == 1)
				{
					monster->init("stageMinion", PointFMake(550, -200 - (j * 300)));
					_v2Minion.push_back(monster);
					monster->setType(FOUR);
				}
			}
		}
		break;
	case ST_THREE:
	{
		enemy* semiboss1;
		semiboss1 = new semiboss;	
	
		semiboss1->setAngle((PI / 2));
		semiboss1->init("semiBoss", PointFMake(360, -200));
		_vsemiBoss.push_back(semiboss1);
		semiboss1->setType(FIVE);						
	}
		break;
	case ST_FOUR:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				enemy* monster;
				monster = new minion;
				if (i == 0)
				{
					monster->setAngle((PI));
					monster->init("stageMinion", PointFMake(90, WINSIZEY + 550 + j * 100));
					_vMinion.push_back(monster);
					monster->setType(SEVEN);
				}
				if (i == 1)
				{
					monster->setAngle((PI));
					monster->init("stageMinion", PointFMake(640, WINSIZEY + 550 + j * 100));
					_v2Minion.push_back(monster);
					monster->setType(EIGHT);
				}
			}
		}
		break;
	
	case ST_FIVE:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				enemy* monster;
				monster = new minion;
				if (i == 0)
				{
					monster->setAngle((PI));
					monster->init("stageMinion", PointFMake(-150 - j * 50, -300));
					_vMinion.push_back(monster);
					monster->setType(NINE);
				}
				if (i == 1)
				{
					monster->setAngle((PI));
					monster->init("stageMinion", PointFMake(1200 - j * 50, -350));
					_v2Minion.push_back(monster);
					monster->setType(TEN);
				}
			}
		}
		break;
	
	case ST_SIX:
		enemy* boss1;
		boss1 = new boss;
		boss1->init("boss", PointFMake(-400, -1000));
		_vBoss.push_back(boss1);
		boss1->setType(ELEVEN);
		break;
	}
}
//=============================================미니언 불렛 패턴====================================================//
void enemyManager::minionBulletFire(int fire)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		RECT rc = (*_viMinion)->getRect();

		switch (_bul)
		{
		case BUL_ONE:
			if ((*_viMinion)->bulletCountFire())
			{
				_bulletPool4->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, -(PI / 2) , 5.0f);
			}
			break;
		case BUL_TWO:
			if ((*_viMinion)->bulletCountFire())
			{
				mini2angle += PI / 180;
				for (int j = 0; j < _vMinion.size(); ++j)
				{
					if (_vMinion[j]->getRect().top > 0 )
					{
						for (int i = 0; i < 4; i += 1)
						{
							_bulletPool4->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, - (PI / 2 * 7) * i * (PI / 180) * 8 + mini2angle, 7.0f);
						}
					}
				}
			}
			break;
		
		case BUL_FOUR:
			if ((*_viMinion)->bullet4CountFire())
			{
				_count++;
				if (_count >= 300 && _count <= 470)
				{
					_bulletPool4->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
				}
			}
			break;
		case BUL_FIVE:
			if ((*_viMinion)->bullet4CountFire())
			{
				_count2++;
				if (_count2 >= 200 && _count2 <= 370)
				{
					_bulletPool4->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
				}
			}
			break;
		}
	}

	//=======================================================2번째벡터미사일패턴==================================================================//

	for (_vi2Minion = _v2Minion.begin(); _vi2Minion != _v2Minion.end(); ++_vi2Minion)
	{

		RECT rc = (*_vi2Minion)->getRect();
		switch (_bul)
		{
		case BUL_ONE:
			if ((*_vi2Minion)->bulletCountFire())
			{
				_bulletPool3->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, -(PI / 2), 5.0f);
			}
			break;

		case BUL_TWO:
			if ((*_vi2Minion)->bulletCountFire())
			{
				mini2angle += PI / 180;
				for (int j = 0; j < _v2Minion.size(); ++j)
				{
					if (_v2Minion[j]->getRect().top > 0)
					{
						for (int i = 0; i < 4; i += 1)
						{
							_bulletPool3->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, -(PI / 2 * 7) * i * (PI / 180) * 8 + mini2angle, 7.0f);
						}
					}
				}
			}
			break;
		case BUL_FOUR:

			if ((*_vi2Minion)->bullet4CountFire())
			{
				_count3++;
				if (_count3 >=300 && _count3 <= 470)
				{
					_bulletPool3->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
				}
			}
			break;
		case BUL_FIVE:
			if ((*_vi2Minion)->bullet4CountFire())
			{
				_count4++;
				if (_count4 >= 200 && _count4 <= 370)
				{
					_bulletPool3->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 5, getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
				}
			}
		}

	}
		//==================================중간보스 미사일 패턴===================================================//

	for (_visemiBoss = _vsemiBoss.begin(); _visemiBoss != _vsemiBoss.end(); ++_visemiBoss)
	{
		RECT semirc = (*_visemiBoss)->getRect();
		switch (_bul)
		{
		case BUL_THREE:
			if ((*_visemiBoss)->bullet3CountFire())
			{
				if ((*_visemiBoss)->getRect().bottom >= 200)
				{
					for (int i = 0; i < 11; ++i)
					{
						_bulletPool->fire(semirc.left + (semirc.right - semirc.left) / 2, semirc.bottom + 5, -(PI / 2 + 45) + (i * 0.2), 7.0f);
					}				
				}		
			}
	
				if (_play->getSemiBossHp() <= 200)
				{
					if ((*_visemiBoss)->bullet5CountFire())
					{
						_semicount++;
						semiangle += (PI / 180) * 10;
						_bulletPool2->fire(semirc.left - 120, semirc.top + (semirc.bottom - semirc.top) / 2, (PI / 180) * (PI / 180 * 5150) + semiangle, 5.f);
						_bulletPool2->fire(semirc.right + 120, semirc.top + (semirc.bottom - semirc.top) / 2, (PI / 180) * (PI / 180 * 10300) - semiangle, 5.f);

						if (_semicount % 150 == 0)
						{
							_semibullet->fire(semirc.left - 120, semirc.top + (semirc.bottom - semirc.top) / 2, getAngle(semirc.left - 120, semirc.top + (semirc.bottom - semirc.top) / 2, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
							_semibullet->fire(semirc.right + 120, semirc.top + (semirc.bottom - semirc.top) / 2, getAngle(semirc.right + 120, semirc.top + (semirc.bottom - semirc.top) / 2, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
						}
					}
				}
			}
			break;
		}
	}
//===============================================보스 미사일 패턴====================================================//
void enemyManager::BossBulletFire(int fire)
{
	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		RECT bossRc = (*_viBoss)->getRect();
		switch (_bossbul)
		{
		case BUL_BOSS_ONE:  //1패턴
			if(_play->getLastBossHp() <= 580 && _play->getLastBossHp() >= 464.5)
			{ 
				if ((*_viBoss)->bulletCountFire())
				{
					_count5++;
					if (_count5 >= 50)
					{
						
						_bulletPool2->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, getAngle(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom, _play->getImage()->GetCenterX(), _play->getImage()->GetCenterY()), 10.0f);
					}
					
				}
				if ((*_viBoss)->bullet4CountFire())
				{
					angle += PI / 180;
					if (_count5 >= 50 && _count5 % 10 == 0)
					{
						for (int i = 0; i < 360; i += 8)
						{
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 57) + angle, 6.0f);
						}
					}
				}
			}
//============================================2패턴==========================================//
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348.5)
			{
				_count8++;
				if (_count8 >= 100)
				{
			
					
					if ((*_viBoss)->bullet6CountFire())
					{
						if (pt2change == false)
						{
							//angle2 = PI / 180;

							if (angle2 <= (PI / 180 * 18))
							{
								angle2 += (PI / 180) * 2;
							}

							if (angle2 > (PI / 180 * 18))
							{
								pt2change = true;
								angle2 = (PI / 180) * 18;
							}
						}
						if (pt2change == true)
						{


							if (angle2 >= (PI / 180))
							{
								angle2 -= (PI / 180) * 2;
							}
							if (angle2 <= (PI / 180))
							{
								pt2change = false;
								angle2 = PI / 180;
							}
						}
						pt2angle = 2.2f;
						pt2angle2 = 0.5f;
						if (pt2angle < 7)
						{
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 1.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 1.5f, speed4);
							
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle)  + 3.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 3.5f, speed4);
							
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 2.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 2.5f, speed4);
							
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 4.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 4.5f, speed4);
							
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 5.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 5.5f, speed4);
							
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 6.5f, speed4);
							_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 6.5f, speed4);
//======================================================== 파란색 ==========================================//

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 1.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 1.f, speed5);

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 2.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 2.f, speed5);

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 3.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 3.f, speed5);

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 4.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 4.f, speed5);

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 5.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 5.f, speed5);

							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * pt2angle) + 6.f, speed5);
							_bulletPool3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, 0 + (angle2 * -pt2angle) + 6.f, speed5);
						}
					}
				}
			}
//============================================3패턴==========================================//
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232.5)
			{
				
					pt3count++;

					if (pt3count % 5 == 0)
					{
						index++;
						boss3pt->SetFrameX(index);
						if (index > 10) index = 10;
					}
					if (pt3count % 5 == 0)
					{
						index++;
						boss3pt1->SetFrameX(index);
						if (index > 10) index = 10;
					}


				_count9++;
				if (_count9 >= 120)
				{
					if ((*_viBoss)->bullet6CountFire())
					{
						angle3 += PI / 180 * 8;
						speed += 0.5;
						
							for (int i = 0; i < 45; i += 3)
							{
								_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI) * (PI / 180 * i * 50) + angle3, speed);
								_bulletPool2->fire(bossRc.left - 120, bossRc.top + (bossRc.bottom - bossRc.top) / 2, (PI) * (PI / 180 * i * 50) + angle3, speed);
								_bossbullet2->fire(bossRc.right + 120, bossRc.top + (bossRc.bottom - bossRc.top) / 2, (PI) * (PI / 180 * i * 50) + angle3, speed);
								if (speed > 7)
								{
									speed = 2;
									_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI) * (PI / 180 * i * 50) + angle3, speed);
									_bulletPool2->fire(bossRc.left - 120, bossRc.top + (bossRc.bottom - bossRc.top) / 2, (PI) * (PI / 180 * i * 50) + angle3, speed);
									_bossbullet2->fire(bossRc.right + 120, bossRc.top + (bossRc.bottom - bossRc.top) / 2, (PI) * (PI / 180 * i * 50) + angle3, speed);
								}
							}
						
					}
				}
			}
//============================================4패턴==========================================//
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116.5)
			{
				_count10++;
				if (_count10 >= 120)
				{
					if ((*_viBoss)->bullet5CountFire())
					{
						angle7 += (PI / 180) * 10;
						angle8 += (PI / 180);

						_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * 5150) + angle7, 5.f);
						_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * 10300) + angle7, 5.f);
						_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180) + angle7, 5.f);
						_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * 15450) + angle7, 5.f);
					}
					if ((*_viBoss)->bullet3CountFire())
					{
						for (int i = 0; i < 360; i += 8)
						{

							_bulletPool2->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 57) + angle8, 8.0f);
						}
					}
				}
			}
//============================================5패턴==========================================//
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0)
			{
				_count11++;
				if (_count11 > 100)
				{
					if ((*_viBoss)->bullet4CountFire())
					{
						_count6++;
						_count12++;
						angle4 += (PI / 180) * 9;
						angle5 += (PI / 180) * 5;
						angle6 += PI / 180;
						for (int i = 0; i < 2; i += 1)
						{
							_bossbullet->fire(65, WINSIZEY / 2 - 200, (PI / 4) * 7, 7.f);
							_bossbullet->fire(650, WINSIZEY / 2 - 200, (PI / 4) * 5, 7.f);

							if (check == false)
							{
								_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 10300), 3.f);
							}
							if (_count6 >= 40)
							{
								check = true;
								_bulletPool2->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 10300) + angle4, 3.f);
							}
							if (_count6 >= 70)
							{
								_bossbullet2->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 10300) - angle4, 3.f);
								_count7++;
							}
							if (_count6 >= 100)
							{
								_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 10300) - angle5, 5.f);
							}
							if (_count6 >= 130)
							{
								_bulletPool->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI / 180) * (PI / 180 * i * 10300) + angle5, 5.f);
							}

							if (_count6 >= 400)
							{
								_bossbullet->fire(250, 0, -(PI / 2), 7.f);
								_bossbullet->fire(465, WINSIZEY, (PI / 2), 7.f);
							}

							if (_count6 >= 70 && _count6 % 5 == 0)
							{
								if (_count12 % 3 == 0)
								{
									for (int i = 0; i < 16; i += 1)
									{
										_bossbullet3->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI) * (PI / 180 * i * 50) + angle6, 7.f);
									}
								}
								if (_count12 % 3 == 1)
								{
									for (int i = 0; i < 16; i += 1)
									{
										_bossbullet4->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI) * (PI / 180 * i * 50) + angle6, 7.f);
									}
								}
								if (_count12 % 3 == 2)
								{
									for (int i = 0; i < 16; i += 1)
									{
										_bossbullet5->fire(bossRc.left + (bossRc.right - bossRc.left) / 2, bossRc.bottom + 5, (PI) * (PI / 180 * i * 50) + angle6, 7.f);
									}
								}
							}
						}
					}
					if ((*_viBoss)->bullet3CountFire())
					{

						if (_count7 >= 50)
						{
							legth += (PI / 180) * 6;
							_bulletPool->fire(65, WINSIZEY / 2 - 200, (PI / 4) * 7 - legth, 5.f);
							_bulletPool->fire(650, WINSIZEY / 2 - 200, (PI / 4) * 5 + legth, 5.f);
						}

						if (_count7 >= 250)
						{
							_count7 = 0;
							legth = 0;
						}
					}
				}
			}
			break;
		}
	}
}


void enemyManager::BulletplayCollision()
{
	RECT temp;
	RECT rc = RectMakeCenter(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(), 2, 2);
	for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
	{
		if(misscheck == false)
		{ 
			if (IntersectRect(&temp, &rc, &_bulletPool->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY  + 100);
				crashcheck = true;
				misscheck = true;
			}
		}
		
	}

	for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bulletPool2->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
		
	}

	for (int i = 0; i < _bulletPool3->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bulletPool3->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
	
	}

	for (int i = 0; i < _bulletPool4->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bulletPool4->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
	}

	for (int i = 0; i < _semibullet->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_semibullet->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
			
			}
		}
	
	}

	for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bossbullet->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
	
	}

	for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bossbullet2->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
		
	}

	for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bossbullet3->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
		
	}

	for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bossbullet4->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
		
	}


	for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
	{
		if (misscheck == false)
		{
			if (IntersectRect(&temp, &rc, &_bossbullet5->getActiveBullets()[i]->getRC()))
			{
				score++;
				playerHP -= 1;
				_play->getImage()->SetX(340);
				_play->getImage()->SetY(WINSIZEY + 100);
				crashcheck = true;
				misscheck = true;
				
			}
		}
		
	}


}


void enemyManager::BombMinionBulletCollision()
{
	//RECT rc = _play->getPlayerBomb()->getVplayBomb()[0].rc;
	RECT temp;

	if (_play->getbomCount() >= 0 && _play->getbomCount() < 600)
	{
		for (int j = 0; j < _bulletPool->getActiveBullets().size(); j++)
		{

			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bulletPool->getActiveBullets()[j]->getRC().left + (_bulletPool->getActiveBullets()[j]->getRC().right - _bulletPool->getActiveBullets()[j]->getRC().left) / 2,
				_bulletPool->getActiveBullets()[j]->getRC().top + (_bulletPool->getActiveBullets()[j]->getRC().bottom - _bulletPool->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bulletPool->getActiveBullets()[j]->setActive(false);
			}
		}


		for (int j = 0; j < _bulletPool2->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bulletPool2->getActiveBullets()[j]->getRC().left + (_bulletPool2->getActiveBullets()[j]->getRC().right - _bulletPool2->getActiveBullets()[j]->getRC().left) / 2,
				_bulletPool2->getActiveBullets()[j]->getRC().top + (_bulletPool2->getActiveBullets()[j]->getRC().bottom - _bulletPool2->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bulletPool2->getActiveBullets()[j]->setActive(false);
			}
		}

		for (int j = 0; j < _bulletPool3->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bulletPool3->getActiveBullets()[j]->getRC().left + (_bulletPool3->getActiveBullets()[j]->getRC().right - _bulletPool3->getActiveBullets()[j]->getRC().left) / 2,
				_bulletPool3->getActiveBullets()[j]->getRC().top + (_bulletPool3->getActiveBullets()[j]->getRC().bottom - _bulletPool3->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bulletPool3->getActiveBullets()[j]->setActive(false);
			}
		}

		for (int j = 0; j < _bulletPool4->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bulletPool4->getActiveBullets()[j]->getRC().left + (_bulletPool4->getActiveBullets()[j]->getRC().right - _bulletPool4->getActiveBullets()[j]->getRC().left) / 2,
				_bulletPool4->getActiveBullets()[j]->getRC().top + (_bulletPool4->getActiveBullets()[j]->getRC().bottom - _bulletPool4->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bulletPool4->getActiveBullets()[j]->setActive(false);
			}
		}

		for (int j = 0; j < _semibullet->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_semibullet->getActiveBullets()[j]->getRC().left + (_semibullet->getActiveBullets()[j]->getRC().right - _semibullet->getActiveBullets()[j]->getRC().left) / 2,
				_semibullet->getActiveBullets()[j]->getRC().top + (_semibullet->getActiveBullets()[j]->getRC().bottom - _semibullet->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_semibullet->getActiveBullets()[j]->setActive(false);
			}
		}


		for (int j = 0; j < _bossbullet->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bossbullet->getActiveBullets()[j]->getRC().left + (_bossbullet->getActiveBullets()[j]->getRC().right - _bossbullet->getActiveBullets()[j]->getRC().left) / 2,
				_bossbullet->getActiveBullets()[j]->getRC().top + (_bossbullet->getActiveBullets()[j]->getRC().bottom - _bossbullet->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bossbullet->getActiveBullets()[j]->setActive(false);
			}

		}

		for (int j = 0; j < _bossbullet2->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bossbullet2->getActiveBullets()[j]->getRC().left + (_bossbullet2->getActiveBullets()[j]->getRC().right - _bossbullet2->getActiveBullets()[j]->getRC().left) / 2,
				_bossbullet2->getActiveBullets()[j]->getRC().top + (_bossbullet2->getActiveBullets()[j]->getRC().bottom - _bossbullet2->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bossbullet2->getActiveBullets()[j]->setActive(false);
			}
		}

		for (int j = 0; j < _bossbullet3->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bossbullet3->getActiveBullets()[j]->getRC().left + (_bossbullet3->getActiveBullets()[j]->getRC().right - _bossbullet3->getActiveBullets()[j]->getRC().left) / 2,
				_bossbullet3->getActiveBullets()[j]->getRC().top + (_bossbullet3->getActiveBullets()[j]->getRC().bottom - _bossbullet3->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bossbullet3->getActiveBullets()[j]->setActive(false);
			}
		}

		for (int j = 0; j < _bossbullet4->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bossbullet4->getActiveBullets()[j]->getRC().left + (_bossbullet4->getActiveBullets()[j]->getRC().right - _bossbullet4->getActiveBullets()[j]->getRC().left) / 2,
				_bossbullet4->getActiveBullets()[j]->getRC().top + (_bossbullet4->getActiveBullets()[j]->getRC().bottom - _bossbullet4->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bossbullet4->getActiveBullets()[j]->setActive(false);
			}
		}
		for (int j = 0; j < _bossbullet5->getActiveBullets().size(); j++)
		{
			if (getDistance(_play->getImage()->GetCenterX(), _play->getImage()->GetCenterY(),
				_bossbullet5->getActiveBullets()[j]->getRC().left + (_bossbullet5->getActiveBullets()[j]->getRC().right - _bossbullet5->getActiveBullets()[j]->getRC().left) / 2,
				_bossbullet5->getActiveBullets()[j]->getRC().top + (_bossbullet5->getActiveBullets()[j]->getRC().bottom - _bossbullet5->getActiveBullets()[j]->getRC().top) / 2)
				< 120)
			{
				_bossbullet5->getActiveBullets()[j]->setActive(false);
			}
		}
	}
}

	


void enemyManager::bulletsideout()
{
	for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
	{

		if (_bulletPool->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bulletPool->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410  || _bulletPool->getActiveBullets()[i]->getRC().right <= 60)
		{
			_bulletPool->getActiveBullets()[i]->setActive(false);
		}
	}
	for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
	{

		if (_bulletPool2->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bulletPool2->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410|| _bulletPool2->getActiveBullets()[i]->getRC().right <= 60)
		{
			_bulletPool2->getActiveBullets()[i]->setActive(false);
		}
	}
	for (int i = 0; i < _semibullet->getActiveBullets().size(); i++)
	{

		if (_semibullet->getActiveBullets()[i]->getRC().top >= WINSIZEY || _semibullet->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410|| _semibullet->getActiveBullets()[i]->getRC().right <= 60)
		{
			_semibullet->getActiveBullets()[i]->setActive(false);
		}
	}
	for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
	{

		if (_bossbullet->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bossbullet->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410|| _bossbullet->getActiveBullets()[i]->getRC().right <= 60)
		{
			_bossbullet->getActiveBullets()[i]->setActive(false);
		}
	}

	for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
	{

		if (_bossbullet2->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bossbullet2->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410 || _bossbullet2->getActiveBullets()[i]->getRC().right <= 60)
		{
			_bossbullet2->getActiveBullets()[i]->setActive(false);
		}
	}

	for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
	{

		if (_bossbullet3->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bossbullet3->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410|| _bossbullet3->getActiveBullets()[i]->getRC().right <= 60)
		{
			_bossbullet3->getActiveBullets()[i]->setActive(false);
		}
		for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
		{

			if (_bossbullet4->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bossbullet4->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410 || _bossbullet4->getActiveBullets()[i]->getRC().right <= 60)
			{
				_bossbullet4->getActiveBullets()[i]->setActive(false);
			}
		}
		for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
		{

			if (_bossbullet5->getActiveBullets()[i]->getRC().top >= WINSIZEY || _bossbullet5->getActiveBullets()[i]->getRC().left >= WINSIZEX - 410 || _bossbullet5->getActiveBullets()[i]->getRC().right <= 20)
			{
				_bossbullet5->getActiveBullets()[i]->setActive(false);
			}
		}

	}
}

void enemyManager::deleteMinion(int minionNum)
{
	_vMinion.erase(_vMinion.begin() + minionNum);
}

void enemyManager::delete2Minion(int minionNum)
{
	_v2Minion.erase(_v2Minion.begin() + minionNum);
}

void enemyManager::delete3Minion(int minionNum)
{
	_v3Minion.erase(_v3Minion.begin() + minionNum);
}

void enemyManager::deleteBoss(int minionNum)
{
	_vBoss.erase(_vBoss.begin() + minionNum);
}

void enemyManager::deletesemiBoss(int minionNum)
{
	_vsemiBoss.erase(_vsemiBoss.begin() + minionNum);
}

void enemyManager::bulletpt1erase()
{
	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bulletPool->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bulletPool2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bulletPool3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bulletPool3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}
	
	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bossbullet->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bossbullet2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bossbullet3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bossbullet4->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

	if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 == 0)
	{
		bopt2count = true;
	}
	if (bopt2count == true)
	{
		bopt2 += 1;

		for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 464 && _play->getLastBossHp() >= 348 && bopt2 < 70)
			{

				_bossbullet5->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt2 > 70)
		{
			bopt2count = false;
		}
	}

}

void enemyManager::bulletpt2erase()
{
	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bulletPool->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}
	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bulletPool2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}
	
	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bulletPool3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bulletPool3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}

	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bossbullet->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}

	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bossbullet2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}

	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bossbullet3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}

	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bossbullet4->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}

	if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 == 0)
	{
		bopt3count = true;
	}
	if (bopt3count == true)
	{
		bopt3 += 1;

		for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 348 && _play->getLastBossHp() >= 232 && bopt3 < 70)
			{

				_bossbullet5->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt3 > 70)
		{
			bopt3count = false;
		}
	}
}

void enemyManager::bulletpt3erase()
{
	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bulletPool->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bulletPool2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bulletPool3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bulletPool3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bossbullet->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bossbullet2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bossbullet3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}

	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bossbullet4->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}
	if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 == 0)
	{
		bopt4count = true;
	}
	if (bopt4count == true)
	{
		bopt4 += 1;

		for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 232 && _play->getLastBossHp() >= 116 && bopt4 < 70)
			{

				_bossbullet5->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt4 > 70)
		{
			bopt4count = false;
		}
	}
}

void enemyManager::bulletpt4erase()
{
	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bulletPool->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bulletPool->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}

	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bulletPool2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bulletPool2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}

	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bulletPool3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bulletPool3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}

	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bossbullet->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bossbullet->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}


	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bossbullet2->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bossbullet2->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}


	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bossbullet3->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bossbullet3->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}


	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bossbullet4->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bossbullet4->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}


	if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 == 0)
	{
		bopt5count = true;
	}
	if (bopt5count == true)
	{
		bopt5 += 1;

		for (int i = 0; i < _bossbullet5->getActiveBullets().size(); i++)
		{
			if (_play->getLastBossHp() <= 116 && _play->getLastBossHp() >= 0 && bopt5 < 70)
			{

				_bossbullet5->getActiveBullets()[i]->setActive(false);
			}
		}
		if (bopt5 > 70)
		{
			bopt5count = false;
		}
	}
}


void enemyManager::deleteSideMinion()
{
	if (_stage == ST_ONE)
	{
		for (int i = 0; i < _vMinion.size(); i++)
		{
			if (_vMinion[i]->getRect().left >= WINSIZEX - 245)
			{
				deleteMinion(i);
			}
		}
		for (int i = 0; i < _v2Minion.size(); i++)
		{
			if (_v2Minion[i]->getRect().right <= 0)
			{
				delete2Minion(i);
			}
		}

	}

	if (_stage == ST_TWO)
	{
		for (int i = 0; i < _vMinion.size(); i++)
		{
			if (_vMinion[i]->getRect().top >= WINSIZEY)
			{
				deleteMinion(i);
			}
		}
		for (int i = 0; i < _v2Minion.size(); i++)
		{
			if (_v2Minion[i]->getRect().top >= WINSIZEY)
			{
				delete2Minion(i);
			}
		}
	}

	if (_stage == ST_FOUR)
	{
		for (int i = 0; i < _vMinion.size(); i++)
		{
			if (_vMinion[i]->getRect().top >= WINSIZEY && _vMinion[i]->getRect().right >= 304)
			{
				deleteMinion(i);
			}
		}
		for (int i = 0; i < _v2Minion.size(); i++)
		{
			if (_v2Minion[i]->getRect().top >= WINSIZEY && _v2Minion[i]->getRect().left <= 426)
			{
				delete2Minion(i);
			}
		}
	}


	if (_stage == ST_FIVE)
	{
		for (int i = 0; i < _vMinion.size(); i++)
		{
			if (_vMinion[i]->getRect().top >= WINSIZEY -150 && _vMinion[i]->getRect().right <= 150)
			{
				deleteMinion(i);
			}
		}
		for (int i = 0; i < _v2Minion.size(); i++)
		{
			if (_v2Minion[i]->getRect().top >= WINSIZEY && _v2Minion[i]->getRect().left >= 450)
			{
				delete2Minion(i);
			}
		}
	}
}
