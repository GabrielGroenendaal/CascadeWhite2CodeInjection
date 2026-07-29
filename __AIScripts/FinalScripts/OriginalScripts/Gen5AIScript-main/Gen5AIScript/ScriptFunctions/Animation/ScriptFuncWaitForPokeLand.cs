using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncWaitForPokeLand : ScriptFunc
{
    public override string Name => "WaitForPokeLand";
    public override int Id => 0x4B;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeSide()
    ];
}