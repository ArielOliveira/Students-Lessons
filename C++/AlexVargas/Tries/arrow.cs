using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Arrow : MonoBehaviour
{
    public GameObject Ball;
    LineRenderer arrow;
    BallForce ballScript;
    
    // Start is called before the first frame update
    void Start()
    {
        arrow = GetComponent<LineRenderer>();
        ballScript = Ball.GetComponent<BallForce>();

        Vector3 firstPosition = new Vector3(Ball.transform.position.x, Ball.transform.position.y, Ball.transform.position.z);
        Vector3 secondPostision = firstPosition + ballScript.direction;

        

    }

    // Update is called once per frame
    void Update()
    {

        Vector3 arrowPosition = new Vector3(Ball.transform.position.x, 0 , Ball.transform.position.z);
        Vector3 direction = new Vector3(ballScript.direction.x, 0, ballScript.direction.z);

        transform.position = arrowPosition + ballScript.direction;
        transform.rotation = Quaternion.LookRotation(ballScript.direction);
        transform.forward = ballScript.direction;



    }
}
