using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfIsNotFainted : ScriptFuncJumpBase
{
    public override string Name => "JumpIfIsNotFainted";
    public override int Id => 0x6B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}