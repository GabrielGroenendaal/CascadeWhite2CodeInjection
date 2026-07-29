using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpCompareSpeed : ScriptFuncJumpBase
{
    public override string Name => "JumpCompareSpeed";

    public override string Description =>
        "Jumps to the specified label if the target's speed compares to the user's speed using the specified comparison operator.";

    public override int Id => 0x26;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeAICompareOperator(), new ScriptArgTypeLabel()];
}