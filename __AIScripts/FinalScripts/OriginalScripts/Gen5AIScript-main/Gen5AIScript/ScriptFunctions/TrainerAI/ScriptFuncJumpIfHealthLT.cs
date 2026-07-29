using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHealthLT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHealthLT";
    public override int Id => 0x05;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];
}