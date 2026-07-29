using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHealthEQ : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHealthEQ";
    public override int Id => 0x07;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];

}