using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncFlee : ScriptFunc
{
    public override string Name => "Flee";
    public override int Id => 0x3D;
    public override ScriptArgType[] ArgTypes => [];
    public override bool AddSpaceBelow => true;
    public override bool Continue => false;
}