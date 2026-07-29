using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasSubstitute : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasSubstitute";
    public override int Id => 0x6D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}