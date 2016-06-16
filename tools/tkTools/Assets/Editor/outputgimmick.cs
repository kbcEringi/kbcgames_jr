using UnityEngine;
using UnityEditor;
using System.IO;
using System.Text;

public class outputgimmick{

    [MenuItem("Window/ギミック出力")]
    public static void ShowWindow()
    {
        GameObject gimmick = Selection.activeGameObject;
        if (gimmick.tag == "GIMMICK")
        {
            Transform[] gimmicks = gimmick.GetComponentsInChildren<Transform>();
            string headerTxt = "";
            foreach (Transform tr in gimmicks)
            {
                if (tr.gameObject == gimmick)
                {
                    continue;
                }
                headerTxt += string.Format("//{0}\n", tr.name);
                headerTxt += "{\n";
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", -tr.position.x, tr.position.y, -tr.position.z);
                headerTxt += string.Format("\tD3DXQUATERNION({0:f}, {1:f}f, {2:f}f, {3:f}f ),    //回転\n", tr.rotation.x, tr.rotation.y, tr.rotation.z, tr.rotation.w);
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f ),            //拡大\n", tr.lossyScale.x, tr.lossyScale.y, tr.lossyScale.z);
                headerTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f ),            //自由に使えるよ\n", tr.GetComponent<Gimmick>().PlayerParameter.x, tr.GetComponent<Gimmick>().PlayerParameter.y, tr.GetComponent<Gimmick>().PlayerParameter.z);
                headerTxt += string.Format("\t{0},                                              //ギミックタイプ\n", tr.GetComponent<Gimmick>().type);
                headerTxt += "},\n";
            }

            StreamWriter sw = new StreamWriter("C:/GitHub/kbcGames_jr/kbcgames_jr/Source/Game/" + gimmick.name + ".h", false, Encoding.UTF8);
            sw.Write(headerTxt);
            sw.Close();
        }
    }
}
