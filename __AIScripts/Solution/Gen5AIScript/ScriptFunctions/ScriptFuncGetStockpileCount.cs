using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetStockpileCount : ScriptFunc
{
    public override string Name => "GetStockpileCount";
    public override int Id => 0x44;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("stockpile_count");
}