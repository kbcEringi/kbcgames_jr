using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputCollitionInfo3D : EditorWindow
{

    [MenuItem("Window/3Dコリジョン 出力")]
    public static void ShowWindow()
    {
        OutputCollitionInfoCommon.OutputCollision("Collision3D", "C:/GitHub/kbcGames_jr/kbcgames_jr/Source/Game/CollisionInfo3D.h");
    }

    void OnGUI()
    {
        
    }

}
