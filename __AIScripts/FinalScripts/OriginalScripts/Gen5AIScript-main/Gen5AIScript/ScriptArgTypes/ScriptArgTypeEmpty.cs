namespace Gen5AIScript.ScriptArgTypes;

public class ScriptArgTypeEmpty(string name = "empty") : ScriptArgType(name)
{
    public override uint FromString(ScriptContext context, int offset, string str)
    {
        return 0;
    }

    public override string FromData(ScriptContext context, int dataOffset, uint value)
    {
        return "--";
    }
}