using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfRandSeedLT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfRandSeedLT";
    public override int Id => 0x6F;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}