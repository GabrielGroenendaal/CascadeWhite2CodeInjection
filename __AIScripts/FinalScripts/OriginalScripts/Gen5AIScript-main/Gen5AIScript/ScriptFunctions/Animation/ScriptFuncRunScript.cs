using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRunScript : ScriptFunc
{
    public override string Name => "RunScript";
    public override int Id => 0x46;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("id"),
        new ScriptArgTypeObjectPos("attacking_pos"),
        new ScriptArgTypeObjectPos("defending_pos"),
    ];
}