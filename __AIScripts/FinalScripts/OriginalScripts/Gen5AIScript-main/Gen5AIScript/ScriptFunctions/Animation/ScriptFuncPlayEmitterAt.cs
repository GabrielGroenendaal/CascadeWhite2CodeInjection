using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitterAt : ScriptFunc
{
    public override string Name => "PlayEmitterAt";
    public override int Id => 0x08;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeFixedPoint("origin_x"),
        new ScriptArgTypeFixedPoint("origin_y"),
        new ScriptArgTypeFixedPoint("origin_z"),
        new ScriptArgTypeFixedPoint("target_x"),
        new ScriptArgTypeFixedPoint("target_y"),
        new ScriptArgTypeFixedPoint("target_z"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("angle"),
        new ScriptArgTypeEmpty(),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("scale"),
        new ScriptArgTypeFixedPoint("velocity"),
    ];
}