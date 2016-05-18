using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputCollitionInfo2D : EditorWindow
{

    [MenuItem("Window/2Dコリジョン 出力")]
    public static void ShowWindow()
    {
        OutputCollitionInfoCommon.OutputCollision("Collision2D", "C:/GitHub/kbcGames_jr/kbcgames_jr/Source/Game/CollisionInfo2D.h");

    }

    void OnGUI()
    {
        
    }

}
