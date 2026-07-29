using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetControlState : ScriptFunc
{
    public override string Name => "SetControlState";
    public override int Id => 0x3A;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeControlState()
    ];
}