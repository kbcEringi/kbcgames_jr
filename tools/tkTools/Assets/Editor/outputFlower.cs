using UnityEngine;
using UnityEditor;
using System.IO;
using System.Text;

public class outputflower
{

    [MenuItem("Window/フラワー出力")]
    public static void ShowWindow()
    {
        GameObject flower = Selection.activeGameObject;
        if (flower.tag == "FLOWER")
        {
            Transform[] flowers = flower.GetComponentsInChildren<Transform>();
            string headerTxt = "";
            foreach (Transform tr in flowers)
            {
                if (tr.gameObject == flower)
                {
                    continue;
                }
                headerTxt += string.Format("//{0}\n", tr.name);
                headerTxt += "{\n";
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", -tr.position.x, tr.position.y, -tr.position.z);
                headerTxt += string.Format("\t{0},                                              //フラワータイプ\n", tr.GetComponent<Flower>().type);
                headerTxt += "},\n";
            }

            StreamWriter sw = new StreamWriter("C:/GitHub/kbcGames_jr/kbcgames_jr/Source/Game/" + flower.name + ".h", false, Encoding.UTF8);
            sw.Write(headerTxt);
            sw.Close();
            Debug.Log("正常");
        }
    }
}
