#pragma once
#include "gameNode.h"

class progressbar : public gameNode
{
private:
	RECT _rcProgress;		//���α׷��� �� ��Ʈ
	float _x, _y;			//���α׷��� �� ��ǥ
	float _width;			//����ũ��

	string _topImgName;
	string _backImgName;


	image* semibossHpbar;
	image* semibossHpbarback;

public:
	progressbar();
	~progressbar();

	HRESULT init(int x, int y, int width, int height);
	HRESULT init(const char* backImgName, const char* frontImgName, int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

};

