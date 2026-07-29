using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncLoadParticles : ScriptFunc
{
    public override string Name => "LoadParticles";
    public override int Id => 0x06;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id")
    ];
}