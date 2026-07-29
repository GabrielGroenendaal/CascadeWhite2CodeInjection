using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfRandSeedNE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfRandSeedNE";
    public override int Id => 0x72;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}