using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfStoredGT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfStoredGT";
    public override int Id => 0x14;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}