using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPartyReserveCount : ScriptFunc
{
    public override string Name => "GetPartyReserveCount";
    public override int Id => 0x27;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("count");
}