using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRemoveTrainer : ScriptFunc
{
    public override string Name => "RemoveTrainer";
    public override int Id => 0x23;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos()
    ];
}