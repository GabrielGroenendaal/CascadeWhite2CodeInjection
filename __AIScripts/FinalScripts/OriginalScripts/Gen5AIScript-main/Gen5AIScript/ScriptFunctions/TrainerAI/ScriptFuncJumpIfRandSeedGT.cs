using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfRandSeedGT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfRandSeedGT";
    public override int Id => 0x70;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}