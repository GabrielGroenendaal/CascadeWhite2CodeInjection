using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJump : ScriptFuncJumpBase
{
    public override string Name => "Jump";
    public override string Description => "Unconditional jump to the specified label.";
    public override int Id => 0x4C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
    public override bool IsJump => true;
}