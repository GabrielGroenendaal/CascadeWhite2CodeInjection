using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasMove : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasMove";
    public override int Id => 0x38;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeMove(), new ScriptArgTypeLabel()];
}