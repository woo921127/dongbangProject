#pragma once
#include "gameNode.h"

enum ENEMYTYPE
{
	ONE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	ELEVEN,
	TWELVE	
};


class enemy : public gameNode
{
protected:
	
	image* _imageName;		
	RECT _rc;				

	int _currentFrameX;		
	int _currentFrameY;

	int _count;				
	int _fireCount;			
	int _rndFireCount;	

	int _fire2Count;
	int _rndFire2Count;

	int _fire3Count;
	int _rndFire3Count;


	int _fire4Count;
	int _rndFire4Count;


	int _fire5Count;
	int _rndFire5Count;



	int _fire6Count;
	int _rndFire6Count;


	int _speed;
	float _angle;

	int _type;

	int _movecount;

	POINTF _pos;

	float _posX;
	float _posY;

	bool change;

	//=== 미니언 2웨이브 체크===/
	bool wave2change;
	bool wave2change2;


	bool wave2change3;
	bool wave2change4;
	int posCount;

public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINTF position);
	void release();
	void update();
	void render();

	void move(int type);		
	void draw();		

	bool bulletCountFire();
	bool bullet2CountFire();
	bool bullet3CountFire();
	bool bullet4CountFire();
	bool bullet5CountFire();
	bool bullet6CountFire();



	inline RECT getRect() { return _rc; }
	inline image* getImage() { return _imageName; }



	void setType(int type) { _type = type; }
	void setPos(POINTF pos) { _pos = pos; }

	//float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	
};

