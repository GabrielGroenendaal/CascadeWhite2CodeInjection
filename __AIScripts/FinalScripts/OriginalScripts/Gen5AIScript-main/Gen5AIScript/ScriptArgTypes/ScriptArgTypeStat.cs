namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeStat(string name = "stat") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "hp" => 0,
            "atk" => 1,
            "def" => 2,
            "spa" => 3,
            "spd" => 4,
            "spe" => 5,
            "acc" => 6,
            "eva" => 7,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "hp",
            1 => "atk",
            2 => "def",
            3 => "spa",
            4 => "spd",
            5 => "spe",
            6 => "acc",
            7 => "eva",
            _ => GetErrorStr(value)
        };
    }
}