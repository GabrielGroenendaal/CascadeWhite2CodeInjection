using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncJumpIfVar : ScriptFuncJumpBase
{
    public override string Name => "JumpIfVar";
    public override int Id => 0x3C;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeAnimVar("a"),
        new ScriptArgTypeAnimCompareOperator(),
        new ScriptArgTypeAnimVar("b"),
        new ScriptArgTypeLabel()
    ];
}