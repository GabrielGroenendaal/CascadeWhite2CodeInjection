namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeMultiplier(string name) : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        if (str.EndsWith('x'))
            str = str[..^1];

        if (TryParse(str, out var value))
        {
            return (uint)Math.Round(value * 4096);
        }

        throw new ArgumentException($"Failed to coerce {str} into {Name}");
    }

    private static bool TryParse(string str, out float value)
    {
        value = default;

        if (TryParseFraction(str, out var fractionValue))
        {
            value = fractionValue;
            return true;
        }

        if (!float.TryParse(str, out var fullValue))
            return false;

        value = fullValue;
        return true;
    }

    private static bool TryParseFraction(string str, out float value)
    {
        value = default;

        var divisorIndex = str.IndexOf('/');
        if (divisorIndex <= 0 || divisorIndex >= str.Length - 1)
            return false;


        var numeratorStr = str[..divisorIndex];
        if (!float.TryParse(numeratorStr, out var numerator))
            return false;

        var denominatorStr = str[(divisorIndex + 1)..];
        if (!float.TryParse(denominatorStr, out var denominator))
            return false;

        value = numerator / denominator;
        return true;
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        // Check if this is a basic fraction
        for (var d = 1; d < 9; ++d)
        {
            for (var n = 1; n < 9; ++n)
            {
                if (d == n)
                    continue;

                if ((uint)Math.Round(4096f * n / d) == value)
                    return $"{n}/{d}x";
            }
        }

        // Otherwise, return as a decimal value
        return $"{(float)value / 4096:0.0###}x";
    }
}