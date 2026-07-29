using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfNotSideCondition : ScriptFuncJumpBase
{
    public override string Name => "JumpIfNoteSideCondition";
    public override int Id => 0x12;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeSideCondition(), new ScriptArgTypeLabel()];
}