#pragma once

#include "pch.h"
#include "framework.h"
#include "PwŒG_Tanks.h"
#include <list>
#include <PwŒG_Tanks.cpp>

#define MAX_LOADSTRING 100
#define WINDOWHEIGHT 600
#define WINDOWWIDTH 800

enum class direction
{
	up = 0, left = 1, down = 2, right = 3
};

class player
{
public:
	int lp;
	int x;
	int y;
	int health;
	int ammo;
	int points;
	int speed;
	direction dir;
	bool wasdPressed[4] = { false,false,false,false };
	direction dirTab[4] = { direction::up,direction::left, direction::down, direction::right };

	player(int lp, int x, int y, int health, int ammo, int points, int speed, direction dir) :
		lp(lp), x(x), y(y), health(health), ammo(ammo), points(points), speed(speed), dir(dir) {	}

	void move(direction dir)
	{
		if (!wasdPressed[0] && !wasdPressed[1] && !wasdPressed[2] && !wasdPressed[3]) return;
		switch (dirTab[0])
		{
		case direction::up:
		{
			y -= speed;
			if (y < tankRad) y = tankRad;
			if (didPlayersCollide()) y += (2 * tankRad - (y - players[!lp].y));
			break;
		}
		case direction::left:
		{
			x -= speed;
			if (x < tankRad) x = tankRad;
			if (didPlayersCollide()) x += (2 * tankRad - (x - players[!lp].x));
			break;
		}
		case direction::down:
		{
			y += speed;
			if (y > WINDOWHEIGHT - tankRad) y = WINDOWHEIGHT - tankRad;
			if (didPlayersCollide()) y -= (2 * tankRad - (players[!lp].y - y));
			break;
		}
		case direction::right:
		{
			x += speed;
			if (x > WINDOWWIDTH - tankRad) x = WINDOWWIDTH - tankRad;
			if (didPlayersCollide()) x -= (2 * tankRad - (players[!lp].x - x));
			break;
		}
		default:
			break;
		}
		if (isOnItem(lp))
		{
			switch (item)
			{
			case items::coin:
				points += 5;
				break;
			case items::ammo:
				ammo += 20;
				break;
			case items::healthkit:
				health = min(health + 50, 100);
				break;
			default:
				break;
			}
			createItem();
		}
	}
};