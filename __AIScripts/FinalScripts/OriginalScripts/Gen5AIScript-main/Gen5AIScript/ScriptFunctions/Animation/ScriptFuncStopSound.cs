using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncStopSound : ScriptFunc
{
    public override string Name => "StopSound";
    public override int Id => 0x35;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeSoundChannel(allowAll: true)
    ];
}