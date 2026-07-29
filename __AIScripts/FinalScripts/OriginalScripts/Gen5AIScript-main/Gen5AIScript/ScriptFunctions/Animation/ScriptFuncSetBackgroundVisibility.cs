using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetBackgroundVisibility : ScriptFunc
{
    public override string Name => "SetBackgroundVisibility";
    public override int Id => 0x2B;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBackgroundType(),
        new ScriptArgTypeVisibilityState()
    ];
}