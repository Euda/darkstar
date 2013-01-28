---------------------------------------------
--  Goblin Dice
--
--  Description: Reset recasts on abilities
--  Type: Physical (Blunt)
--
--
---------------------------------------------
require("/scripts/globals/settings");
require("/scripts/globals/status");
require("/scripts/globals/monstertpmoves");
---------------------------------------------
function OnMobSkillCheck(target,mob,skill)
    return 0;
end;

function OnMobWeaponSkill(target, mob, skill)

    target:resetRecasts();

    skill:setMsg(360);

    return 1;
end;
