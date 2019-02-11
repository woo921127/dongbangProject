#pragma once
#include "gameNode.h"

struct tagItem
{
	image* itemimg;
	RECT rc;
	float x, y;
};


class ItemManager : public gameNode
{
private:
	vector<tagItem>			_vItem;
	vector<tagItem>::iterator _viItem;

	const char*					_imageName;
	int							_ItemMax;

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();


	vector<tagItem> getVItem() { return _vItem; }
	vector<tagItem>::iterator getVIItem() { return _viItem; }

	void createItem(float posX, float posY);
	void deleteitem(int playitemNum);

};

