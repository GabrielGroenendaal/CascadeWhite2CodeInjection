using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfMoveEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfMoveEQ";
    public override int Id => 0x19;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeMove(), new ScriptArgTypeLabel()];

}