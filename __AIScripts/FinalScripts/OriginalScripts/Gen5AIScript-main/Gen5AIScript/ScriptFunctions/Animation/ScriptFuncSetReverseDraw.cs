using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetReverseDraw : ScriptFunc
{
    public override string Name => "SetReverseDraw";
    public override int Id => 0x4C;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBool("is_reversed")
    ];
}