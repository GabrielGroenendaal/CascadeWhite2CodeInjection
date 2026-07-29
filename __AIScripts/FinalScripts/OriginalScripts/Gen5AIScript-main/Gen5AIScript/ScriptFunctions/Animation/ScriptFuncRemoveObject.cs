using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRemoveObject : ScriptFunc
{
    public override string Name => "RemoveObject";
    public override int Id => 0x32;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index")
    ];
}