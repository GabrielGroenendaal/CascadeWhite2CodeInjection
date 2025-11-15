using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncGetBattleType : ScriptFunc
{
    public override string Name => "GetBattleType";
    public override int Id => 0x46;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeBattleType();
}