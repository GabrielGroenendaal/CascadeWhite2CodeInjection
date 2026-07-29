using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetBackgroundPalette : ScriptFunc
{
    public override string Name => "SetBackgroundPalette";
    public override int Id => 0x27;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("iterations"),
    ];
}