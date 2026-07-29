using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfNotBadlyPoisoned : ScriptFuncJumpBase
{
    public override string Name => "JumpIfNotBadlyPoisoned";
    public override int Id => 0x0E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}