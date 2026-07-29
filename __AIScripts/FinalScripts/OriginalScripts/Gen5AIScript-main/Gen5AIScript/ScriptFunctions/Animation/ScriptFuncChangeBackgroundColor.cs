using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncChangeBackgroundColor : ScriptFunc
{
    public override string Name => "ChangeBackgroundColor";
    public override int Id => 0x2A;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBackgroundType(),
        new ScriptArgTypeInt("opacity_start"),
        new ScriptArgTypeInt("opacity_end"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeColor()
    ];
}