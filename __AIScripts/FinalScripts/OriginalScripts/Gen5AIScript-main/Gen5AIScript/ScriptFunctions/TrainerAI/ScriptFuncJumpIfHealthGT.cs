using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHealthGT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHealthGT";
    public override int Id => 0x06;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];

}