using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPanSound : ScriptFunc
{
    public override string Name => "PanSound";
    public override int Id => 0x36;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeSoundChannel(allowAll: true),
        new ScriptArgTypeChangeSoundPropertyType(),
        new ScriptArgTypeSoundPan("start"),
        new ScriptArgTypeSoundPan("end"),
        new ScriptArgTypeInt("start_delay"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
    ];
}