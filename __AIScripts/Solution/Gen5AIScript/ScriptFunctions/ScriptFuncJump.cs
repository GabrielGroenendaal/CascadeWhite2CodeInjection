using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJump : ScriptFuncConditionalJumpBase
{
    public override string Name => "Jump";
    public override string Description => "Unconditional jump to the specified label.";
    public override int Id => 0x4C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel("address")];
    public override bool IsJump => true;
}