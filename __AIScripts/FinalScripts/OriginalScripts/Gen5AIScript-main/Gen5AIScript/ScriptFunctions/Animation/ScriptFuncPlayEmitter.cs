using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitter : ScriptFunc
{
    public override string Name => "PlayEmitter";
    public override int Id => 0x07;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeEmitterPos("origin"),
        new ScriptArgTypeEmitterPos("target"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("angle"),
        new ScriptArgTypeEmpty(),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("scale"),
        new ScriptArgTypeFixedPoint("velocity"),
    ];
}