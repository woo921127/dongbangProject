case E_E_FIRETYPE_4:
	POINTFLOAT tmpPos = _vEnemy[idx]->getPos();
	POINTFLOAT tmpPosBullet;
	double tmpRad = 40;
	double tmpAngle = 0;
	int circleBulletNum = 22;
	double bulletAngle = PI * 3 / 2;
	double additionalAngle = PI2 / (22 * 2 + 6 * 2);	//	요거 손봐야댐

	bulletImg = IMAGEMANAGER->findImage("mobBulletBig");
	frameX = 2;
	frameY = 0;

	//왼쪽원 - 10도씩, 0도에서 시작해서, 135도에서 끝남
	tmpPos.x = tmpPos.x - tmpRad;
	tmpAngle = 0;	//	0도시작
	bulletAngle = PI / 2 * 3;	//	총알각 - 위부터 왼쪽으로
	for (int i = 0; i < circleBulletNum; i++) {
		tmpPosBullet.x = tmpPos.x + tmpRad * cos(tmpAngle);
		tmpPosBullet.y = tmpPos.y + tmpRad * sin(tmpAngle);
		_mobBulletMgr->FireBullet(bulletImg, tmpPosBullet, tmpPosBullet, bulletAngle, E_E_MOB2_PINK_BULLETSPD,
			E_E_MOB2_PINK_BULLETRAD, frameX, frameY, 0, -1);
		tmpAngle -= (PI / 4 * 5) / circleBulletNum;
		bulletAngle -= additionalAngle;
	}

	//우측원 - 5도씩, 180도에서 시작해서, 45도에서 끝남
	tmpPos = _vEnemy[idx]->getPos();
	tmpPos.x = tmpPos.x + tmpRad;
	tmpAngle = PI;	//	180도시작
	bulletAngle = PI / 2 * 3;	//	270도(총알날아가는각도)

	for (int i = 0; i < circleBulletNum; i++) {
		tmpPosBullet.x = tmpPos.x + tmpRad * cos(tmpAngle);
		tmpPosBullet.y = tmpPos.y + tmpRad * sin(tmpAngle);
		_mobBulletMgr->FireBullet(bulletImg, tmpPosBullet, tmpPosBullet, bulletAngle, E_E_MOB2_PINK_BULLETSPD,
			E_E_MOB2_PINK_BULLETRAD, frameX, frameY, 0, -1);
		tmpAngle += (PI / 4 * 5) / circleBulletNum;
		bulletAngle += additionalAngle;
	}

	//	왼쪽직선부터 v자로
	tmpPos = _vEnemy[idx]->getPos();
	tmpPos.x = tmpPos.x - (tmpRad * abs(cos(PI / 4)) + tmpRad);
	tmpPos.y = tmpPos.y + tmpRad * abs(cos(PI / 4));
	bulletAngle = PI * 2 / 3;	//	120도(총알날아가는각도)

	const int tmpNum = 6;		//	additional angle에 영향줌. 위에 선언/정의되어있음


	double tmpVecX = abs((_vEnemy[idx]->getPos().x - tmpPos.x)) / (double)tmpNum;
	double tmpVecY = tmpVecX;
	tmpPosBullet = tmpPos;
	for (int i = 0; i < tmpNum * 2; i++) {
		_mobBulletMgr->FireBullet(bulletImg, tmpPosBullet, tmpPosBullet, bulletAngle, E_E_MOB2_PINK_BULLETSPD,
			E_E_MOB2_PINK_BULLETRAD, frameX, frameY, 0, -1);
		if (i < tmpNum) {
			tmpPosBullet.x += tmpVecX;
			tmpPosBullet.y += tmpVecY;
		}
		else {
			tmpPosBullet.x += tmpVecX;
			tmpPosBullet.y -= tmpVecY;
		}
		bulletAngle -= additionalAngle;


	}