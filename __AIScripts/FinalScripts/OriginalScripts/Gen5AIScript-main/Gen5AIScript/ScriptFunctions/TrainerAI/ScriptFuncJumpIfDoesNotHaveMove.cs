using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfDoesNotHaveMove : ScriptFuncJumpBase
{
    public override string Name => "JumpIfDoesNotHaveMove";
    public override int Id => 0x39;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeMove(), new ScriptArgTypeLabel()];
}