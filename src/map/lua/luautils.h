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

#ifndef _LUAUTILS_H
#define _LUAUTILS_H

#include "../../common/cbasetypes.h"

#include "../entities/battleentity.h"

/************************************************************************
*																		*
*																		*
*																		*
************************************************************************/

class CAbility;
class CSpell;
class CBaseEntity;
class CBattleEntity;
class CCharEntity;
class CInstance;
class CItem;
class CMobSkill;
class CRegion;
class CStatusEffect;

namespace luautils
{
	extern struct lua_State* LuaHandle;

	int32 init();
	int32 free();
    int32 garbageCollect(); // performs a full garbage collecting cycle
	int32 print(lua_State*);

    int32 SendEntityVisualPacket(lua_State*);                                    // временное решение для работы гейзеров в Dangruf_Wadi

	int32 GetNPCByID(lua_State*);												// Returns NPC By Id
	int32 GetMobByID(lua_State*);												// Returns Mob By Id
	int32 GetMobIDByJob(lua_State*);											// Return mobid by job
	int32 WeekUpdateConquest(lua_State*);
    int32 GetRegionOwner(lua_State*);										    // узнаем страну, владеющую текущим регионом
	int32 getNationRank(lua_State* L);
	int32 SetRegionalConquestOverseers();										// Update NPC Conquest Guard
	int32 setMobPos(lua_State*);												// set a mobs position (only if mob is not in combat)

	int32 getCorsairRollEffect(lua_State*);
    int32 getSpell(lua_State*);

	int32 SpawnMob(lua_State*);													// Spawn Mob By Mob Id - NMs, BCNM...
	int32 DespawnMob(lua_State*);												// Despawn (Fade Out) Mob By Id
	int32 GetPlayerByName(lua_State*);											// Gets Player ref from a name supplied
	int32 GetMobAction(lua_State*);												// Get Mobs current action
	int32 VanadielTOTD(lua_State*);												// текущее игровое время суток
	int32 VanadielHour(lua_State*);												// текущие Vanadiel часы
	int32 VanadielMinute(lua_State*);											// текущие Vanadiel минуты
	int32 VanadielDayOfTheYear(lua_State*);										// Gets Integer Value for Day of the Year (Jan 01 = Day 1)
	int32 VanadielDayOfTheMonth(lua_State*);									// Gets day of the month (Feb 6 = Day 6)
	int32 VanadielYear(lua_State*);												// Gets the current Vanadiel Year
	int32 VanadielMonth(lua_State*);											// Gets the current Vanadiel Month
	int32 VanadielDayElement(lua_State*);										// Gets element of the day (0: fire, ...)
	int32 VanadielMoonPhase(lua_State*);										// Gets the current Vanadiel Moon Phase
	int32 VanadielMoonDirection(lua_State* L);									// Gets the current Vanadiel Moon Phasing direction (waxing, waning, neither)
    int32 SetVanadielTimeOffset(lua_State* L);
    int32 IsMoonNew(lua_State* L);												// Returns true if the moon is new  
	int32 IsMoonFull(lua_State* L);												// Returns true if the moon is full
	int32 StartElevator(lua_State*);
	int32 GetServerVariable(lua_State*);
	int32 SetServerVariable(lua_State *);
	int32 clearVarFromAll(lua_State *);											// Deletes a specific player variable from all players

    int32 GetTextIDVariable(uint16 ZoneID, const char* variable);               // загружаем значение переменной TextID указанной зоны

	int32 OnServerStart();													// triggers when game server starts up

	int32 OnGameDayAutomatisation();											// Automatic action of NPC every game day
	int32 OnGameHourAutomatisation();											// Automatic action of NPC every game hour
	int32 OnZoneWeatherChange(uint16 ZoneID, uint8 weather);
	int32 OnTOTDChange(uint16 ZoneID, uint8 TOTD);

    int32 OnGameIn(CCharEntity* PChar);											//
	int32 OnZoneIn(CCharEntity* PChar);											// triggers when a player zones into a zone
	int32 OnZoneInitialise(uint16 ZoneID);										// triggers when zone is loaded
	int32 OnRegionEnter(CCharEntity* PChar, CRegion* PRegion);					// when player enters a region of a zone
	int32 OnRegionLeave(CCharEntity* PChar, CRegion* Pregion);					// when player leaves a region of a zone
    int32 OnTransportEvent(CCharEntity* PChar, uint32 TransportID);

	int32 OnTrigger(CCharEntity* PChar, CBaseEntity* PNpc);						// triggered when user targets npc and clicks action button
	int32 OnEventUpdate(CCharEntity* PChar, uint16 eventID, uint32 result);		// triggered when game triggers event update during cutscene
	int32 OnEventFinish(CCharEntity* PChar, uint16 eventID, uint32 result);		// triggered when cutscene/event is completed
	int32 OnTrade(CCharEntity* PChar, CBaseEntity* PNpc);						// triggers when a trade completes with an npc

	int32 OnNpcSpawn(CBaseEntity* PNpc);						// triggers when a patrol npc spawns
	int32 OnNpcPath(CBaseEntity* PNpc);						// triggers when a patrol npc reaches a point

