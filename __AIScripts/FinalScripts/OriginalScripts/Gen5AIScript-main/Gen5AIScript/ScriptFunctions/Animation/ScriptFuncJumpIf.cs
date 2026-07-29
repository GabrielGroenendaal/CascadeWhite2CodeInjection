using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncJumpIf : ScriptFuncJumpBase
{
    public override string Name => "JumpIf";
    public override int Id => 0x3B;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeAnimVar(),
        new ScriptArgTypeAnimCompareOperator(),
        new ScriptArgTypeInt("value"),
        new ScriptArgTypeLabel()
    ];
}