#include "stdafx.h"
#include "ItemManager.h"



ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{

	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y, _viItem->itemimg->GetWidth(), _viItem->itemimg->GetHeight());

		_viItem->y += 3;
	}
}

void ItemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		Rectangle(getMemDC(), _viItem->rc);

		_viItem->itemimg->render(getMemDC(), _viItem->rc.left, _viItem->rc.top, 0, 0, 16, 16);
	}

	//char str[128];
	//sprintf_s(str,"아이템사이즈 : %d ", _vItem.size());
	//TextOut(getMemDC(), 500, 450, str, strlen(str));

	

}

void ItemManager::createItem(float posX, float posY)
{
	
		tagItem item;
		ZeroMemory(&item, sizeof(item));
		item.itemimg = new image;
		item.itemimg->init("powerItem.bmp", 16, 16, true, RGB(255, 0, 255));
		item.x = posX;
		item.y = posY;
		item.rc = RectMakeCenter(item.x, item.y, item.itemimg->GetWidth(), item.itemimg->GetHeight());

		_vItem.push_back(item);

}

void ItemManager::deleteitem(int playitemNum)
{
	SAFE_RELEASE(_vItem[playitemNum].itemimg);
	_vItem.erase(_vItem.begin() + playitemNum);
}