	int32 OnEffectGain(CBattleEntity* PEntity, CStatusEffect* StatusEffect);	// triggers when an effect is applied to pc/npc
	int32 OnEffectTick(CBattleEntity* PEntity, CStatusEffect* StatusEffect);	// triggers when effect tick timer has been reached
	int32 OnEffectLose(CBattleEntity* PEntity, CStatusEffect* StatusEffect);	// triggers when effect has been lost

	int32 OnItemUse(CBaseEntity* PTarget, CItem* PItem);						// triggers when item is used
	int32 OnItemCheck(CBaseEntity* PTarget, CItem* PItem, uint32 param = 0);	// check to see if item can be used
	int32 CheckForGearSet(CBaseEntity* PTarget);								// check for gear sets

	int32 OnSpellCast(CBattleEntity* PCaster, CBattleEntity* PTarget, CSpell* PSpell);			// triggered when casting a spell
	int32 OnMonsterMagicPrepare(CBattleEntity* PCaster, CBattleEntity* PTarget);// triggered when monster wants to use a spell on target

    int32 OnMobInitialize(CBaseEntity* PMob);									// Used for passive trait
	int32 OnMobPath(CBaseEntity* PMob);						// triggers when a patrol npc finishes its pathfind
	int32 OnMobSpawn(CBaseEntity* PMob);										// triggers on mob spawn
	int32 OnMobRoamAction(CBaseEntity* PMob);										// triggers when event mob is ready for a custom roam action
	int32 OnMobRoam(CBaseEntity* PMob);
	int32 OnMobEngaged(CBaseEntity* PMob, CBaseEntity* PTarget);				// triggers on mob engaging a target
	int32 OnMobDisengage(CBaseEntity* PMob);									// triggers on mob disengaging (no more targets)
	int32 OnMobDrawIn(CBaseEntity* PMob, CBaseEntity* PTarget);
	int32 OnMobFight(CBaseEntity* PMob, CBaseEntity* PTarget);					// Сalled every 3 sec when a player fight monster
	int32 OnCriticalHit(CBattleEntity* PTarget);
	int32 OnMobDeath(CBaseEntity* PMob, CBaseEntity* PKiller);					// triggers on mob death
	int32 OnMobDespawn(CBaseEntity* PMob);										// triggers on mob despawn (death not assured)

	int32 OnBcnmEnter(CCharEntity* PChar, CInstance* PInstance);					//triggers when enter a bcnm
	int32 OnBcnmLeave(CCharEntity* PChar, CInstance* PInstance, uint8 LeaveCode);	//triggers when leaving a bcnm
																					//Code 1=via Circle 2=warp/dc 3=win 4=lose
	int32 OnBcnmRegister(CCharEntity* PChar, CInstance* PInstance);					//triggers when successfully registered a bcnm

	int32 OnMobWeaponSkill(CBaseEntity* PChar, CBaseEntity* PMob, CMobSkill* PMobSkill);							// triggers when mob weapon skill is used
	int32 OnMobSkillCheck(CBaseEntity* PChar, CBaseEntity* PMob, CMobSkill* PMobSkill);								// triggers before mob weapon skill is used, returns 0 if the move is valid
	int32 OnMagicCastingCheck(CBaseEntity* PChar, CBaseEntity* PTarget, CSpell* PSpell);							// triggers when a player attempts to cast a spell
	int32 OnAbilityCheck(CBaseEntity* PChar, CBaseEntity* PTarget, CAbility* PAbility, CBaseEntity** PMsgTarget);	// triggers when a player attempts to use a job ability or roll
	int32 OnPetAbility(CBaseEntity* PPet, CBaseEntity* PMob, CMobSkill* PMobSkill, CBaseEntity* PPetMaster);		// triggers when pet uses an ability
	int32 OnUseWeaponSkill(CCharEntity* PChar, CBaseEntity* PMob, uint16* tpHitsLanded, uint16* extraHitsLanded);	// triggers when weapon skill is used
	int32 OnUseAbility(CCharEntity* PChar, CBattleEntity* PTarget, CAbility* PAbility, apAction_t* action);		// triggers when job ability is used
	int32 OnUseAbilityRoll(CCharEntity* PChar, CBattleEntity* PTarget, CAbility* PAbility, uint8 total);			// triggers on corsair roll

    int32 GetMobRespawnTime(lua_State* L);                                      // get the respawn time of a mob
	int32 DeterMob(lua_State* L);                                               // Allow or prevent a mob from spawning
	int32 UpdateNMSpawnPoint(lua_State* L);                                     // Update the spawn point of an NM
	int32 SetDropRate(lua_State*);												// Set drop rate of a mob setDropRate(dropid,itemid,newrate)
	int32 UpdateTreasureSpawnPoint(lua_State* L);                               // Update the spawn point of an Treasure
	int32 UpdateServerMessage(lua_State*);										// update server message, first modify in conf and update

    int32 OnAdditionalEffect(CBattleEntity* PAttacker, CBattleEntity* PDefender, CItemWeapon* PItem, apAction_t* Action, uint32 damage); // for items with additional effects

    int32 nearLocation(lua_State*);

};

#endif //- _LUAUTILS_H -
