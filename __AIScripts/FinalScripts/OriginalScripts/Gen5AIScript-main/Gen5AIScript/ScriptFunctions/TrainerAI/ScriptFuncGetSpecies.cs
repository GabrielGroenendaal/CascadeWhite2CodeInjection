using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetSpecies : ScriptFunc
{
    public override string Name => "GetSpecies";
    public override int Id => 0x6E;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeSpecies();
}