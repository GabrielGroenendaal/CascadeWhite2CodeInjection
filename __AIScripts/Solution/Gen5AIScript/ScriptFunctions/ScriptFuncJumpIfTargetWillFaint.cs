using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfTargetWillFaint : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfTargetWillFaint";
    public override int Id => 0x36;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeBool("useRandom"), new ScriptArgTypeLabel()];
}