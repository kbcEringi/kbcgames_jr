using UnityEngine;
using System.Collections;

public class Gimmick : MonoBehaviour {
    public int type = -1;
    public Vector3 PlayerParameter = new Vector3( 0, 0, 0 );

    public void AddComponentTo(Vector3 ple,int t)
    {
        PlayerParameter = ple;
        type = t;
    }

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
