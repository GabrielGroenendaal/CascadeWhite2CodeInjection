using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfNotTaunted : ScriptFuncJumpBase
{
    public override string Name => "JumpIfNotTaunted";
    public override int Id => 0x50;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}