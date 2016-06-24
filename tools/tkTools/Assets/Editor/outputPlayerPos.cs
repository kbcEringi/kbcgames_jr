using UnityEngine;
using UnityEditor;
using System.IO;
using System.Text;

public class outputPlayerPos
{

    [MenuItem("Window/Playerposition出力")]
    public static void ShowWindow()
    {
        GameObject Player = Selection.activeGameObject;
        if (Player.tag == "PLAYER")
        {
            string headerTxt = "";

            headerTxt += string.Format("//{0}\n", Player.name);
                headerTxt += "{\n";
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", -Player.transform.position.x, Player.transform.position.y, -Player.transform.position.z);
                headerTxt += "},\n";

                StreamWriter sw = new StreamWriter("C:/GitHub/kbcGames_jr/kbcgames_jr/Source/Game/" + Player.name + ".h", false, Encoding.UTF8);
            sw.Write(headerTxt);
            sw.Close();
        }
    }
}
