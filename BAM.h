#pragma once

#include <list>

using namespace std;

enum DIRECTION{KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_NULL};

const int m_ROW = 20;
const int m_COL = 20;

struct BAMPOS
{
	int x;
	int y;
};

class CBAM
{
public:
	CBAM();
	~CBAM();

public:
	list<BAMPOS> m_bamlist;	
	list<BAMPOS> m_bamend;
	DIRECTION m_dir;
	BAMPOS m_tail;


public:
	bool move(DIRECTION dir);
	void bbam();
	void addtail();
	bool iscontact();

private:
	bool isout();
	


};

