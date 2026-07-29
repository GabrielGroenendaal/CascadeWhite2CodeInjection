using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfUserWillFaint : ScriptFuncJumpBase
{
    public override string Name => "JumpIfUserWillFaint";
    public override int Id => 0x48;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}