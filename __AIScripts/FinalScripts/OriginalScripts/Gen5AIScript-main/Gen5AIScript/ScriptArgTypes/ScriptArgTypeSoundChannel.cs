namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeSoundChannel(string name = "channel", bool allowAll = true) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "system" => 0,
            "sfx_1" => 1,
            "sfx_2" => 2,
            "psg" => 3,
            "sfx_3" => 4,
            "default" => 5,
            "all" => 5,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "system",
            1 => "sfx_1",
            2 => "sfx_2",
            3 => "psg",
            4 => "sfx_3",
            5 => allowAll ? "all" : "default",
            _ => GetErrorStr(value)
        };
    }
}