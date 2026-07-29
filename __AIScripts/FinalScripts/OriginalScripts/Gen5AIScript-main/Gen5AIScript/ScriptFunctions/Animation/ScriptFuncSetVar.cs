using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetVar : ScriptFunc
{
    public override string Name => "SetVar";
    public override int Id => 0x40;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeAnimVar(),
        new ScriptArgTypeInt("value")
    ];
}