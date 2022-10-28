#include "stdafx.h"
#include "BAM.h"

//家府颇老 持扁
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

void CBAM::bbam() 
{
	// 檬扁 轨 备己 (3付叼)
	BAMPOS bam;
	bam.x = m_ROW / 2;
	bam.y = m_COL / 2;
	// 赣府
	m_bamlist.push_back(bam);

	bam.x -= 1;
	// 个烹
	m_bamlist.push_back(bam);

	bam.x -= 1;
	// 部府
	m_bamlist.push_back(bam);

	m_dir = KEY_NULL;

	m_tail = m_bamlist.back();

	m_bamend = m_bamlist;
}



CBAM::CBAM()
{
	bbam();
	
}


CBAM::~CBAM()
{
}

bool CBAM::move(DIRECTION dir)
{
	if (m_dir == KEY_LEFT && dir == KEY_RIGHT)
	{
		dir = m_dir;
	}		
	else if (m_dir == KEY_RIGHT && dir == KEY_LEFT)
	{
		dir = m_dir;
	}		
	else if (m_dir == KEY_UP && dir == KEY_DOWN)
	{
		dir = m_dir;
	}		
	else if (m_dir == KEY_DOWN && dir == KEY_UP)
	{
		dir = m_dir;
	}
	else
		m_dir = dir;

	BAMPOS pos;

	pos = m_bamlist.front();

	switch (dir)
	{
	case KEY_LEFT:
		pos.x--;
		m_bamlist.push_front(pos);
		m_bamlist.pop_back();
		break;
	case KEY_RIGHT:
		pos.x++;
		m_bamlist.push_front(pos);
		m_bamlist.pop_back();
		break;
	case KEY_UP:
		pos.y--;
		m_bamlist.push_front(pos);
		m_bamlist.pop_back();
		break;
	case KEY_DOWN:
		pos.y++;
		m_bamlist.push_front(pos);
		m_bamlist.pop_back();
		break;
	case KEY_NULL:
		break;
	default:
		break;
	}

	m_tail = m_bamlist.back();

	if (isout())
	{
		m_bamlist = m_bamend;

		return false;
	}
	else
		m_bamend = m_bamlist;

	return true;
}


void CBAM::addtail()
{
	m_bamlist.push_back(m_tail);
}

bool CBAM::isout()
{
	BAMPOS pos = m_bamlist.front();
	if (pos.x < 0)
		return true;
	else if (pos.x >= m_COL)
		return true;
	else if (pos.y < 0)
		return true;
	else if (pos.y >= m_ROW)
		return true;

	return false;
}

bool CBAM::iscontact()
{
	BAMPOS pos = m_bamlist.front();

	list<BAMPOS>::iterator itr = m_bamlist.begin();		
	
	for (itr = ++itr; itr !=m_bamlist.end(); ++itr)
	{
		if (itr->x == pos.x && itr->y == pos.y)
			return true;
	}
	return false;
}
