using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfFlashFireIsActive : ScriptFuncJumpBase
{
    public override string Name => "JumpIfFlashFireIsActive";
    public override int Id => 0x54;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeLabel()];
}