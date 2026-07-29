using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfRandNE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfRandNE";
    public override int Id => 0x03;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}