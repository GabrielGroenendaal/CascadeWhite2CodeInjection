using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetPositiveStatStageTotal : ScriptFunc
{
    public override string Name => "GetPositiveStatStageTotal";
    public override int Id => 0x64;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("stat_change_total");
}