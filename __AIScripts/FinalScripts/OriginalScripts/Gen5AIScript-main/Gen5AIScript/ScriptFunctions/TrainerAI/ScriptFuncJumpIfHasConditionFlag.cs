using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasConditionFlag : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasConditionFlag";
    public override int Id => 0x0F;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeConditionFlag(), new ScriptArgTypeLabel()];
}