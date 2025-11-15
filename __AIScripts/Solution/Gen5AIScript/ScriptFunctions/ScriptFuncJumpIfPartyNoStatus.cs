using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfPartyNoStatus : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfPartyNoStatus";
    public override int Id => 0x2E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeCondition(), new ScriptArgTypeLabel()];
}