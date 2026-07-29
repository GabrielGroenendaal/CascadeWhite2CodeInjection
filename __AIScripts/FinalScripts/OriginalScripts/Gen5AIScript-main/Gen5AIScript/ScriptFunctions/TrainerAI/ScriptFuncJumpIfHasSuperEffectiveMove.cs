using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasSuperEffectiveMove : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasSuperEffectiveMove";
    public override int Id => 0x62;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}