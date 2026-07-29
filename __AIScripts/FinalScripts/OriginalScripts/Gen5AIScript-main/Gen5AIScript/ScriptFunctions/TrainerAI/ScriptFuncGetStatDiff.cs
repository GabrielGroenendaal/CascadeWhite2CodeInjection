using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetStatDiff : ScriptFunc
{
    public override string Name => "GetStatDiff";

    public override string Description => "stores the specified stat of the specified Pokémon subtracted by the specified stat of the user." +
                                          "Negative would mean that the user's stat is larger.";

    public override int Id => 0x65;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeStat()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("stat_diff");
}