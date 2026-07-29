using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRemovePoke : ScriptFunc
{
    public override string Name => "RemovePoke";
    public override int Id => 0x1F;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos()
    ];
}