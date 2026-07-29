using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncDistortBackground : ScriptFunc
{
    public override string Name => "DistortBackground";
    public override int Id => 0x26;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeDistortBackgroundDir(),
        new ScriptArgTypeFixedPoint("radius"),
        new ScriptArgTypeInt("line"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeBackgroundFadeType(),
        new ScriptArgTypeInt("fade_frames"),
    ];
}