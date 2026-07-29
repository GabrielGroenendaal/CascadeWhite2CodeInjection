using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetTrainerAnimation : ScriptFunc
{
    public override string Name => "SetTrainerAnimation";
    public override int Id => 0x22;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeInt("id")
    ];
}