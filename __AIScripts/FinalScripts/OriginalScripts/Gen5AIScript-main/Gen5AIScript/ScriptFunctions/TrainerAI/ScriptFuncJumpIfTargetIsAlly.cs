using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfTargetIsAlly : ScriptFuncJumpBase
{
    public override string Name => "JumpIfTargetIsAlly";
    public override int Id => 0x51;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}