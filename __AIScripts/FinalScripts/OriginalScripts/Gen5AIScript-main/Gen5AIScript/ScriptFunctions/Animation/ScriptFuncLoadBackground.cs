using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncLoadBackground : ScriptFunc
{
    public override string Name => "LoadBackground";
    public override int Id => 0x24;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id")
    ];
}