using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfIsFainted : ScriptFuncJumpBase
{
    public override string Name => "JumpIfIsFainted";
    public override int Id => 0x6A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}