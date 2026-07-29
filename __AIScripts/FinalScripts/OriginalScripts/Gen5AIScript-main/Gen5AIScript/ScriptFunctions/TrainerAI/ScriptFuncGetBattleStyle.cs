using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncGetBattleStyle : ScriptFunc
{
    public override string Name => "GetBattleStyle";
    public override int Id => 0x45;
    public override ScriptArgType[] ArgTypes => [];
    public override ScriptArgType ReturnType => new ScriptArgTypeBattleStyle();
}