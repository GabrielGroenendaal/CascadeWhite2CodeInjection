namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeWaitForType(string name = "type") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return str.ToLower() switch
        {
            "all" => 0,
            "camera" => 1,
            "emitter" => 2,
            "poke" => 3,
            "animation" => 4,
            "background" => 5,
            "stage_color" => 6,
            "field_color" => 7,
            "stage_field_color" => 8,
            "animation_color" => 9,
            "all_sound" => 10,
            "sfx_1" => 11,
            "sfx_2" => 12,
            "sfx_3" => 13,
            "psg" => 14,
            "system_sound" => 15,
            "poke_cry" => 16,
            "window" => 17,
            "background_palette" => 18,
            "background_shift" => 19,
            _ => FromErrorStr(str)
        };
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return value switch
        {
            0 => "all",
            1 => "camera",
            2 => "emitter",
            3 => "poke",
            4 => "animation",
            5 => "background",
            6 => "stage_color",
            7 => "field_color",
            8 => "stage_field_color",
            9 => "animation_color",
            10 => "all_sound",
            11 => "sfx_1",
            12 => "sfx_2",
            13 => "sfx_3",
            14 => "psg",
            15 => "system_sound",
            16 => "poke_cry",
            17 => "window",
            18 => "background_palette",
            19 => "background_shift",
            _ => GetErrorStr(value)
        };
    }
}