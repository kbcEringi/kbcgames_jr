using UnityEngine;
using UnityEditor;
using System.IO;
using System.Text;

public class stagecollitionRestoration
{

    public static string filename = "Collision3D_stage05";

    [MenuItem("Window/stagecollition救出")]
    public static void ShowWindow()
    {
        GameObject emptyGameObject = new GameObject(filename);

        FileInfo fi = new FileInfo(Application.dataPath + "/a/" + filename + ".h");
        StreamReader fs= fi.OpenText();
        string st;
        while (true)
        {
            st = fs.ReadLine();
            if(st == string.Empty)
            {
                break;
            }
            string name = st.Replace("//", "");
            st = fs.ReadLine();
            st = fs.ReadLine();
            string[] pos = st.Split('(', ',', ')');

            st = fs.ReadLine();
            string[] rot = st.Split('(', ',', ')');
            st = fs.ReadLine();
            string[] sca = st.Split('(', ',', ')');
            st = fs.ReadLine();
            GameObject cube1 = GameObject.CreatePrimitive(PrimitiveType.Cube);
            cube1.transform.parent = GameObject.Find(filename).transform;
            cube1.name = name;
            cube1.transform.position = new Vector3(float.Parse(pos[1].Replace("f", "")), float.Parse(pos[2].Replace("f", "")), float.Parse(pos[3].Replace("f", "")));
            cube1.transform.rotation = new Quaternion(float.Parse(rot[1].Replace("f", "")), float.Parse(rot[2].Replace("f", "")), float.Parse(rot[3].Replace("f", "")), float.Parse(rot[4].Replace("f", "")));
            cube1.transform.localScale = new Vector3(float.Parse(sca[1].Replace("f", "")), float.Parse(sca[2].Replace("f", "")), float.Parse(sca[3].Replace("f", "")));
        }
    }
}
