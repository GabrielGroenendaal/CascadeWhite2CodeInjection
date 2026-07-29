namespace Gen5AIScript;

public abstract class ScriptFunctionLibrary
{
    public abstract ScriptFunc? GetScriptFunc(string name);
    public abstract ScriptFunc? GetScriptFunc(int id);
}