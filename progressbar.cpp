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

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
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

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
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
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�
	IMAGEMANAGER->render(_backImgName, getMemDC()
		, _rcProgress.left + semibossHpbarback->GetWidth() / 2
		, _y + semibossHpbarback->GetHeight() / 2
		, 0, 0
		, semibossHpbarback->GetWidth()
		, semibossHpbarback->GetHeight());

	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render(_topImgName, getMemDC()
		, _rcProgress.left + semibossHpbarback->GetWidth() / 2
		, _y + semibossHpbarback->GetHeight() / 2
		, 0, 0
		, _width, semibossHpbarback->GetHeight());

	Rectangle(getMemDC(), _rcProgress);

}

void progressbar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_width = (currentGauge / maxGauge) * semibossHpbarback->GetWidth();
}
