using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasNoMovesWithEffect : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasNoMovesWithEffect";
    public override int Id => 0x3B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel()];
}