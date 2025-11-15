using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfStoredNAND : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfStoredNAND";
    public override int Id => 0x18;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeStored("value"), new ScriptArgTypeLabel()];
}