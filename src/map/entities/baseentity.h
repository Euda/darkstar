﻿/*
===========================================================================

  Copyright (c) 2010-2014 Darkstar Dev Teams

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/

  This file is part of DarkStar-server source code.

===========================================================================
*/

#ifndef _BASEENTITY_H
#define _BASEENTITY_H

#include "../../common/cbasetypes.h"
#include "../../common/mmo.h"

#include "../ai/ai_general.h"

enum ENTITYTYPE
{
	TYPE_PC		= 0x01,
	TYPE_NPC	= 0x02,
	TYPE_MOB	= 0x04,
	TYPE_PET	= 0x08,
    TYPE_SHIP   = 0x10
};

enum STATUSTYPE
{
	STATUS_NORMAL			= 0,
	STATUS_UPDATE			= 1,
	STATUS_DISAPPEAR		= 2,
	STATUS_3				= 3,
	STATUS_4				= 4,
	STATUS_CUTSCENE_ONLY	= 6,
	STATUS_18				= 18,
	STATUS_SHUTDOWN			= 20
};

enum ANIMATIONTYPE
{
	ANIMATION_NONE					= 0,
	ANIMATION_ATTACK				= 1,
	ANIMATION_DEATH					= 3,
    ANIMATION_CHOCOBO               = 5,
	ANIMATION_FISHING   			= 6,
    //healing 7
	ANIMATION_OPEN_DOOR				= 8,
	ANIMATION_CLOSE_DOOR			= 9,
	ANIMATION_ELEVATOR_UP			= 10,
	ANIMATION_ELEVATOR_DOWN			= 11,
	ANIMATION_HEALING				= 33,
	ANIMATION_FISHING_FISH			= 38,
	ANIMATION_FISHING_CAUGHT		= 39,
	ANIMATION_FISHING_ROD_BREAK		= 40,
	ANIMATION_FISHING_LINE_BREAK	= 41,
	ANIMATION_FISHING_MONSTER		= 42,
	ANIMATION_FISHING_STOP			= 43,
	ANIMATION_SYNTH					= 44,
	ANIMATION_SIT					= 47,
	ANIMATION_RANGED				= 48,
	ANIMATION_FISHING_START			= 50
};

// TODO: возможо стоит сделать эту структуру частью класса, взамен нынешних id и targid, но уже без метода clean

struct EntityID_t
{
    void clean()
    {
        id = 0;
        targid = 0;
    }

    uint32 id;
    uint16 targid;
};

class CZone;

struct location_t
{
	position_t	p;              // позиция сущности
    uint16		destination;    // текущая зона
    CZone*      zone;           // текущая зона
	uint16		prevzone;       // предыдущая зона (для монстров и npc не используется)
	bool		zoning;         // флаг сбрасывается при каждом входе в новую зону. необходим для реализации логики игровых задач ("quests")
	uint16		boundary;       // определенная область в зоне, в которой находится сущность (используется персонажами и транспортом)
};

/************************************************************************
*																		*
*  Базовый класс для всех сущностей в игре								*
*																		*
************************************************************************/

class CBaseEntity
{
public:

	uint32			id;					// глобальный идентификатор, уникальный на сервере
	uint16			targid;				// локалный идентификатор, уникальный в зоне
	ENTITYTYPE		objtype;			// тип сущности
	STATUSTYPE		status;				// статус сущности (разные сущности - разные статусы)
	uint16			m_TargID;			// targid объекта, на который смотрит сущность
	string_t		name;				// имя сущности
	look_t			look;				// внешний вид всех сущностей
	look_t			mainlook;			// only used if mob use changeSkin()
	location_t		loc;				// местоположение сущности
	uint8			animation;			// анимация
	uint8			animationsub;		// дополнительный параметры анимации
	uint8			speed;				// скорость передвижения
	uint8			speedsub;			// подолнительный параметр скорости передвижения
	uint8			namevis; 
	bool			untargetable;
	bool			hpvis;

	virtual const int8* GetName();      // имя сущности

	uint16			getZone();			// текущая зона
	float			GetXPos();			// позиция по координате X
	float			GetYPos();			// позиция по координате Y
	float			GetZPos();			// позиция по координате Z
	uint8			GetRotPos();
	void			HideName(bool hide); // hide / show name
	bool			IsNameHidden();		// checks if name is hidden

    CAIGeneral*     PBattleAI;          // интеллект любой сущности

    CBaseEntity();						// конструктор
    virtual ~CBaseEntity();						// деструктор
private:
};

#endif

