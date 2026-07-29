using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfVolatile1NE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfVolatile1NE";
    public override int Id => 0x0C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeCondition(), new ScriptArgTypeLabel()];
}