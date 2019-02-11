#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{

	play = IMAGEMANAGER->addFrameImage("플레이어", "player1.bmp", 320, 50, 8, 1, true, RGB(255, 0, 255));
	
	playFly = IMAGEMANAGER->addFrameImage("플레이어fly", "playfly1.bmp", 2040, 120, 17, 1, true, RGB(0, 0, 0));

	playcount = 255;

	play->setAlpahBlend(true, playcount);

	play->SetX(340);
	play->SetY(WINSIZEY - 100);


	playFly->SetX(play->GetX());
	playFly->SetY(play->GetY());


	_state = PLAY_IDLE;

	playBomb = IMAGEMANAGER->addFrameImage("플레이어폭탄", "Bombimg2.bmp", 3600, 400, 9, 1, true, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("hpbar", "hpbar.bmp", 580, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bosshpbar", "bosshpbar.bmp", 580, 5, true, RGB(255, 0, 255));
	_playbullet = new playbullet;
	_playbullet->init(5000, 750);


	_item = new ItemManager;
	_item->init();


	_Bomb = new Bomb;
	_Bomb->init(1, 150);


	_maxHP = 580;
	_bossMaxHP = 580;
	minionHP = minionHP2 = 5;

	HPbar = RectMake(70, 35, _maxHP,5);
	bossHPbar = RectMake(70, 35, _bossMaxHP, 5);


itemcount = 3;

_HPcheck._semibossHp = 200;
_HPcheck._lastbossHp = 1000;
excount = 600;

check = false;
bomcheck = false;
_power = 0;

return S_OK;
}

void player::release()
{
}

void player::update()
{
	playMove();
	_playbullet->update();
	_Bomb->update();
	_item->update();
	bulletMinionCollision();
	//BombMinionCollision();


	HPbar = RectMake(70, 35, _maxHP, 5);
	bossHPbar = RectMake(70, 35, _bossMaxHP, 5);
	if (_em->getStage() == 6)
	{
		_count2++;
		_count1++;
	}

	

}

void player::render()
{
	_Bomb->render();
	_item->render();
	playFly->frameRender(getMemDC(), playFly->GetX(), playFly->GetY(), playFly->getFrameX(), 0);
	
	//_semibossHp->render();

	if (itemcount > 0)
	{
		if (KEYMANAGER->isToggleKey('C'))
		{
			if (check == false)
			{
				excount--;
				if (excount >= 0)
				{
					playBomb->frameRender(getMemDC(), playBomb->GetX(), playBomb->GetY(), playBomb->getFrameX(), 0);
				}
				else
				{
					check = true;
					itemcount -= 1;
					excount = 600;
				}
			}
			else if (check == true)
			{
				if (KEYMANAGER->isOnceKeyUp('C'))
				{
					check = false;
				}
			}
		}
	}

	if (_em->getcount() == 0)
	{
		play->frameRender(getMemDC(), play->GetX(), play->GetY(), play->getFrameX(), 0);
	}
	else if (_em->getcount() != 0)
	{
		playcount -= 25;
		play->alphaFrameRender(getMemDC(), play->GetX(), play->GetY(), play->getFrameX(), 0, playcount);
	}





	if (_em->getStage() == 3)
	{
		Rectangle(getMemDC(), HPbar);
		IMAGEMANAGER->findImage("hpbar")->render(getMemDC(), HPbar.left, HPbar.top, 0, 0, _maxHP, 5);
	}

	if (_em->getStage() == 6)
	{
		Rectangle(getMemDC(), bossHPbar);
		IMAGEMANAGER->findImage("bosshpbar")->render(getMemDC(), bossHPbar.left, bossHPbar.top, 0, 0, _bossMaxHP, 5);
	}




	_playbullet->render();
	char str[128];
	//sprintf_s(str,"x:%f y:%f ", play->GetX(), play->GetY());
	//TextOut(getMemDC(), 200, 50, str, strlen(str));
	//
}


void player::playMove()
{
	if(_em->getcount2() == 0)
	{ 
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && play->GetX() > 60)
	{
		play->SetX(play->GetX() - 4);
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			play->SetX(play->GetX() + 2);
			
		}
		_state = PLAY_LEFT_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_state = PLAY_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && play->GetX() + play->GetWidth() < 938)
	{
		play->SetX(play->GetX() + 4);

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			play->SetX(play->GetX() - 2);

		}
		_state = PLAY_RIGHT_MOVE;

	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_state = PLAY_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && play->GetY() > 30)
	{
		play->SetY(play->GetY() - 4);

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			play->SetY(play->GetY() + 2);

		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && play->GetY() + play->GetHeight() < WINSIZEY -30)
	{
		play->SetY(play->GetY() + 4);
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			play->SetY(play->GetY() - 2);

		}
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		_firecount++;
		if (_firecount % 3 == 0)
		{
			if (_em->getStage() == 6)
			{
				if (_count2 > 150)
				{
					_playbullet->fire(play->GetCenterX(), play->GetY() - 10, PI / 2, 15.f);
				}
			}
			else
			_playbullet->fire(play->GetCenterX(), play->GetY() - 10, PI / 2, 15.f);
		}
		if (_power >= 10)
		{
			_shift++;
			if (_firecount %3 == 0)
			{  
		
				if (_em->getStage() == 6)
				{
					if (_count1 > 150)
					{
						if (_shift <= 85)
						{
							_playbullet->fire2(play->GetCenterX() - 40 + _shift, play->GetCenterY(), PI / 2, 5.f);
							_playbullet->fire2(play->GetCenterX() + 40 - _shift, play->GetCenterY(), PI / 2, 5.f);
						}
						if (_shift >= 84)
						{
							_shift = 0;
						}
						
					}
				}
				else
				{
		
					if (_shift <= 85)
					{
						_playbullet->fire2(play->GetCenterX() - 40 + _shift, play->GetCenterY(), PI / 2, 5.f);
						_playbullet->fire2(play->GetCenterX() + 40 - _shift, play->GetCenterY(), PI / 2, 5.f);
					}
					if (_shift >= 84)
					{
						_shift = 0;
					}
					
				}
			}
		}
	
	}
}



		playBomb->SetX(play->GetX() - 182);
		playBomb->SetY(play->GetY() - 178);
	
		playFly->SetX(play->GetX() - 42);
		playFly->SetY(play->GetY() - 25);



	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];

		vector<string> vStr;

		vStr.push_back(itoa(play->GetX(), temp, 10));
		vStr.push_back(itoa(play->GetY(), temp, 10));

		TXTDATA->txtSave("세이브.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		char tmep[128];

		vector<string> vStr;

		vStr = TXTDATA->txtLoad("세이브.txt");


		play->SetX(atoi(vStr[0].c_str()));
		play->SetY(atoi(vStr[1].c_str()));
	}

	_BombCount++;
	if (_BombCount % 1 == 0)
	{

		_Bombindex++;
		playBomb->SetFrameX(_Bombindex);

		if (_Bombindex > 7) _Bombindex = 1;
		
		_BombCount = 0;
	}


	flycount++;
	if (flycount % 1 == 0)
	{
		flyindex++;
		playFly->SetFrameX(flyindex);

		if (flyindex > 17) flyindex = -1;

		flycount = 0;
	}

	_count++;

	if (_count % 6 == 0)
	{
		if (_state == PLAY_IDLE)
		{
			_index++;
			play->SetFrameX(_index);

			if (_index > 2) _index = -1;
		}


		if (_state == PLAY_RIGHT_MOVE)
		{
			_index = 6;
			_index++;
			play->SetFrameX(_index);

			if (_index >= 5) _index = 5;
		}
		if (_state == PLAY_LEFT_MOVE)
		{
			_index = 4;
			_index++;
			play->SetFrameX(_index);

			if (_index >= 3) _index = 3;
		}
		_count = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_HPcheck._lastbossHp -= 10;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_HPcheck._lastbossHp += 10;
	}

	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_power += 10;

	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		itemcount += 1;
	}
	
}

