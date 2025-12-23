using Gen5AIScript.ScriptFunctions;

namespace Gen5AIScript;

public class ScriptFuncLibrary
{
    private readonly ScriptFunc?[] _byIndex;
    private readonly Dictionary<string, ScriptFunc?> _byName = new();

    public ScriptFuncLibrary()
    {
        _byIndex =
        [
            // 0x00
            new ScriptFuncJumpIfRandLT(), // 0x00
            new ScriptFuncJumpIfRandGT(), // 0x01
            new ScriptFuncJumpIfRandEQ(), // 0x02
            new ScriptFuncJumpIfRandNE(), // 0x03
            new ScriptFuncAddToScore(), // 0x04
            new ScriptFuncJumpIfHealthLT(), // 0x05
            new ScriptFuncJumpIfHealthGT(), // 0x06
            new ScriptFuncJumpIfHealthEQ(), // 0x07
            new ScriptFuncJumpIfHealthNE(), // 0x08
            new ScriptFuncJumpIfHasAnyStatus(), // 0x09
            new ScriptFuncJumpIfHasNoStatus(), // 0x0A
            new ScriptFuncJumpIfHasCondition(), // 0x0B
            new ScriptFuncJumpIfNotCondition(), // 0x0C
            new ScriptFuncJumpIfBadlyPoisoned(), // 0x0D
            new ScriptFuncJumpIfNotBadlyPoisoned(), // 0x0E
            new ScriptFuncJumpIfHasConditionFlag(), // 0x0F

            // 0x10
            new ScriptFuncJumpIfNotConditionFlag(), // 0x10
            new ScriptFuncJumpIfHasSideCondition(), // 0x11
            new ScriptFuncJumpIfNotSideCondition(), // 0x12
            new ScriptFuncJumpIfStoredLT(), // 0x13
            new ScriptFuncJumpIfStoredGT(), // 0x14
            new ScriptFuncJumpIfStoredEQ(), // 0x15
            new ScriptFuncJumpIfStoredNE(), // 0x16
            new ScriptFuncJumpIfStoredAND(), // 0x17
            new ScriptFuncJumpIfStoredNAND(), // 0x18
            new ScriptFuncJumpIfMoveEQ(), // 0x19
            new ScriptFuncJumpIfMoveNE(), // 0x1A
            new ScriptFuncJumpIfStoredIsInList(), // 0x1B
            new ScriptFuncJumpIfStoredIsNotInList(), // 0x1C
            new ScriptFuncJumpIfHasDamagingMove(), // 0x1D
            new ScriptFuncJumpIfNoDamagingMove(), // 0x1E
            new ScriptFuncGetTurnCount(), // 0x1F

            // 0x20
            new ScriptFuncGetType(), // 0x20
            new ScriptFuncGetMoveBasePower(), // 0x21
            new ScriptFuncCalcMoveDamage(), // 0x22
            new ScriptFuncGetPreviousMove(), // 0x23
            new ScriptFuncDuplicate(new ScriptFuncJumpIfStoredEQ(), 0x24), // DUPLICATE of 0x15; seemingly a vestige from when int values had different sizes
            new ScriptFuncDuplicate(new ScriptFuncJumpIfStoredNE(), 0x25), // DUPLICATE of 0x16; ''
            new ScriptFuncJumpCompareSpeed(), // 0x26
            new ScriptFuncGetPartyReserveCount(), // 0x27
            new ScriptFuncGetMove(), // 0x28
            new ScriptFuncGetMoveEffect(), // 0x29
            new ScriptFuncGetAbilityGuess(), // 0x2A
            null!, // 0x2B   AI043
            new ScriptFuncJumpIfEffectivenessEQ(), // 0x2C
            new ScriptFuncJumpIfPartyHasStatus(), // 0x2D
            new ScriptFuncJumpIfUserWillFaint_Priority(), // 0x2E
            new ScriptFuncGetWeather(), // 0x2F

            // 0x30
            new ScriptFuncJumpIfMoveEffectEQ(), // 0x30
            new ScriptFuncJumpIfMoveEffectNE(), // 0x31
            new ScriptFuncJumpIfStatStageLT(), // 0x32
            new ScriptFuncJumpIfStatStageGT(), // 0x33
            new ScriptFuncJumpIfStatStageEQ(), // 0x34
            new ScriptFuncJumpIfStatStageNE(), // 0x35
            new ScriptFuncJumpIfTargetWillFaint(), // 0x36
            new ScriptFuncJumpIfTargetWillNotFaint(), // 0x37
            new ScriptFuncJumpIfHasMove(), // 0x38
            new ScriptFuncJumpIfDoesNotHaveMove(), // 0x39
            new ScriptFuncJumpIfHasMoveWithEffect(), // 0x3A
            new ScriptFuncJumpIfHasNoMovesWithEffect(), // 0x3B


            null!, // 0x3C
            new ScriptFuncFlee(), // 0x3D
            

            null!, // 0x3E

            // AI063
            null!, // 0x3F This was used to trigger the Safari Zone "{POKÉMON} is watching carefully" message

            // 0x40
            new ScriptFuncGetHeldItem(), // 0x40
            new ScriptFuncGetHeldItemEffect(), // 0x41
            new ScriptFuncJumpIfUserWillTakeLowDamage_Debuffs(), // 0x42
            new ScriptFuncStoreIsFirstTurn(), // 0x43
            new ScriptFuncJumpIfUserAboutToWakeUp(), // 0x44
            new ScriptFuncGetBattleStyle(), // 0x45
            new ScriptFuncGetBattleType(), // 0x46
            new ScriptFuncGetUsedItem(), // 0x47
            
            null!,
            //new ScriptFuncJumpIfUserWillFaint_Setup(), // 0x48

            new ScriptFuncGetPowerOfStoredMove(), // 0x49
            new ScriptFuncGetEffectOfStoredMove(), // 0x4A
            new ScriptFuncGetGetProtectCount(), // 0x4B
            new ScriptFuncJump(), // 0x4C
            new ScriptFuncEndScript(), // 0x4D
            new ScriptFuncJumpCompareLevel(), // 0x4E
            new ScriptFuncJumpIfTaunted(), // 0x4F

            // 0x50
            new ScriptFuncJumpIfNotTaunted(), // 0x50
            new ScriptFuncJumpIfTargetIsAlly(), // 0x51
            new ScriptFuncGetPokeHasType(), // 0x52
            new ScriptFuncGetPokeHasAbility(), // 0x53
            new ScriptFuncJumpIfFlashFireIsActive(), // 0x54
            new ScriptFuncJumpIfHeldItemEQ(), // 0x55
            new ScriptFuncJumpIfFieldEffectEQ(), // 0x56
            new ScriptFuncGetSideStatusLevel(), // 0x57
            new ScriptFuncJumpIfPartyHasDamage(), // 0x58
            new ScriptFuncJumpIfUserIsSlowerThanAllEnemies(), // 0x59
            new ScriptFuncGetFlingPower(), // 0x5A
            new ScriptFuncGetMovePP(), // 0x5B
            new ScriptFuncJumpIfCanUseLastResort(), // 0x5C
            new ScriptFuncGetMoveCategory(), // 0x5D
            new ScriptFuncGetPreviousMoveCategory(), // 0x5E
            new ScriptFuncGetPosInTurnOrder(), // 0x5F

            // 0x60
            new ScriptFuncCheckOwnDamageIntoAlly(), // 0x60 NEW 
            // new ScriptFuncGetPokeTurnCount(), // 0x60
            new ScriptFuncJumpIfReservedHasStrongerMove(), // 0x61
            new ScriptFuncJumpIfHasSuperEffectiveMove(), // 0x62
            new ScriptFuncJumpIfLastMoveGTStrongest(), // 0x63
            new ScriptFuncJumpIfUserWillTakeLowDamage_Setup(), // 0x64 NEW
            //new ScriptFuncGetPositiveStatStageTotal(), // 0x64
            new ScriptFuncGetStatDiff(), // 0x65
            null!,
            //new ScriptFuncJumpIfUserAboutToWakeUp(), // 0x66
            null!, // 0x67
            null!,
            //new ScriptFuncJumpIfUserWillFaint_Priority(), // 0x68
            //null!,
            //null!,
            //null!,
            new ScriptFuncJumpIfUserWillFaint_Setup(), // 0x69 NEW
            // new ScriptFuncCalcDamageWithPartner(), // 0x69
            new ScriptFuncJumpIfIsFainted(), // 0x6A
            new ScriptFuncJumpIfIsNotFainted(), // 0x6B
            new ScriptFuncGetAbility(), // 0x6C
            new ScriptFuncJumpIfHasSubstitute(), // 0x6D
            new ScriptFuncGetSpecies(), // 0x6E
            new ScriptFuncJumpIfRandSeedLT(), // 0x6F

            // 0x70
            new ScriptFuncJumpIfRandSeedGT(), // 0x70
            new ScriptFuncJumpIfRandSeedEQ(), // 0x71
            new ScriptFuncJumpIfRandSeedNE(), // 0x72
            new ScriptFuncJumpTable(), // 0x73
            new ScriptFuncJumpIfAttackForeseen(), // 0x74
            new ScriptFuncJumpIfAtkLTSpa(), // 0x75
            new ScriptFuncJumpIfAtkGTSpa(), // 0x76
            new ScriptFuncJumpIfAtkEQSpa(), // 0x77
        ];

        for (var i = 0; i < _byIndex.Length; ++i)
        {
            var scriptFunc = _byIndex[i];

            if (scriptFunc == null)
                continue;

            // validate
            if (scriptFunc.Id != i)
                throw new Exception($"ScriptFunc at index 0x{i:X2} has an id of 0x{scriptFunc.Id:X2}");

            if (scriptFunc is not ScriptFuncDuplicate)
                _byName.Add(scriptFunc.Name, scriptFunc);
        }
    }

    public ScriptFunc? GetScriptFunc(string name) => _byName[name];
    public ScriptFunc? GetScriptFunc(int id) => _byIndex[id];
}