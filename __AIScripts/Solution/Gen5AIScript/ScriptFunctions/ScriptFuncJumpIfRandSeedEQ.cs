using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfRandSeedEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfRandSeedEQ";
    public override int Id => 0x71;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}