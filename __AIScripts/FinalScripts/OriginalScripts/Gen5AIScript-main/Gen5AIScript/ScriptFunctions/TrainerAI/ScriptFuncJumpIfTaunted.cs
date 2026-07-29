using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfTaunted : ScriptFuncJumpBase
{
    public override string Name => "JumpIfTaunted";
    public override int Id => 0x4F;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}