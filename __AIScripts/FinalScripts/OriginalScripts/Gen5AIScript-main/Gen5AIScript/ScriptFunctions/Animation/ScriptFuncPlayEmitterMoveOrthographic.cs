using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitterMoveOrthographic : ScriptFunc
{
    public override string Name => "PlayEmitterMoveOrthographic";
    public override int Id => 0x0E;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeEmitterMoveType(),
        new ScriptArgTypeEmitterPos("origin"),
        new ScriptArgTypeEmitterPos("target"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("frames"),
        new ScriptArgTypeFixedPoint("arc_apex"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("velocity"),
        new ScriptArgTypeFixedPoint("wave_count")
    ];
}