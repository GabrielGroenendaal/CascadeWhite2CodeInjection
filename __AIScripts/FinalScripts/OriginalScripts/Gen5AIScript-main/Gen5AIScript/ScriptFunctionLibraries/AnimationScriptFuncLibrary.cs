using Gen5AIScript.ScriptFunctions.Animation;

namespace Gen5AIScript.ScriptFunctionLibraries;

public class AnimationScriptFuncLibrary : ScriptFunctionLibrary
{
    private readonly ScriptFunc?[] _byIndex;
    private readonly Dictionary<string, ScriptFunc?> _byName = new();

    public AnimationScriptFuncLibrary()
    {
        _byIndex =
        [
            // 0x00
            new ScriptFuncMoveCamera(), // 0x00
            new ScriptFuncMoveCameraTarget(), // 0x01
            new ScriptFuncRotateCamera(), // 0x02
            new ScriptFuncShakeCamera(), // 0x03
            new ScriptFuncSetCameraProjectionType(), // 0x04
            new ScriptFuncPushCamera(), // 0x05
            new ScriptFuncLoadParticles(), // 0x06
            new ScriptFuncPlayEmitter(), // 0x07
            new ScriptFuncPlayEmitterAt(), // 0x08
            new ScriptFuncPlayEmitterOrthographic(), // 0x09
            new ScriptFuncPlayAllEmitters(), // 0x0A
            new ScriptFuncStopAllEmitters(), // 0x0B
            new ScriptFuncPlayEmitterMove(), // 0x0C
            new ScriptFuncPlayEmitterMoveFrom(), // 0x0D
            new ScriptFuncPlayEmitterMoveOrthographic(), // 0x0E
            new ScriptFuncPlayEmitterMoveOrthographicFrom(), // 0x0F

            // 0x10
            new ScriptFuncPlayEmitterCircle(), // 0x10
            new ScriptFuncPlayEmitterCircleOrthographic(), // 0x11
            new ScriptFuncMovePoke(), // 0x12
            new ScriptFuncMovePokeCircle(), // 0x13
            new ScriptFuncMovePokeWave(), // 0x14
            new ScriptFuncScalePoke(), // 0x15
            new ScriptFuncRotatePoke(), // 0x16
            new ScriptFuncChangePokeOpacity(), // 0x17
            new ScriptFuncPokeMosaic(), // 0x18
            new ScriptFuncSetPokeEyeState(), // 0x19
            new ScriptFuncSetPokeAnimState(), // 0x1A
            new ScriptFuncChangePokeColor(), // 0x1B
            new ScriptFuncSetPokeVisibility(), // 0x1C
            new ScriptFuncSetPokeShadowVisibility(), // 0x1D
            new ScriptFuncSetPokeShadowScale(), // 0x1E
            new ScriptFuncRemovePoke(), // 0x1F

            // 0x20
            new ScriptFuncSetTrainerClass(), // 0x20
            new ScriptFuncMoveTrainer(), // 0x21
            new ScriptFuncSetTrainerAnimation(), // 0x22
            new ScriptFuncRemoveTrainer(), // 0x23
            new ScriptFuncLoadBackground(), // 0x24
            new ScriptFuncMoveBackground(), // 0x25
            new ScriptFuncDistortBackground(), // 0x26
            new ScriptFuncSetBackgroundPalette(), // 0x27
            new ScriptFuncSetBackgroundPosition(), // 0x28
            new ScriptFuncSetBackgroundOpacity(), // 0x29
            new ScriptFuncChangeBackgroundColor(), // 0x2A
            new ScriptFuncSetBackgroundVisibility(), // 0x2B
            new ScriptFuncMoveWindow(), // 0x2C
            new ScriptFuncCreateObject(), // 0x2D
            new ScriptFuncMoveObject(), // 0x2E
            new ScriptFuncScaleObject(), // 0x2F

            // 0x30
            new ScriptFuncSetObjectAnimation(), // 0x30
            new ScriptFuncChangeObjectColor(), // 0x31
            new ScriptFuncRemoveObject(), // 0x32
            new ScriptFuncSetGaugeVisibility(), // 0x33
            new ScriptFuncPlaySound(), // 0x34
            new ScriptFuncStopSound(), // 0x35
            new ScriptFuncPanSound(), // 0x36
            new ScriptFuncChangeSoundProperty(), // 0x37
            new ScriptFuncWaitFor(), // 0x38
            new ScriptFuncWait(), // 0x39
            new ScriptFuncSetControlState(), // 0x3A
            new ScriptFuncJumpIf(), // 0x3B
            new ScriptFuncJumpIfVar(), // 0x3C
            new ScriptFuncJumpIfExists(), // 0x3D
            new ScriptFuncSetTempVar(), // 0x3E
            new ScriptFuncGetVar(), // 0x3F

            // 0x40
            new ScriptFuncSetVar(), // 0x40
            new ScriptFuncSubstitute(), // 0x41
            new ScriptFuncTransform(), // 0x42
            new ScriptFuncPlayPokeCry(), // 0x43
            new ScriptFuncSetCapturePosition(), // 0x44
            new ScriptFuncSetBall(), // 0x45
            new ScriptFuncRunScript(), // 0x46
            new ScriptFuncReturn(), // 0x47
            new ScriptFuncJump(), // 0x48
            new ScriptFuncPause(), // 0x49
            new ScriptFuncJumpToScript(), // 0x4A
            new ScriptFuncWaitForPokeLand(), // 0x4B
            new ScriptFuncSetReverseDraw(), // 0x4C
            new ScriptFuncEndScript() // 0x4D
        ];

        for (var i = 0; i < _byIndex.Length; ++i)
        {
            var scriptFunc = _byIndex[i];

            if (scriptFunc == null)
                continue;

            // validate
            if (scriptFunc.Id != i)
                throw new Exception($"ScriptFunc at index 0x{i:X2} has an id of 0x{scriptFunc.Id:X2}");

            _byName.Add(scriptFunc.Name, scriptFunc);
        }
    }

    public override ScriptFunc? GetScriptFunc(string name) => _byName[name];
    public override ScriptFunc? GetScriptFunc(int id) => _byIndex[id];
}