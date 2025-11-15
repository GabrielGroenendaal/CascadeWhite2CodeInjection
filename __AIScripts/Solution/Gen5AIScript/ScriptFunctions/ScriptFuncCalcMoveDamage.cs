using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncCalcMoveDamage : ScriptFunc
{
    public override string Name => "CalcMoveDamage";
    public override string Description => "2 if attacker has no moves or if no other move is stronger than the considered move; 1 if there's a different that's stronger; 0 if the considered move does no damage";
    public override int Id => 0x22;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeBool("random")];
    public override ScriptArgType ReturnType => new ScriptArgTypeDamageCalcResult();
}