using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfRandGT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfRandGT";
    public override int Id => 0x01;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}