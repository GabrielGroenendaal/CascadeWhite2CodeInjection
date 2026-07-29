using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPreviousMove : ScriptFunc
{
    public override string Name => "GetPreviousMove";
    public override int Id => 0x23;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeMove();
}