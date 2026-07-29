using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMovePokeWave : ScriptFunc
{
    public override string Name => "MovePokeWave";
    public override int Id => 0x14;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeWaveAxis(),
        new ScriptArgTypeFixedPoint("origin_angle"),
        new ScriptArgTypeFixedPoint("target_angle"),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeInt("frames")
    ];
}