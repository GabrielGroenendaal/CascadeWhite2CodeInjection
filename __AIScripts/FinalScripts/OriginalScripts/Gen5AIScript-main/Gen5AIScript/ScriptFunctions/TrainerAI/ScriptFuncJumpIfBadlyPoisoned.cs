using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfBadlyPoisoned : ScriptFuncJumpBase
{
    public override string Name => "JumpIfBadlyPoisoned";
    public override int Id => 0x0D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}