using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlaySound : ScriptFunc
{
    public override string Name => "PlaySound";
    public override int Id => 0x34;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("id"),
        new ScriptArgTypeSoundChannel(allowAll: false),
        new ScriptArgTypeSoundPan(),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("pitch"),
        new ScriptArgTypeInt("volume"),
        new ScriptArgTypeInt("modulation_amplitude"),
        new ScriptArgTypeInt("modulation_rate"),
        new ScriptArgTypeEmpty()
    ];
}