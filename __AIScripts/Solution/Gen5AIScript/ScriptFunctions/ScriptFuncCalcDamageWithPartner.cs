using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncCalcDamageWithPartner : ScriptFunc
{
    public override string Name => "CalcDamageWithPartner";
    public override int Id => 0x69;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeBool("random")];
    public override ScriptArgType ReturnType => new ScriptArgTypeDamageCalcResult();
}