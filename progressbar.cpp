#include "stdafx.h"
#include "progressbar.h"


progressbar::progressbar()
{
}


progressbar::~progressbar()
{
}

HRESULT progressbar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	{
		string imgName = AppendInt("frontBar", width);
		string fileName = MakeImageName("hpBarTop");
		_topImgName = imgName;
		semibossHpbar = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	{
		string imgName = AppendInt("backBar", width);
		string fileName = MakeImageName("hpBarBottom");
		_backImgName = imgName;
		semibossHpbarback = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	//프로그레스 바 이미지의 크기가 가로크기가 된다.
	_width = semibossHpbarback->GetWidth();

	return S_OK;
}

HRESULT progressbar::init(const char* backImgName, const char* frontImgName, int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	{
		string imgName = AppendInt(frontImgName, width);
		string fileName = MakeImageName(frontImgName);
		_topImgName = imgName;
		semibossHpbar = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));

	}

	{
		string imgName = AppendInt(backImgName, width);
		string fileName = MakeImageName(backImgName);
		_backImgName = imgName;
		semibossHpbarback = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	//프로그레스 바 이미지의 크기가 가로크기가 된다.
	_width = semibossHpbarback->GetWidth();

	return S_OK;
}

void progressbar::release()
{
}

void progressbar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, semibossHpbar->GetWidth(), semibossHpbar->GetHeight());
}

void progressbar::render()
{
	//렌더는 그려주는 순서 영향을 받는다. 그려지는 순서대로 앞으로 나온다
	IMAGEMANAGER->render(_backImgName, getMemDC()
		, _rcProgress.left + semibossHpbarback->GetWidth() / 2
		, _y + semibossHpbarback->GetHeight() / 2
		, 0, 0
		, semibossHpbarback->GetWidth()
		, semibossHpbarback->GetHeight());

	//앞에 그려지는 게이지의 가로크기를 조절한다.
	IMAGEMANAGER->render(_topImgName, getMemDC()
		, _rcProgress.left + semibossHpbarback->GetWidth() / 2
		, _y + semibossHpbarback->GetHeight() / 2
		, 0, 0
		, _width, semibossHpbarback->GetHeight());

	Rectangle(getMemDC(), _rcProgress);

}

void progressbar::setGauge(float currentGauge, float maxGauge)
{
	//수치가 들어오면 계산해준다.
	_width = (currentGauge / maxGauge) * semibossHpbarback->GetWidth();
}
