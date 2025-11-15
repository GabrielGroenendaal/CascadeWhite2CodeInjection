using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasSuperEffectiveMove : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasSuperEffectiveMove";
    public override int Id => 0x62;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}