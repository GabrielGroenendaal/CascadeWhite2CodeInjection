using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpCompareLevel : ScriptFuncJumpBase
{
    public override string Name => "JumpCompareLevel";
    public override string Description =>
        "Jumps to the specified label if the target's level compares to the user's level using the specified comparison operator.";

    public override int Id => 0x4E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeAICompareOperator(), new ScriptArgTypeLabel()];
}