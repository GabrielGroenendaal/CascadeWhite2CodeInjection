using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetBackgroundPosition : ScriptFunc
{
    public override string Name => "SetBackgroundPosition";
    public override int Id => 0x28;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBackgroundPosition(),
    ];
}