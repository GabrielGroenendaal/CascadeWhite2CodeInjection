using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPosInTurnOrder : ScriptFunc
{
    public override string Name => "GetPosInTurnOrder";
    public override int Id => 0x5F;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("pos_in_turn_order");
}