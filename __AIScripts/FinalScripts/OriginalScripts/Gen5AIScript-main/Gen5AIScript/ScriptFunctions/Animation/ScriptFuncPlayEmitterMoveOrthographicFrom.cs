using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitterMoveOrthographicFrom : ScriptFunc
{
    public override string Name => "PlayEmitterMoveOrthographicFrom";
    public override int Id => 0x0F;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeEmitterMoveType(),
        new ScriptArgTypeFixedPoint("origin_x"),
        new ScriptArgTypeFixedPoint("origin_y"),
        new ScriptArgTypeFixedPoint("origin_z"),
        new ScriptArgTypeEmitterPos("target"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("frames"),
        new ScriptArgTypeFixedPoint("arc_apex"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("velocity"),
        new ScriptArgTypeFixedPoint("scale")
    ];
}