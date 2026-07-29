using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncChangeObjectColor : ScriptFunc
{
    public override string Name => "ChangeObjectColor";
    public override int Id => 0x31;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index"),
        new ScriptArgTypeInt("opacity_start"),
        new ScriptArgTypeInt("opacity_end"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeColor()
    ];
}