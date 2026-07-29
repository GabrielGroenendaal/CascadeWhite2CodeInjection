using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncGetVar : ScriptFunc
{
    public override string Name => "GetVar";
    public override int Id => 0x3F;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeAnimVar()
    ];
}