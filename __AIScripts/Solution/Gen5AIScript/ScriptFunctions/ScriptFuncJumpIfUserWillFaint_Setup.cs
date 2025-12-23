using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserWillFaint_Setup : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfUserWillFaint_Setup";
    public override int Id => 0x69;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}