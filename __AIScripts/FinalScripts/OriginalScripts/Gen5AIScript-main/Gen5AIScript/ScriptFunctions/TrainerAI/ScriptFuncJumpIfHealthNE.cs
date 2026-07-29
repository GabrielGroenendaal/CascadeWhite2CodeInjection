using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHealthNE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHealthNE";
    public override int Id => 0x08;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel()];

}