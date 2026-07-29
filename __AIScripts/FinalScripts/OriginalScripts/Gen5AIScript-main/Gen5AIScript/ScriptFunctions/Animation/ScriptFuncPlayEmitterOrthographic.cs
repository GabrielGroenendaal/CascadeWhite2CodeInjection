using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitterOrthographic : ScriptFunc
{
    public override string Name => "PlayEmitterOrthographic";
    public override int Id => 0x09;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeEmitterPos("origin"),
        new ScriptArgTypeEmitterPos("target"),
        new ScriptArgTypeFixedPoint("x_offset"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("z_offset"),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("scale"),
        new ScriptArgTypeFixedPoint("velocity")
    ];
}