using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncStoreIsFirstTurn : ScriptFunc
{
    public override string Name => "StoreIsFirstTurn";
    public override int Id => 0x43;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeBool("is_first_turn");
}