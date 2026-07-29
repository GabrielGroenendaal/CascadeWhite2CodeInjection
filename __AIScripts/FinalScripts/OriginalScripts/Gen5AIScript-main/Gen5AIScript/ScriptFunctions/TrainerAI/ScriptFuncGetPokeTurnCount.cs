using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPokeTurnCount : ScriptFunc
{
    public override string Name => "GetPokeTurnCount";
    public override int Id => 0x60;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeAbility();
}