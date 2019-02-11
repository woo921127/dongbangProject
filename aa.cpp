case E_E_FIRETYPE_4:
	POINTFLOAT tmpPos = _vEnemy[idx]->getPos();
	POINTFLOAT tmpPosBullet;
	double tmpRad = 40;
	double tmpAngle = 0;
	int circleBulletNum = 22;
	double bulletAngle = PI * 3 / 2;
	double additionalAngle = PI2 / (22 * 2 + 6 * 2);	//	��� �պ��ߴ�

	bulletImg = IMAGEMANAGER->findImage("mobBulletBig");
	frameX = 2;
	frameY = 0;

	//���ʿ� - 10����, 0������ �����ؼ�, 135������ ����
	tmpPos.x = tmpPos.x - tmpRad;
	tmpAngle = 0;	//	0������
	bulletAngle = PI / 2 * 3;	//	�Ѿ˰� - ������ ��������
	for (int i = 0; i < circleBulletNum; i++) {
		tmpPosBullet.x = tmpPos.x + tmpRad * cos(tmpAngle);
		tmpPosBullet.y = tmpPos.y + tmpRad * sin(tmpAngle);
		_mobBulletMgr->FireBullet(bulletImg, tmpPosBullet, tmpPosBullet, bulletAngle, E_E_MOB2_PINK_BULLETSPD,
			E_E_MOB2_PINK_BULLETRAD, frameX, frameY, 0, -1);
		tmpAngle -= (PI / 4 * 5) / circleBulletNum;
		bulletAngle -= additionalAngle;
	}

	//������ - 5����, 180������ �����ؼ�, 45������ ����
	tmpPos = _vEnemy[idx]->getPos();
	tmpPos.x = tmpPos.x + tmpRad;
	tmpAngle = PI;	//	180������
	bulletAngle = PI / 2 * 3;	//	270��(�Ѿ˳��ư��°���)

	for (int i = 0; i < circleBulletNum; i++) {
		tmpPosBullet.x = tmpPos.x + tmpRad * cos(tmpAngle);
		tmpPosBullet.y = tmpPos.y + tmpRad * sin(tmpAngle);
		_mobBulletMgr->FireBullet(bulletImg, tmpPosBullet, tmpPosBullet, bulletAngle, E_E_MOB2_PINK_BULLETSPD,
			E_E_MOB2_PINK_BULLETRAD, frameX, frameY, 0, -1);
		tmpAngle += (PI / 4 * 5) / circleBulletNum;
		bulletAngle += additionalAngle;
	}

	//	������������ v�ڷ�
	tmpPos = _vEnemy[idx]->getPos();
	tmpPos.x = tmpPos.x - (tmpRad * abs(cos(PI / 4)) + tmpRad);
	tmpPos.y = tmpPos.y + tmpRad * abs(cos(PI / 4));
	bulletAngle = PI * 2 / 3;	//	120��(�Ѿ˳��ư��°���)

	const int tmpNum = 6;		//	additional angle�� ������. ���� ����/���ǵǾ�����


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