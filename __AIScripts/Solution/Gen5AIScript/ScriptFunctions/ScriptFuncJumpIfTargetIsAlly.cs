using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfTargetIsAlly : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfTargetIsAlly";
    public override int Id => 0x51;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}