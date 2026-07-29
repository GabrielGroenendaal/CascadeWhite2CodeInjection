using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncWaitFor : ScriptFunc
{
    public override string Name => "WaitFor";
    public override int Id => 0x38;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeWaitForType()
    ];
}