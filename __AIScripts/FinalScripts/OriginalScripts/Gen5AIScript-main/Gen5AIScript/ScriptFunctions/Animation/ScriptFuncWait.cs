using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncWait : ScriptFunc
{
    public override string Name => "Wait";
    public override int Id => 0x39;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("frames")
    ];
}