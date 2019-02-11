#pragma once
#include "gameNode.h"

class progressbar : public gameNode
{
private:
	RECT _rcProgress;		//프로그레스 바 렉트
	float _x, _y;			//프로그레스 바 좌표
	float _width;			//가로크기

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

