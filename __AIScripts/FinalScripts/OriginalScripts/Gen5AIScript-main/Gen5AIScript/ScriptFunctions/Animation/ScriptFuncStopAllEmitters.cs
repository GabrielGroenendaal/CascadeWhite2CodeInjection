using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncStopAllEmitters : ScriptFunc
{
    public override string Name => "StopAllEmitters";
    public override int Id => 0x0B;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id")
    ];
}