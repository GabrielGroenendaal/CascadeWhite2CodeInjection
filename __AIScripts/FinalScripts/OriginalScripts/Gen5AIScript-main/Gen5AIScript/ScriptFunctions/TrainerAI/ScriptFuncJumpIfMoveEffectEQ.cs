using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfMoveEffectEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfMoveEffectEQ";
    public override int Id => 0x30;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMoveEffect(), new ScriptArgTypeLabel()];

}