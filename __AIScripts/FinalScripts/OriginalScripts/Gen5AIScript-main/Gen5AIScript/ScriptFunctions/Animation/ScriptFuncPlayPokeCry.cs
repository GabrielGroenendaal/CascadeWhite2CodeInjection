using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayPokeCry : ScriptFunc
{
    public override string Name => "PlayPokeCry";
    public override int Id => 0x43;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeInt("pitch"),
        new ScriptArgTypeInt("volume"),
        new ScriptArgTypeInt("sub_volume_diff"),
        new ScriptArgTypeInt("sub_speed_diff"),
        new ScriptArgTypeBool("is_reverse"),
        new ScriptArgTypeInt("delay"),
    ];
}