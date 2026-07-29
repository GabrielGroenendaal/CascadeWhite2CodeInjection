using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayAllEmitters : ScriptFunc
{
    public override string Name => "PlayAllEmitters";
    public override int Id => 0x0A;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeEmitterPos("origin"),
        new ScriptArgTypeEmitterPos("target"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeFixedPoint("angle"),
        new ScriptArgTypeEmpty(),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeFixedPoint("lifetime"),
        new ScriptArgTypeFixedPoint("scale"),
        new ScriptArgTypeFixedPoint("velocity")
    ];
}