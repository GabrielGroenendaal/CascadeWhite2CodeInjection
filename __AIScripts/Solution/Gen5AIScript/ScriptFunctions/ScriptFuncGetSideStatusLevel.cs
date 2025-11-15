using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetSideStatusLevel : ScriptFunc
{
    public override string Name => "GetSideStatusLevel";
    public override int Id => 0x57;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeSideCondition()];
    public override ScriptArgType ReturnType => new ScriptArgTypeInt("side_status_level");
}