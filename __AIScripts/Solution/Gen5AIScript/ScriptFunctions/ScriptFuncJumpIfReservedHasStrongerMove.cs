using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfReservedHasStrongerMove : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfReservedHasStrongerMove";
    public override int Id => 0x61;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeBool("random"), new ScriptArgTypeLabel()];
}