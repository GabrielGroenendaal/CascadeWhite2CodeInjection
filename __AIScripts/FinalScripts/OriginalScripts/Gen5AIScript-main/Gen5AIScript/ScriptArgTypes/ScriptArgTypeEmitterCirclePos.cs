namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeEmitterCirclePos(string name = "pos") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "attacker_ccw" => 0,
            "attacker_cw" => 1,
            "defender_ccw" => 2,
            "defender_cw" => 3,
            "center_ccw" => 4,
            "center_cw" => 5,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "attacker_ccw",
            1 => "attacker_cw",
            2 => "defender_ccw",
            3 => "defender_cw",
            4 => "center_ccw",
            5 => "center_cw",
            _ => GetErrorStr(value)
        };
    }
}