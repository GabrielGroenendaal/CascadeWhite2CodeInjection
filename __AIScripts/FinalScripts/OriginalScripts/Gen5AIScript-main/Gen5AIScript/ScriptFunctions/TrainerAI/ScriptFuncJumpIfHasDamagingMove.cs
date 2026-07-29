using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasDamagingMove : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasDamagingMove";
    public override int Id => 0x1D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}