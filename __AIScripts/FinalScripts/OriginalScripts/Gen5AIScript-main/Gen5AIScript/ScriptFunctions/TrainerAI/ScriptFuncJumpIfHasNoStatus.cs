using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasNoStatus : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasNoStatus";
    public override int Id => 0x0A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}