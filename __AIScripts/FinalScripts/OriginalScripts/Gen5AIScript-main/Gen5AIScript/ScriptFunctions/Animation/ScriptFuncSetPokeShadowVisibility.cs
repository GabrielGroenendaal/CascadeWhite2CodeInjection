using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetPokeShadowVisibility : ScriptFunc
{
    public override string Name => "SetPokeShadowVisibility";
    public override int Id => 0x1D;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeVisibilityState(),
    ];
}