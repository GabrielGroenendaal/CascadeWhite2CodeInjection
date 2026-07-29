using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetGaugeVisibility : ScriptFunc
{
    public override string Name => "GaugeVisibility";
    public override int Id => 0x33;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeGaugeVisibilityState(),
        new ScriptArgTypeGauge()
    ];
}