void player::bulletMinionCollision()
{
	RECT temp;
	RECT plrc = RectMakeCenter(play->GetCenterX(), play->GetCenterY(), 45, 45);
	
		for (int i = 0; i < _item->getVItem().size();)
		{
			if (IntersectRect(&temp, &plrc, &_item->getVItem()[i].rc))
			{
				_item->deleteitem(i);
				_power += 1;
				playscore += 1;

				break;
			}
			else { i++; }
		}




//=============================================================================================================================//
	for (int i = 0; i < _playbullet->getVplaybullet().size(); i++)
	{
		
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			if (IntersectRect(&temp, &_playbullet->getVplaybullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				
				minionHP --;
				playscore += 2;
				_playbullet->deleteplaybullet(i);
				if (minionHP <= 0)
				{
					_item->createItem(_em->getVMinion()[j]->getRect().left + 10,_em->getVMinion()[j]->getRect().top);
					
					_em->deleteMinion(j);

					minionHP = 5;
				}
				break;
			}
			
		}

	}


	for (int i = 0; i < _playbullet->getVplaybullet().size(); i++)
	{
		for (int j = 0; j < _em->getV2Minion().size(); j++)
		{
			if (IntersectRect(&temp, &_playbullet->getVplaybullet()[i].rc, &_em->getV2Minion()[j]->getRect()))
			{
				minionHP2--;
				playscore += 2;
				_playbullet->deleteplaybullet(i);
				if(minionHP2 <=0)
				{ 
				_item->createItem(_em->getV2Minion()[j]->getRect().left + 10, _em->getV2Minion()[j]->getRect().top);
				_em->delete2Minion(j);
				minionHP2 = 5;
				}
				break;
			}
		}
	}

	for (int i = 0; i < _playbullet->getVplaybullet().size(); i++)
	{
		for (int j = 0; j < _em->getV3Minion().size(); j++)
		{
			if (IntersectRect(&temp, &_playbullet->getVplaybullet()[i].rc, &_em->getV3Minion()[j]->getRect()))
			{
				_em->delete3Minion(j);
				_playbullet->deleteplaybullet(i);
				break;
			}
		}
	}

	for (int i = 0; i < _playbullet->getVplaybullet().size(); i++)
	{
		for (int j = 0; j < _em->getVBoss().size(); j++)
		{
			if (IntersectRect(&temp, &_playbullet->getVplaybullet()[i].rc, &_em->getVBoss()[0]->getRect()))
			{
				playscore += 12;

				if(_bossMaxHP >= 117)
				{ 
				_bossMaxHP -= 0.257f;
				}
				if (_bossMaxHP <= 117)
				{
				_bossMaxHP -= 0.105f;
				}
				_playbullet->deleteplaybullet(i);
				if(_bossMaxHP <= 0)
				{ 
					_em->deleteBoss(0);
				}
				break;
			}
		}
	}

	for (int i = 0; i < _playbullet->getVplaybullet().size(); i++)
	{
		for (int j = 0; j < _em->getVsemiBoss().size(); j++)
		{
			if (IntersectRect(&temp, &_playbullet->getVplaybullet()[i].rc, &_em->getVsemiBoss()[0]->getRect()))
			{
				playscore += 7;
			    _maxHP -= 0.734f;
				crash++;
				_playbullet->deleteplaybullet(i);
				if (_maxHP <= 0)
				{
					_em->deletesemiBoss(0);
					_maxHP = 580;
				}
				break;
			}
		}
	}
}

void player::BombMinionCollision()
{
	RECT temp;

	for (int i = 0; i < _Bomb->getVplayBomb().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			if (IntersectRect(&temp, &_Bomb->getVplayBomb()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_em->deleteMinion(j);
				break;
				
			}
		}
	}
}







