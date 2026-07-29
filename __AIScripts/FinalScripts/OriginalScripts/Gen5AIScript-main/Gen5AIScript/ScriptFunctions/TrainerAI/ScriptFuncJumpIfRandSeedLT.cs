using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfRandSeedLT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfRandSeedLT";
    public override int Id => 0x6F;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}