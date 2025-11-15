using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfRandSeedGT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfRandSeedGT";
    public override int Id => 0x70;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}