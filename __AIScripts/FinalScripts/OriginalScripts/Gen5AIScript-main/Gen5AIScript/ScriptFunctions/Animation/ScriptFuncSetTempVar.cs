using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetTempVar : ScriptFunc
{
    public override string Name => "SetTempVar";
    public override int Id => 0x3E;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("value")
    ];
}